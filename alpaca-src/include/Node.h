/*
 * Node.h
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#ifndef NODE_H_
#define NODE_H_

#include "IBusEngine.h"
#include "LastErrMsg.h"

namespace alpaca {

class CNode {
public:
	CNode();
	virtual ~CNode();

	virtual int Initialize(const NodeInitParam& params) = 0;

	const char* GetLastErrMsg();

	int Recv(char* peerNodeID, size_t& peerNodeIDBufLen, void* dataBuf,
			size_t& dataLen, bool noWait);

	int Send(const char* peerNodeID, size_t peerNodeIDLen, const char* data,
			size_t dataLen);

	int Schedule(bool noWait);

	int SetNodePort(INodePort* port);

	int GetNodeOpt(int option_name, void *&option_value, size_t *&option_len);
protected:
	int _InitLocalData(const NodeInitParam& params);

protected:
	LastErrMsg _lastErrMsg;
	void* _socket;

	void* _dataBuf;
	size_t _dataBufLen;
	char* _peerNodeIDBuf;
	size_t _peerNodeIDBufLen;

	char* _selfID;
	size_t _selfIDLen;

	INodePort* _nodePort;
};
}
#endif /* NODE_H_ */
