/*
 * BusEngine.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: marv
 */

#include "BusEngine.h"
#include "ServerNodePort.h"
#include "ClientNodePort.h"
#include <zmq.h>

BusEngine::BusEngine() :
		_zmqContext(NULL) {
	// TODO Auto-generated constructor stub

}

BusEngine::~BusEngine() {
	// TODO Auto-generated destructor stub
}

int BusEngine::Initialize(void *arg, int arglen) {
	int ret = -1;
	void *context = zmq_ctx_new();

	if (context != NULL) {
		ret = 0;
		_zmqContext = context;
	}

	return ret;
}

INodePort* BusEngine::CreateServerNodePort(const char *addr,
		const char *identity, size_t dataBufLen, size_t peerIdBufLen) {
	NodeInitParam param;
	param.addr = addr;
	param.identity = identity;
	param.dataBufLen = dataBufLen;
	param.peerIdBufLen = peerIdBufLen;
	param.context = _zmqContext;

	ServerNodePort* p = new ServerNodePort();
	int ret = p->Initialize(&param, sizeof(param));
	if (ret != 0) {
		SET_ERR_MSG(_lastErrMsg, p->GetLastErrMsg())
		delete p;
		return 0;
	} else {
		_srvNodePortSet.insert(p);
		return p;
	}
}

INodePort* BusEngine::CreateClientNodePort(const char *addr,
		const char *identity, size_t dataBufLen, size_t peerIdBufLen) {
	NodeInitParam param;
	param.addr = addr;
	param.identity = identity;
	param.dataBufLen = dataBufLen;
	param.peerIdBufLen = peerIdBufLen;

	ClientNodePort* p = new ClientNodePort();
	int ret = p->Initialize(&param, sizeof(param));
	if (ret != 0) {
		SET_ERR_MSG(_lastErrMsg, p->GetLastErrMsg())
		return 0;
	} else {
		_srvNodePortSet.insert(p);
		return p;
	}
}

int BusEngine::Activate() {
	return 0;
}

int BusEngine::Release() {
	if (_zmqContext != NULL)
	{
		return zmq_ctx_destroy(_zmqContext);
	}

	set<INodePort*>::iterator itor = _srvNodePortSet.begin();
	for (; itor != _srvNodePortSet.end(); itor++) {
		delete *itor;
	}

	itor = _cliNodePortSet.begin();
	for (; itor != _srvNodePortSet.end(); itor++) {
		delete *itor;
	}

	return 0;
}

int BusEngine::Schedule(bool onlyServer) {
	set<INodePort*>::iterator itor = _srvNodePortSet.begin();
	for (; itor != _srvNodePortSet.end(); itor++) {
		(*itor)->Schedule(true);
	}

	if (!onlyServer) {
		itor = _cliNodePortSet.begin();
		for (; itor != _cliNodePortSet.end(); itor++) {
			(*itor)->Schedule(true);
		}
	}

	return 0;
}

const char* BusEngine::GetLastErrMsg() {
	return _lastErrMsg.What();
}

