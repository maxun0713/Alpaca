//
//  main.cpp
//  BueEngine
//
//  Created by marv on 14-5-10.
//  Copyright (c) 2014年 marv. All rights reserved.
//

#include "BusEngine.h"
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
int main(int argc, const char * argv[])
{
	BusEngine busEngine;
	int ret = busEngine.Initialize(NULL, 0);
	if (ret != 0)
	{
		return -1;
	}

    INodePort* srvPort = busEngine.CreateServerNodePort("tcp://127.0.0.1:8888", "SERVER", 1000, 256);
    if (srvPort == NULL)
    {
    	return -1;
    }

    while (1)
    {
    	ret = busEngine.Schedule(true);
    	if (ret != 0)
    	{
    		cout << busEngine.GetLastErrMsg() << endl;
    		sleep(2);
    	}
    }

    return 0;
}

