/*
 * ServerNode.cpp
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#include "ServerNode.h"
#include <zmq.h>
#include <string.h>

ServerNode::ServerNode()
{
    // TODO Auto-generated constructor stub

}

ServerNode::~ServerNode()
{
    // TODO Auto-generated destructor stub
}

int ServerNode::Initialize(const NodeInitParam& params)
{
    if(params.addr == NULL ||
            params.context == NULL ||
            params.identity == NULL)
    {
        SET_ERR_MSG(_lasgErrMsg, "initial params error")
        return -1;
    }

    int error;
    int ret;
    int linger = 0;
    long lingerLen = sizeof(linger);
    _socket = zmq_socket(params.context, ZMQ_ROUTER);
    if(NULL == _socket)
    {
        error = zmq_errno();
        SET_ERR_MSG(_lasgErrMsg, "create zmq socket failed :"
                << zmq_strerror(error))
        return -1;
    }

    ret = zmq_setsockopt(_socket, ZMQ_IDENTITY, params.identity,
            strlen(params.identity));
    if(ret != 0)
    {
        error = zmq_errno();
        SET_ERR_MSG(_lasgErrMsg, "set zmq socket opt failed :"
                << zmq_strerror(error))
        return -1;
    }

    ret = zmq_setsockopt(_socket, ZMQ_LINGER, &linger, lingerLen);
    if(ret != 0)
    {
        error = zmq_errno();
        SET_ERR_MSG(_lasgErrMsg, "set zmq socket opt failed :"
                << zmq_strerror(error))
        return -1;
    }

    return 0;
}
