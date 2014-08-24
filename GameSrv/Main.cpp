/*
 * Main.cpp
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#include "LogEngine.h"
#include "Util.h"
#include "GameSrv.h"
#include "CommonDef.h"
#include <iostream>

using namespace std;

int _Run(const char* app, int daemon) {
	T_ERROR_VAL(app)

	if (Lock(app)) {
		LOG_ERROR("another " << app << " instance is running");
		return -1;
	}

	T_ERROR_VAL(SavePid(app) == 0)
	T_ERROR_VAL(SetSystemParms() == 0)
	if (daemon)
		T_ERROR_VAL(Deamonlize(0, 1) == 0)

	IServer* IServer = new GameSrv();
	if (IServer == NULL) {
		LOG_FATAL("create ");
	}

	T_ERROR_VAL(IServer->Initialize(NULL, 0) == 0)
	T_ERROR_VAL(IServer->Activate() == 0)

	LOG_INFO(app << " is about to run");

	IServer->OnProc(NULL);

	IServer->Release();

	delete IServer;

	UnLock(app);

	return 0;
}

int main(int argc, char** argv) {
	LogEngine engine;
	engine.Initialize(argv[0], "/home/marv");

	return _Run(argv[0], 0);
}
