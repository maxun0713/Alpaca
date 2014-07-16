/*
 * BusEngine.h
 *
 *  Created on: Jul 3, 2014
 *      Author: marv
 */

#ifndef BUSENGINE_H_
#define BUSENGINE_H_

#include "IModule.h"
#include "IBusEngine.h"
#include <set>

using namespace bus;
using namespace std;
class BusEngine : public IBusEngine {
public:
	BusEngine();
	virtual ~BusEngine();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;

	virtual INodePort* CreateServerNodePort(const char* addr, const char* identity,
			size_t dataBufLen, size_t peerIdBufLen) ;
	virtual INodePort* CreateClientNodePort(const char* addr, const char* identity,
			size_t dataBufLen, size_t peerIdBufLen) ;

	virtual int Schedule(bool onlyServer) ;

	const char* GetLastErrMsg();

private:
	void*   _zmqContext;
	set<INodePort*>  _srvNodePortSet;
	set<INodePort*>  _cliNodePortSet;
	LastErrMsg  _lastErrMsg;
};

#endif /* BUSENGINE_H_ */
