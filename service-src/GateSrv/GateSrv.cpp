/*
 * GateServer.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#include "GateSrv.h"
#include "IOEngine/Inc/IEventEngine.h"
#include "BusEngine/Inc/IBusEngine.h"
#include "SessionManager.h"
#include "CommonDef.h"
#include "ConfigDef.h"
#include "GatePortSink.h"
#include <string.h>
#include <iostream>

using namespace bus;
using namespace std;

GateSrv::GateSrv():_eventEngine(NULL), _busEngine(NULL),_portToGameSrv(NULL) {
	// TODO Auto-generated constructor stub
}

GateSrv::~GateSrv() {
	// TODO Auto-generated destructor stub
}

uint64_t GateSrv::OnTimer()
{
	return 0;
}



SERVER_STATUS GateSrv::OnProc(void *arg)
{
	while (1)
	{
		cout << _portToGameSrv->Send("GameSrv", "Hello", strlen("Hello")) << endl;
		sleep(5);
	}
	return SERVER_STATUS_SHUTDOWN;
}



int GateSrv::Release()
{
	T_ERROR_VAL(_busEngine->Release() == 0)
	T_ERROR_VAL(_eventEngine->Release() == 0)

	delete this;
	return 0;
}



int GateSrv::Activate()
{
	_portToGameSrv = _busEngine->CreateClientNodePort(addr, slefID, bufLen, nodeIDBufLen);
	T_ERROR_VAL(_portToGameSrv)
	T_ERROR_VAL(_portToGameSrv->AddPortSink(new GatePortSink()) == 0)
	T_ERROR_VAL(_busEngine->Activate() == 0)

	//T_ERROR_VAL(_eventEngine->Activate() == 0)
	return 0;
}



int GateSrv::Initialize(void *arg, int arglen)
{
	T_ERROR_VAL(_modManager.Initialize((void*)SERVICE_PATH,
			strlen(SERVICE_PATH)) == 0)
	_eventEngine = (IEventEngine*)_modManager.LoadModule("IOEngine");
	T_ERROR_VAL(_eventEngine)
	T_ERROR_VAL(_eventEngine->Initialize(NULL, 0) == 0);
	T_ERROR_VAL(_eventEngine->CreateListener(ServerIP, port, new SessionManager()) == 0)

	_busEngine = (IBusEngine*)_modManager.LoadModule("BusEngine");
	T_ERROR_VAL(_busEngine)
	T_ERROR_VAL(_busEngine->Initialize(NULL, 0) == 0)

	return 0;
}


