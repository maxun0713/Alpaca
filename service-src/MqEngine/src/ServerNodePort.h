/*
 * ServerNodePort.h
 *
 *  Created on: Jul 2, 2014
 *      Author: marv
 */

#ifndef SERVERNODEPORT_H_
#define SERVERNODEPORT_H_

#include "IBusEngine.h"
#include <set>

using namespace bus;
using namespace std;

class ServerNode;
class ServerNodePort: public IServerPortSink {
public:
	ServerNodePort();
	virtual ~ServerNodePort();

	int AddPortSink(IServerPortSink* sink);
	int RemovePortSink(IServerPortSink* sink);

	int Initialize(const NodeInitParam& params);

	void virtual OnRecv(const char* peerNode, void* data, size_t dataLen);
private:
	ServerNode*  _servNode;
	set<IServerPortSink*> _portSinkSet;
};

#endif /* SERVERNODEPORT_H_ */
