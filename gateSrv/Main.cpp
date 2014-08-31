/*
 * Main.cpp
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#include "LogEngine.h"
#include "Util.h"
#include "CommonDef.h"
#include "GateSrv.h"
#include <iostream>

using namespace std;
using namespace alpaca;

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

	IServer* server = new GateSrv();
	if (server == NULL) {
		LOG_FATAL("create ");
	}

	T_ERROR_VAL(server->Initialize(NULL, 0) == 0)
	T_ERROR_VAL(server->Activate() == 0)

	LOG_INFO(app << " is about to run");

	server->OnProc(NULL);

	server->Release();

	delete server;

	UnLock(app);

	return 0;
}

int main(int argc, char** argv) {
	LogEngine engine;
	engine.Initialize(argv[0], "/home/marv");

	return _Run(argv[0], 0);
}
