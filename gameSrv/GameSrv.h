/*
 * GameSrv.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef GAMESRV_H_
#define GAMESRV_H_

#include "IServer.h"
#include "ModuleManager.h"
#include "BusEngine.h"

using namespace alpaca;

class GameSrv: public IServer {
public:
	GameSrv();
	virtual ~GameSrv();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	uint64_t virtual OnTimer();
	SERVER_STATUS virtual OnProc(void* arg);

private:
	ModuleManager _modManager;
	IBusEngine* _busEngine;
	INodePort* _portForGate;

};

#endif /* GAMESRV_H_ */
