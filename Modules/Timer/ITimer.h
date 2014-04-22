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

#define TIMER_TYPE_ONCE  1 << 0
#define TIMER_TYPE_REP   1 << 2

class ITimer {
public:
	ITimer(void* data, uint64_t timeout,short type)
		:_data(data),_timeout(timeout),_type(type){};
	virtual ~ITimer(){};

	void virtual Proc() = 0;
	void virtual Destroy() = 0;

	uint64_t GetTimeout() {
		return _timeout;
	}

private:
	void* _data;
	uint64_t _timeout;
	short _type;
};

} /* namespace Alpaca */

#endif /* ITIMER_H_ */
