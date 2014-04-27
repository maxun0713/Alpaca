/*
 * TestTimer.cpp
 *
 *  Created on: 2014年4月24日
 *      Author: marv
 */

#include <Modules/Timer/TestTimer.h>

TestTimer::TestTimer(void* data, uint64_t timeout, uint64_t cycle):ITimer(data, timeout, cycle){
	// TODO Auto-generated constructor stub

}

TestTimer::~TestTimer() {
	// TODO Auto-generated destructor stub
}

void TestTimer::Proc() {
	time_t t = time(NULL);
	cout << "test " << ctime(&t) <<endl;
}

void TestTimer::Destroy() {
}
