/*
 * IGameSrv.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef IGAMESRV_H_
#define IGAMESRV_H_

class IServer;
class IGameSrv:public IServer
{
	public:
	IGameSrv() {};
	virtual ~IGameSrv(){};

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	uint64_t virtual OnTimer() = 0;
	SERVER_STATUS virtual OnProc(void* arg)= 0;
};

#endif /* IGAMESRV_H_ */
