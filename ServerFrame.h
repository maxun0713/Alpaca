/*
 * ServerFrame.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef SERVERFRAME_H_
#define SERVERFRAME_H_

#include "IServer.h"
#include "ModuleManager.h"
class ServerFrame:public IServer {
public:
	ServerFrame();
	virtual ~ServerFrame();

	int virtual OnTimer(void* arg);
	SERVER_STATUS virtual OnProc(void* arg);

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release();
private:
	ModuleManager  _modManager;
};

#endif /* SERVERFRAME_H_ */
