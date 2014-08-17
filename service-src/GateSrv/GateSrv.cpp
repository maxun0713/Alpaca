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
#include "GamePortSink.h"
#include "ExternPortManager.h"
#include <string.h>
#include <iostream>
#include <zmq.h>
#include "Message.pb.h"
#include "MsgCoder.h"

using namespace bus;
using namespace std;

GateSrv::GateSrv() :
	_eventEngine(NULL), _busEngine(NULL), _portToGameSrv(NULL),
			_lastConnTime(0) {
	// TODO Auto-generated constructor stub
}

GateSrv::~GateSrv() {
	// TODO Auto-generated destructor stub
}

uint64_t GateSrv::OnTimer() {
	return 0;
}

SERVER_STATUS GateSrv::OnProc(void *arg) {
	while (1) {
		HeartBeat();

		sleep(5);
	}
	return SERVER_STATUS_SHUTDOWN;
}

int GateSrv::HeartBeat() {
	cout << "Heartbeat" << endl;
	time_t now = time(NULL);
	if (now - _lastConnTime > 60) {
		int iRet;
		char buf[1024] = { 0 };
		char* pBuf = buf;
		int bufLen = sizeof(buf);
		MSG_HeartBeat_SYN msg;
		MsgCoder coder;
		iRet = coder.EncodeMsgBody(HEARTBEAT_SYN, &msg, pBuf, bufLen);
		return _portToGameSrv->Send("GameSrv", pBuf, bufLen);
	}
	return 1;
}

int GateSrv::Release() {
	T_ERROR_VAL(_busEngine->Release() == 0)
	T_ERROR_VAL(_eventEngine->Release() == 0)

	delete this;
	return 0;
}

int GateSrv::Activate() {
	T_ERROR_VAL(_busEngine->Activate() == 0)
	return 0;
}

int GateSrv::Initialize(void *arg, int arglen) {
	T_ERROR_VAL(_modManager.Initialize((void*)SERVICE_PATH,
					strlen(SERVICE_PATH)) == 0)
	_eventEngine = (IEventEngine*) _modManager.LoadModule("IOEngine");
	T_ERROR_VAL(_eventEngine)
	T_ERROR_VAL(_eventEngine->Initialize(NULL, 0) == 0);
	T_ERROR_VAL(_eventEngine->CreateListener(ServerIP, port + 1, new SessionManager()) == 0)

	_busEngine = (IBusEngine*) _modManager.LoadModule("BusEngine");
	T_ERROR_VAL(_busEngine)
	T_ERROR_VAL(_busEngine->Initialize(NULL, 0) == 0)

	_portToGameSrv = _busEngine->CreateClientNodePort(addr, slefID, bufLen,
			nodeIDBufLen);
	T_ERROR_VAL(_portToGameSrv)
	T_ERROR_VAL(_portToGameSrv->AddPortSink(new GamePortSink()) == 0)

	int32_t portFd;
	void *pPortFd = static_cast<void*> (&portFd);
	size_t portFdSize = sizeof(portFd);
	size_t *pPortFdSize = &portFdSize;
	T_ERROR_VAL(_portToGameSrv->GetPortOpt(ZMQ_FD, pPortFd , pPortFdSize) == 0)
	T_ERROR_VAL(portFd > 0)
	T_ERROR_VAL(_eventEngine->AddEvent(portFd, EV_READ|EV_PERSIST, NULL, NULL))

	return 0;
}

