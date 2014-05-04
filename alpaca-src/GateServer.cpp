/*
 * GateServer.cpp
 *
 *  Created on: 2014年5月3日
 *      Author: marv
 */

#include "GateServer.h"
#include "DefaultConfig.h"
#include "IOEngine/Inc/IEventEngine.h"
#include "CommonDef.h"

GateServer::GateServer():_engine(NULL) {
	// TODO Auto-generated constructor stub

}

GateServer::~GateServer() {
	// TODO Auto-generated destructor stub
}

uint64_t GateServer::OnTimer() {
	return 0;
}

SERVER_STATUS GateServer::OnProc(void* arg) {
	_engine->Activate();
	return SERVER_STATUS_PAUSED;
}

int GateServer::Initialize(void* arg, int arglen) {
	T_ERROR_VAL(_modManager.Initialize((void*)FRAME_SERVICE_PATH,
			strlen(FRAME_SERVICE_PATH)) == 0)
	_engine = (IEventEngine*)_modManager.LoadModule("IOEngine");
	T_ERROR_VAL(_engine);
	_engine->Initialize(NULL, 0);
	_engine->CreateListener("127.0.0.1", 27017, NULL);
	return 0;
}

int GateServer::Activate() {
	return 0;
}

int GateServer::Release() {
	return 0;
}
