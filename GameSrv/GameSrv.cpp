/*
 * GameSrv.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#include "GameSrv.h"
#include "ConfigDef.h"
#include "CommonDef.h"
#include "GatePortSink.h"
#include <string.h>

GameSrv::GameSrv() :
	_busEngine(NULL), _portForGate(NULL) {

}

GameSrv::~GameSrv() {

}

int GameSrv::Initialize(void* arg, int arglen) {
	T_ERROR_VAL(_modManager.Initialize((void*)SERVICE_PATH,
					strlen(SERVICE_PATH)) == 0)

	_busEngine = new BusEngine();
	T_ERROR_VAL(_busEngine)
	T_ERROR_VAL(_busEngine->Initialize(NULL, 0) == 0)

	return 0;
}

int GameSrv::Activate() {
	_portForGate = _busEngine->CreateServerNodePort(addr, slefID, bufLen,
			nodeIDBufLen);
	T_ERROR_VAL(_portForGate)
	T_ERROR_VAL(_portForGate->AddPortSink(new GatePortSink()) == 0)
	T_ERROR_VAL(_busEngine->Activate() == 0)

	return 0;
}

int GameSrv::Release() {
	T_ERROR_VAL(_busEngine->Release() == 0)
	delete this;
	return 0;
}

uint64_t GameSrv::OnTimer() {
	return 0;
}

SERVER_STATUS GameSrv::OnProc(void* arg) {
	while (1) {
		int ret = _busEngine->Schedule(true);
	}
	return SERVER_STATUS_SHUTDOWN;
}
