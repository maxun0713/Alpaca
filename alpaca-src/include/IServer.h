/*
 * IServer.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef ISERVER_H_
#define ISERVER_H_

#include "IModule.h"
#include "CoreTypes.h"
#include <stdint.h>

namespace alpaca {

class IServer :public IModule{
public:
	IServer():_status(SERVER_STATUS_SHUTDOWN){};
	virtual ~IServer(){};

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	uint64_t virtual OnTimer() = 0;
	SERVER_STATUS virtual OnProc(void* arg)= 0;
protected:
	SERVER_STATUS _status;
};

}
#endif /* ISERVER_H_ */
