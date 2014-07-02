//
//  ClientNode.cpp
//  mqengine
//
//  Created by marv on 14-6-29.
//  Copyright (c) 2014年 marv. All rights reserved.
//

#include "ClientNode.h"
#include <zmq.h>
#include <string.h>

ClientNode::ClientNode()
{
    
}

ClientNode::~ClientNode()
{
}


int ClientNode::Initialize(const NodeInitParam &params)
{
    if (params.addr == NULL ||
        params.context == NULL ||
        params.identity == NULL )
    {
        SET_ERR_MSG(_lastErrMsg, "initial params error")
        return -1;
    }
    
    int ret;
    _socket = zmq_socket(params.context, ZMQ_ROUTER);
    if (_socket == NULL)
    {
    	SET_ERR_MSG(_lastErrMsg, "create zmq socket")
    	return -1;
    }
    
    ret = zmq_setsockopt(_socket, ZMQ_IDENTITY, params.identity,
                         strlen(params.identity));
    if (ret != 0)
    {
    	SET_ERR_MSG(_lastErrMsg, "set zmq socket identity")
    	return -1;
    }
    
    ret = zmq_connect(_socket, params.addr);
    if (ret != 0)
    {
    	SET_ERR_MSG(_lastErrMsg, "zmq connect failed")
    	return -1;
    }
	
    return _InitLocalData(params);
}
