/*
 * IBusEngine.h
 *
 *  Created on: Jul 3, 2014
 *      Author: marv
 */

#ifndef IBUSENGINE_H_
#define IBUSENGINE_H_

#include "IModule.h"
#include <stdio.h>

namespace bus {
const size_t DEFAULT_NODE_DATA_BUF_LEN = 0x1000;
const size_t DEFAULT_NODE_DATA_BUF_LEN_MIN = 0x400;
const size_t DEFAULT_NODE_ID_BUF_LEN = 0x100;
const size_t DEFAULT_NODE_ID_BUF_LEN_MIN = 0x80;

struct NodeInitParam {
	const char* addr;  //server node addr;
	const char* identity; //self identity
	void* context;  //zmq context
	size_t dataBufLen;
	size_t peerIdBufLen;
};

class IPortSink {
public:
	virtual ~IPortSink() {
	}
	;

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen) = 0;
};

class INodePort {
public:
	virtual ~INodePort() {
	}
	;

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	virtual int AddPortSink(IPortSink* sink) = 0;
	virtual int RemovePortSink(IPortSink* sink) = 0;

	virtual int Schedule(bool noWait) = 0;

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen) = 0;

	virtual int Send(const char* peerNodeID, const char* data,
			size_t dataLen) = 0;

	virtual const char* GetLastErrMsg() = 0;

	virtual int GetPortOpt(int option_name, void *&option_value, size_t *&option_len) = 0;
};

class IBusEngine: public IModule {
public:
	virtual ~IBusEngine(){}

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	virtual INodePort* CreateServerNodePort(const char* addr,
			const char* identity, size_t dataBufLen, size_t peerIdBufLen) = 0;
	virtual INodePort* CreateClientNodePort(const char* addr,
			const char* identity, size_t dataBufLen, size_t peerIdBufLen) = 0;
	virtual int Schedule(bool onlyServer) = 0;
};

}

#endif /* IBUSENGINE_H_ */
