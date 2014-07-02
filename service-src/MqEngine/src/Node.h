/*
 * Node.h
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#ifndef NODE_H_
#define NODE_H_

#include "LastErrMsg.h"
#include "IBusEngine.h"

using namespace bus;

class CNode
{
public:
    CNode();
    virtual ~CNode();

    virtual int Initialize(const NodeInitParam& params) = 0;

    const char* GetLastErrMsg();
    
    int Recv(char* peerNodeID, size_t& peerNodeIDBufLen, void* dataBuf,
             size_t& dataLen, bool noWait);

protected:
    int _Send(const char* peerNodeID, size_t peerNodeIDLen, const char* data,
              size_t dataLen);

	int _InitLocalData(const NodeInitParam& params);
protected:
    LastErrMsg _lastErrMsg;
    void*      _socket;

	void*	   _dataBuf;
	size_t     _dataBufLen;
	char*      _peerNodeIDBuf;
	size_t     _peerNodeIDBufLen;

	char*      _selfID;
	size_t     _selfIDLen;
};

#endif /* NODE_H_ */
