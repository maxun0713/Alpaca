/*
 * main.cpp
 *
 *  Created on: 2014年4月22日
 *      Author: marv
 */




#include <map>
#include <iostream>
#include "TestTimer.h"
#include "TimerModule.h"
using namespace std;
using namespace Alpaca;
int main()
{
	TimerModule mod;
	mod.Initialize(NULL, 0);
	ITimer* timer  = new TestTimer(NULL, mod.GetTimeCache() + 300, 3000);
	uint64_t gap;

	int x = mod.AddTimer(timer);
	while(1)
	{
		gap = mod.OnTimer() - mod.GetTimeCache();
	}


	return 0;
}
