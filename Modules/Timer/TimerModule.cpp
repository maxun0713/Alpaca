/*
 * TimerModule.cpp
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */

#include "TimerModule.h"
#include "CommonDef.h"
#include <sys/time.h>

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

int TimerModule::Initialize(void* arg, int arglen) {
	struct timeval current;

	T_ERROR_VAL_WITH_ERR_INFO(gettimeofday(&current, NULL) == 0)
	_timeCache = current.tv_sec * 1000  + current.tv_usec / 1000;

	return 0;
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


int  TimerModule::DelTime(int timerid)
{
//	TIMER_SLOT_ITERATOR iter = _timerSlot.find(timerid);


	return -1;
}

uint64_t TimerModule::OnTimer() {
	struct timeval current;
	bool finish = false;

	T_ERROR_VAL_WITH_ERR_INFO(gettimeofday(&current, NULL) == 0)
	_timeCache = current.tv_sec * 1000  + current.tv_usec / 1000;

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
