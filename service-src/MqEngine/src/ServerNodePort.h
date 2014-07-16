/*
 * ServerNodePort.h
 *
 *  Created on: Jul 2, 2014
 *      Author: marv
 */

#ifndef SERVERNODEPORT_H_
#define SERVERNODEPORT_H_

#include "IBusEngine.h"
#include "LastErrMsg.h"
#include "ServerNode.h"
#include <set>

using namespace bus;
using namespace std;

class ServerNodePort: public INodePort {
public:
	ServerNodePort();
	virtual ~ServerNodePort();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	virtual int AddPortSink(IPortSink* sink);
	virtual int RemovePortSink(IPortSink* sink);

	virtual int Schedule(bool noWait);

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);

	virtual int Send(const char* peerNodeID, const char* data, size_t dataLen);

	const char* GetLastErrMsg();
private:
	ServerNode _node;
	set<IPortSink*> _portSinkSet;
	LastErrMsg _lastErrMsg;
};

#endif /* SERVERNODEPORT_H_ */
