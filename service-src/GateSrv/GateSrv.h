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
class IMsgCoder;

namespace bus {
   class IBusEngine;
   class INodePort;
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

	int HeartBeat();
private:
	ModuleManager        _modManager;

	IEventEngine*        _eventEngine;

	bus::IBusEngine*     _busEngine;
	bus::INodePort*      _portToGameSrv;
	time_t               _lastConnTime;

	IMsgCoder*           _msgCoder;
};

#endif /* GATESERVER_H_ */
