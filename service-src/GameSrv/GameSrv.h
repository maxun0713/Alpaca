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
#include "MsgCoder/Inc/IMsgCoder.h"

class IMsgCoder;
namespace bus {
class IBusEngine;
class INodePort;
}
;

class GameSrv: public IGameSrv {
public:
	GameSrv();
	virtual ~GameSrv();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	uint64_t virtual OnTimer();
	SERVER_STATUS virtual OnProc(void* arg);

	static IMsgCoder* _msgCoder;
private:
	ModuleManager _modManager;
	bus::IBusEngine* _busEngine;
	bus::INodePort* _portForGate;


};

#endif /* GAMESRV_H_ */
