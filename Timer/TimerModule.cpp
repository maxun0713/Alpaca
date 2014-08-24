/*
 * TimerModule.cpp
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */

#include "TimerModule.h"
#include <sys/time.h>
#include <errno.h>
#include <string.h>

namespace Alpaca {

TimerModule::TimerModule():_timerIDCounter(0), _timeCache(0) {
	// TODO Auto-generated constructor stub

}

TimerModule::~TimerModule() {
	// TODO Auto-generated destructor stub
}


uint64_t TimerModule::GetTimeCache() const
{
	return _timeCache;
}


int TimerModule::_UpdateTimeCache(){
	struct timeval current;
	if(gettimeofday(&current, NULL) )
	{
		SET_ERR_MSG(_lastErrMsg, " update time cache failed" << strerror(errno))
		return -1;
	}

	_timeCache = current.tv_sec * 1000  + current.tv_usec / 1000;
	return 0;
}

int TimerModule::Initialize(void* arg, int arglen) {
	return _UpdateTimeCache();
}

int TimerModule::Activate() {
	return 0;
}

int TimerModule::Release() {
	return 0;
}

int TimerModule::AddTimer(ITimer* timer, bool newly) {
	if(!timer ) return -1;

	uint64_t timeout = timer->GetTimeout();
	TIMER_GROUP_ITERATOR iter = _storage.find(timeout);
	int idCounter = _timerIDCounter;

	if(iter != _storage.end())
	{
		iter->second.insert(make_pair(timeout, timer));
	}
	else
	{
		TIMER_GROUP group;
		group.insert(make_pair(timeout, timer));
		_storage.insert(make_pair(timeout, group) );
	}

	if(newly)
	{
		timer->SetTimerId(idCounter);
		_timerSlot.insert(make_pair(idCounter, timeout));
		_timerIDCounter ++;
	}

	return idCounter;
}


int  TimerModule::DelTimer(int timerid)
{
	TIMER_SLOT_ITERATOR iter = _timerSlot.find(timerid);
	if(iter == _timerSlot.end())
	{
		SET_ERR_MSG(_lastErrMsg, "no timer found id: " << timerid);
		return -1;
	}
	_timerSlot.erase(iter);

	uint64_t timeout = iter->second;
	TIMER_GROUP_ITERATOR groupIter = _storage.find(timeout);
	if(groupIter != _storage.end())
	{
		groupIter->second.erase(timerid);
		return 0;
	}
	else
	{
		SET_ERR_MSG(_lastErrMsg, "no timer slot found id: " << timerid << ", timeout: " << timeout);
		return -1;
	}

	return -1;
}

uint64_t TimerModule::Schedule() {
	bool finish = false;

	if(_UpdateTimeCache())  return -1;

	while(!finish)
	{
		finish = _ProcTimers();
	}

	if(!_storage.empty())
	{
		return _storage.begin()->first - _timeCache;
	}

	return _timeCache;
}

bool TimerModule:: _ProcTimers()
{
	TIMER_GROUP_ITERATOR groupIter;
	TIMER_ITERATOR   timerIter;

	groupIter = _storage.begin();
	if(!_storage.empty())
	{
		if(groupIter->first > _timeCache)
		{
			return true;  //no timer callback to invoke
		}

		TIMER_GROUP& group = groupIter->second;
		timerIter = group.begin();
		for(; timerIter !=group.end(); timerIter++)
		{
			ITimer* tmp = timerIter->second;
			if(tmp)
			{
				tmp->Proc();
				if(tmp->GetCycle())
				{
					tmp->ProceedTimeout();
					AddTimer(timerIter->second, false);
				}
				else
				{
					DelTimer(tmp->GetTimerID());
					tmp->Destroy();
				}
			}
		}

		_storage.erase(groupIter);
		return false;
	}

	return true;
}


} /* namespace Alpaca */
