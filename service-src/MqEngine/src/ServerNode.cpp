/*
 * ServerNode.cpp
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#include "ServerNode.h"
#include <string.h>

#define ERR_QUIT(op) \
        int error = zmq_errno(); \
        SET_ERR_MSG(_lasgErrMsg, op \
                << zmq_strerror(error))\
        \
        return -1;\


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

    int ret;
    int linger = 0;
    long lingerLen = sizeof(linger);
    int mandatory = 1;
    long mandatoryLen = sizeof(mandatory);
    _socket = zmq_socket(params.context, ZMQ_ROUTER);
    if(NULL == _socket)
    {
        ERR_QUIT("create zmq socket ")
    }

    ret = zmq_setsockopt(_socket, ZMQ_IDENTITY, params.identity,
            strlen(params.identity));
    if(ret != 0)
    {
        ERR_QUIT("set zmq socket opt ")
    }

    ret = zmq_setsockopt(_socket, ZMQ_LINGER, &linger, lingerLen);
    if(ret != 0)
    {
        ERR_QUIT("set zmq socket opt ")
    }

    ret = zmq_setsockopt(_socket, ZMQ_ROUTER_MANDATORY, &mandatory, mandatoryLen);
    if(ret != 0)
    {
        ERR_QUIT("set zmq socket opt ")
    }

    return 0;
}

int ServerNode::Recv(char* peerIDBuf, int& peerIDBufLen, void* buf, int& bufLen)
{
    zmq_msg_t remote;
    zmq_msg_t delimiter;
    zmq_msg_t body;
    int ret,more;
    size_t moreLen = sizeof(more);
    int dataLen;

    zmq_msg_init(&remote);
    ret = zmq_msg_recv(&remote, _socket, ZMQ_DONTWAIT);
    if(ret != 0)
    {
        ERR_QUIT("recv msg ")
    }

    cout << (char*)zmq_msg_data(&remote) << endl;
    cout << zmq_msg_size(&remote) << endl;
    zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
    if(!more)
    {
      SET_ERR_MSG(_lasgErrMsg, "invalid msg format1")
      zmq_msg_close(&remote);
      return -1;
    }

    dataLen = zmq_msg_size(&remote);
    if(dataLen > peerIDBufLen-1)
    {
        SET_ERR_MSG(_lasgErrMsg, "peerIDBuf not enough")
        zmq_msg_close(&remote);
        return -1;
    }
    memcpy(peerIDBuf, (char*)zmq_msg_data(&remote), dataLen);
    peerIDBuf[dataLen] = '\0';

    zmq_msg_init(&delimiter);
    ret = zmq_msg_recv(&delimiter, _socket, ZMQ_DONTWAIT);
    if(ret != 0)
    {
        ERR_QUIT("recv msg ")
    }
    cout << (char*)zmq_msg_data(&delimiter) << endl;
    cout << zmq_msg_size(&delimiter) << endl;
    zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
    if(!more)
    {
      SET_ERR_MSG(_lasgErrMsg, "invalid msg format2")
      zmq_msg_close(&remote);
      zmq_msg_close(&delimiter);
      return -1;
    }

    zmq_msg_init(&body);
    ret = zmq_msg_recv(&body, _socket, ZMQ_DONTWAIT);
    if(ret != 0)
    {
        ERR_QUIT("recv msg ")
    }

    cout << (char*)zmq_msg_data(&body) << endl;
    cout << zmq_msg_size(&body) << endl;
    zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
    if(more)
    {
      SET_ERR_MSG(_lasgErrMsg, "invalid msg format3")
      zmq_msg_close(&remote);
      zmq_msg_close(&delimiter);
      zmq_msg_close(&body);
      return -1;
    }
    dataLen = zmq_msg_size(&body);
    if(dataLen < bufLen -1)
    {
        SET_ERR_MSG(_lasgErrMsg, "data buf not enough")
        zmq_msg_close(&remote);
        zmq_msg_close(&delimiter);
        zmq_msg_close(&body);
        return -1;
    }
    memcpy(buf, zmq_msg_data(&body),dataLen);

    zmq_msg_close(&remote);
    zmq_msg_close(&delimiter);
    zmq_msg_close(&body);
    return 0;
}

int ServerNode::Send(const char* peerID, int peerIDLen, void* data, int dataLen)
{
    if(NULL == peerID )
    {
        SET_ERR_MSG(_lasgErrMsg, "peerID is NULL")
        return -1;
    }

    int ret;
    zmq_msg_t delimiter;

    ret = zmq_send(_socket, peerID, peerIDLen, ZMQ_SNDMORE|ZMQ_DONTWAIT);
    if(ret)
    {
        ERR_QUIT("send msg ")
    }

    zmq_msg_init_size(&delimiter, 0);
    ret = zmq_msg_send(&delimiter, _socket, ZMQ_SNDMORE|ZMQ_DONTWAIT);
    if(ret)
    {
        ERR_QUIT("send msg ")
    }

    ret = zmq_send(_socket, data, dataLen, ZMQ_DONTWAIT);
    if(ret)
    {
        ERR_QUIT("send msg ")
    }

    return 0;
}
