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
	int finish = 0;
	uint64_t now,diff;
	struct timeval current;

	T_ERROR_VAL_WITH_ERR_INFO(gettimeofday(&current, NULL) == 0)
	now = current.tv_sec * 1000  + current.tv_usec / 1000;
	diff = now - _timeCache;
	_timeCache = now;

	TIMER_STORAGE_ITER iter = _storage.begin();
	TIMER_GROUP group;
//	ITimer* timer;
	for(; iter != _storage.end() && !finish ; iter++)
	{
		if(iter->first > diff)
		{
			return iter->first;
		}

//		group = _storage.equal_range(iter->first);
//		for(timer=group.first; timer!=group.second; timer++)
//		if(iter->second)
//		{
//			iter->second->Proc();
//		}
//		else
//		{
//			LOG_ERROR("timer null exception");
//		}
	}


	return 0;
}


} /* namespace Alpaca */
