/*
 * GateServer.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef GATESERVER_H_
#define GATESERVER_H_

#include "IServer.h"
#include "IGateSrv.h"
#include "ModuleManager.h"

class IEventEngine;

namespace bus {
   class IBusEngine;
};


class GateSrv :public IGateSrv{
public:
	GateSrv();
	virtual ~GateSrv();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;

	uint64_t virtual OnTimer() ;
	SERVER_STATUS virtual OnProc(void* arg);
private:
	IEventEngine*   _eventEngine;
	bus::IBusEngine*     _busEngine;
	ModuleManager   _modManager;
};

#endif /* GATESERVER_H_ */
