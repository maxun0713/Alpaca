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
#include <set>
using namespace std;

namespace Alpaca {

#define DEFAULT_TIMER_CYCLE 1000

class TimerModule: public IModule{
public:
	TimerModule();
	virtual ~TimerModule();

	uint64_t GetTimeCache() const;
	int      AddTimer(ITimer* timer, bool newly = true);
	uint64_t Schedule();

	int      DelTimer(int timeid);

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;
private:

	bool    _ProcTimers();
	int     _UpdateTimeCache();
private:
	typedef map<uint64_t, map<int, ITimer*> > TIMER_STORAGE;
	typedef map<uint64_t, map<int, ITimer*> >::iterator TIMER_GROUP_ITERATOR;
	typedef map<int , ITimer* >TIMER_GROUP;
	typedef map<int, ITimer*>::iterator TIMER_ITERATOR;
	TIMER_STORAGE  _storage;
	typedef map<int, uint64_t>::iterator TIMER_SLOT_ITERATOR;
	map<int, uint64_t>	   _timerSlot;
	int            _timerIDCounter;
	uint64_t       _timeCache;
};

} /* namespace Alpaca */

#endif /* TIMERMODULE_H_ */
