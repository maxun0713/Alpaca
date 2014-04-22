/*
 * TimerModule.h
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */

#ifndef TIMERMODULE_H_
#define TIMERMODULE_H_

#include "IModule.h"
#include "ITimer.h"
#include <map>
using namespace std;

namespace Alpaca {

#define DEFAULT_TIMER_CYCLE 1000

class TimerModule: public IModule{
public:
	TimerModule();
	virtual ~TimerModule();

	int      AddTimer(ITimer* timer);
	uint64_t OnTimer();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;
private:

	bool    _ProcTimers(uint64_t delta);
private:
	typedef multimap<uint64_t, ITimer* > TIMER_STORAGE;
	typedef multimap<uint64_t, ITimer* >::iterator TIMER_STORAGE_ITER;
	typedef pair<TIMER_STORAGE_ITER, TIMER_STORAGE_ITER> TIMER_GROUP;
	TIMER_STORAGE  _storage;
	uint64_t       _timeCache;
};

} /* namespace Alpaca */

#endif /* TIMERMODULE_H_ */
