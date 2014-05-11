/*
 * Node.h
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#ifndef NODE_H_
#define NODE_H_

#include "LastErrMsg.h"


struct NodeInitParam {
    const char* addr;  //server node addr;
    const char* identity; //self identity
    void*       context;  //zmq context
};

class Node
{
public:
    Node();
    virtual ~Node();

    virtual int Initialize(const NodeInitParam& params) = 0;

    const char* What();
protected:
    LastErrMsg _lasgErrMsg;
    void*      _socket;
};

#endif /* NODE_H_ */
