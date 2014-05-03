/*
 * GateServer.h
 *
 *  Created on: 2014年5月3日
 *      Author: marv
 */

#ifndef GATESERVER_H_
#define GATESERVER_H_

#include "IServer.h"
#include "ModuleManager.h"

class EventEngine;
class GateServer:public IServer {
public:
	GateServer();
	virtual ~GateServer();

	uint64_t virtual OnTimer();
	SERVER_STATUS virtual OnProc(void* arg);

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release();
private:
	ModuleManager  _modManager;
	EventEngine*    _engine;
};

#endif /* GATESERVER_H_ */
