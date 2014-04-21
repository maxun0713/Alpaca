/*
 * IServer.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef ISERVER_H_
#define ISERVER_H_

#include "IModule.h"

class IServer :public IModule{
public:
	IServer(){};
	virtual ~IServer(){};

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	int virtual OnTimer(void* arg) = 0;
	int virtual OnProc(void* arg)= 0;
};

#endif /* ISERVER_H_ */
