/*
 * ServerNode.h
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#ifndef SERVERNODE_H_
#define SERVERNODE_H_

#include "Node.h"
#include <zmq.h>

class ServerNode: public Node
{
public:
    ServerNode();
    virtual ~ServerNode();

    int    Initialize(const NodeInitParam& params);

    int    Recv(char* peerIDBuf, int& peerIDBufLen, void* buf, int& bufLen);

    int    Send(const char* peerID, int peerIDLen, void* data, int dataLen);
};

#endif /* SERVERNODE_H_ */
