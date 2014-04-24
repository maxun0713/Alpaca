/*
 * ITimer.h
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */

#ifndef ITIMER_H_
#define ITIMER_H_

#include <stdint.h>

namespace Alpaca {

class ITimer {
public:
	ITimer(void* data, uint64_t timeout, uint64_t cycle)
		:_data(data),_timeout(timeout),_cycle(cycle),_id(0){};
	virtual ~ITimer(){};

	void virtual Proc() = 0;
	void virtual Destroy() = 0;

	uint64_t GetTimeout() {
		return _timeout;
	}

	void ProceedTimeout(){
		_timeout += _cycle;
	}

	uint64_t GetCycle() const{
		return _cycle;
	}

	void SetTimerId(int id){
		_id = id;
	}

	int  GetTimerID(){
		return _id;
	}

private:
	void* _data;
	uint64_t _timeout;
	uint64_t _cycle;
	int   _id;
};

} /* namespace Alpaca */

#endif /* ITIMER_H_ */
