/*
 * IGateSrv.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef IGATESRV_H_
#define IGATESRV_H_

class IServer;

class IGateSrv: public IServer {
public:
	IGateSrv() {};
	virtual ~IGateSrv(){};

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	uint64_t virtual OnTimer() = 0;
	SERVER_STATUS virtual OnProc(void* arg)= 0;
};

#endif /* IGATESRV_H_ */
