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

TimerModule::TimerModule():_timeCache(0) {
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

	_storage.insert(make_pair(timer->GetTimeout(), timer));

	return 0;
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
	TIMER_STORAGE_ITER iter,tmp;
	TIMER_GROUP group;

	iter = _storage.begin();
	for(; iter != _storage.end() ; iter++)
	{
		if(iter->first > delta)
		{
			return true;  //no timer callback to invoke
		}

		group = _storage.equal_range(iter->first);
		for(tmp=group.first; tmp!=group.second; tmp++)
		{
			if(tmp->second)
			{
				tmp->second->Proc();
				if(tmp->second->GetType() & TIMER_TYPE_ONCE)
				{
					_storage.erase(tmp); //iterator invalid, quit this round
					return false;
				}
			}
		}
	}

	return true;
}


} /* namespace Alpaca */
