/*
 * GameSrv.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef GAMESRV_H_
#define GAMESRV_H_

#include "IServer.h"
#include "IGameSrv.h"
#include "ModuleManager.h"



namespace bus {
   class IBusEngine;
};

class GameSrv: public IGameSrv
{
public:
	GameSrv();
	virtual ~GameSrv();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;

	uint64_t virtual OnTimer() ;
	SERVER_STATUS virtual OnProc(void* arg);
private:
	ModuleManager   _modManager;
	bus::IBusEngine*  _busEngine;

};

#endif /* GAMESRV_H_ */
