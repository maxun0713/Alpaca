/*
 * ServerNode.cpp
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#include "ServerNode.h"
#include <string.h>
#include <zmq.h>

namespace alpaca {
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
	if (params.addr == NULL ||
		params.context == NULL ||
		params.identity == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "initial params error")
		return -1;
	}

	int ret;
	_socket = zmq_socket(params.context, ZMQ_ROUTER);
	if (NULL == _socket)
	{
		SET_ERR_MSG(_lastErrMsg, "create zmq socket ")
		return -1;
	}

	ret = zmq_setsockopt(_socket, ZMQ_IDENTITY, params.identity,
		strlen(params.identity));
	if (ret != 0)
	{
		SET_ERR_MSG(_lastErrMsg,"set zmq socket identity ")
		return -1;
	}

	ret = zmq_bind(_socket, params.addr);
	if (ret != 0)
	{
		SET_ERR_MSG(_lastErrMsg, "bind zmq socket")
		return -1;
	}

	return _InitLocalData(params);
}

}
