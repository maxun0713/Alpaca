/*
 * IModule.h
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#ifndef IMODULE_H_
#define IMODULE_H_

#include "LastErrMsg.h"

class IModule {
public:
	IModule(){};
	virtual ~IModule(){};

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	const char* GetLastErrMsg() { return _lastErrMsg.What(); }
protected:
	LastErrMsg  _lastErrMsg;
};

#endif /* IMODULE_H_ */
