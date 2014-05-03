/*
 * TestTimer.h
 *
 *  Created on: 2014年4月24日
 *      Author: marv
 */

#ifndef TESTTIMER_H_
#define TESTTIMER_H_

#include "ITimer.h"
#include <iostream>
using namespace Alpaca;
using namespace std;

class TestTimer : public ITimer{
public:
	TestTimer(void* data, uint64_t timeout, uint64_t cycle);
	virtual ~TestTimer();

	void virtual Proc() ;
	void virtual Destroy() ;
};

#endif /* TESTTIMER_H_ */
