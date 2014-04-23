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

int TimerModule::AddTimer(ITimer* timer) {

	if(!timer | (timer->GetTimeout() <= 0) ) return -1;

	uint64_t timeout = timer->GetTimeout();
	TIMER_GROUP_ITERATOR iter = _storage.find(timeout);

	if(iter)
	{
		iter->second.insert(make_pair(timeout, timer));
	}
	else
	{
		TIMER_GROUP group;
		group.insert(make_pair(timeout, timer));
		_storage.insert(make_pair(timeout, group) );
	}

	timer->SetTimerId(_timerIDCounter);
	_timerSlot.insert(make_pair(_timerIDCounter, timeout));
	return _timerIDCounter++;
}


int  TimerModule::DelTime(int timerid)
{
	TIMER_SLOT_ITERATOR iter = _timerSlot.find(timerid);
//	uint64_t timeout;
//	if( iter == _timerSlot.end())
//	{
//		SET_ERR_MSG(_lastErrMsg, "invalid timer id" << timerid);
//		return -1;
//	}


//	TIMER_GROUP group = _storage.equal_range()
//	TIMER_ITERATOR   timerIter;

	return -1;
}

uint64_t TimerModule::OnTimer() {
	uint64_t now,diff;
	struct timeval current;
	bool finish = false;

	T_ERROR_VAL_WITH_ERR_INFO(gettimeofday(&current, NULL) == 0)
	now = current.tv_sec * 1000  + current.tv_usec / 1000;
	diff = now - _timeCache;
	_timeCache = now;

	while(!finish)
	{
		finish = _ProcTimers(diff);
	}

	if(!_storage.empty())
	{
		return _storage.begin()->first;
	}

	return DEFAULT_TIMER_CYCLE;
}

bool TimerModule:: _ProcTimers(uint64_t delta)
{
	TIMER_GROUP_ITERATOR groupIter;
//	TIMER_GROUP group;
	TIMER_ITERATOR   timerIter;
//	uint64_t hint = 0;

	groupIter = _storage.begin();
	for(; _storage != _storage.end() ; groupIter++)
	{
		if(groupIter->first > delta)
		{
			return true;  //no timer callback to invoke
		}


		TIMER_GROUP& group = *(groupIter->second);

		//group = _storage.equal_range(groupIter->first);
//		timerIter = group.begin();
//		for(; timerIter !=group.end(); timerIter++)
//		{
//			if(timerIter->second)
//			{
//				timerIter->second->Proc();
//				if(timerIter->second->GetType() & TIMER_TYPE_ONCE)
//				{
////					hint = timerIter->second->GetTimeout();
//					_timerSlot.erase(timerIter->second->GetTimerID());
//					group.erase(timerIter); //iterator invalid, quit this round
//					return false;
//				}
//			}
//		}
	}

// just keep the slot
//	if(hint)
//	{
//		groupIter = _storage.find(hint);
//		if(groupIter->second.empty())
//		{
//
//		}
//	}

	return true;
}


} /* namespace Alpaca */
