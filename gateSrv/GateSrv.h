/*
 * GateServer.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef GATESERVER_H_
#define GATESERVER_H_

#include "IServer.h"
#include "ModuleManager.h"
#include "EventEngine.h"
#include "BusEngine.h"

using namespace alpaca;


class GateSrv: public IServer {
public:
	GateSrv();
	virtual ~GateSrv();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	uint64_t virtual OnTimer();
	SERVER_STATUS virtual OnProc(void* arg);

	int HeartBeat();
private:
	ModuleManager _modManager;

	EventEngine* _eventEngine;

	BusEngine* _busEngine;
	INodePort* _portToGameSrv;
	time_t _lastConnTime;
};

#endif /* GATESERVER_H_ */
