/*
 * ClientNodePort.h
 *
 *  Created on: Jul 15, 2014
 *      Author: marv
 */

#ifndef CLIENTNODEPORT_H_
#define CLIENTNODEPORT_H_

#include "IBusEngine.h"
#include "LastErrMsg.h"
#include "ClientNode.h"
#include <set>

namespace alpaca {
using namespace std;

class ClientNodePort : public INodePort{
public:
	ClientNodePort();
	virtual ~ClientNodePort();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	virtual int AddPortSink(IPortSink* sink);
	virtual int RemovePortSink(IPortSink* sink);

	virtual int Schedule(bool noWait);

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);

	virtual int Send(const char* peerNodeID, const char* data, size_t dataLen);

	const char* GetLastErrMsg();

	virtual int GetPortOpt(int option_name, void *&option_value, size_t *&option_len);
private:
	ClientNode _node;
	set<IPortSink*> _portSinkSet;
	LastErrMsg _lastErrMsg;
};

}

#endif /* CLIENTNODEPORT_H_ */
