/*
 * Main.cpp
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#include "LogEngine.h"
#include "Util.h"
#include "ServerFrame.h"
#include <iostream>

using namespace std;


int _Run(const char* app, int daemon)
{
	T_ERROR_VAL(app)

	if( Lock(app))
	{
		LOG_ERROR("another " << app << " instance is running");
		return -1;
	}

	T_ERROR_VAL(SavePid(app) == 0)
	T_ERROR_VAL(SetSystemParms() == 0)
	if(daemon)  T_ERROR_VAL(Deamonlize(0, 1) == 0)

	ServerFrame* servFrame = new ServerFrame();
	T_ERROR_VAL(servFrame->Initialize(NULL, 0) == 0)
	T_ERROR_VAL(servFrame->Activate() == 0)

	LOG_INFO(app << "is about to run");
	SERVER_STATUS status;
	do{
		servFrame->OnTimer();

		status = servFrame->OnProc(NULL);
	}while(status != SERVER_STATUS_SHUTDOWN);

	servFrame->Release();

	UnLock(app);

	return 0;
}

int main(int argc, char** argv)
{
	LogEngine engine;
	engine.Initialize(argv[0], "/home/marv");

	return _Run(argv[0], 0);
}
