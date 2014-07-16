/*
 * Node.cpp
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#include "Node.h"
#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CNode::CNode() :
		_socket(NULL), _dataBuf(NULL), _dataBufLen(0), _peerNodeIDBuf(NULL),
		_peerNodeIDBufLen(0), _selfID(NULL), _selfIDLen(0), _nodePort(NULL) {
	// TODO Auto-generated constructor stub
}

CNode::~CNode() {
	if (_socket != NULL) {
		zmq_close(_socket);
		_socket = NULL;
	}

	if (_dataBuf != NULL) {
		free(_dataBuf);
		_dataBuf = NULL;
	}

	if (_peerNodeIDBuf != NULL) {
		free(_peerNodeIDBuf);
		_peerNodeIDBuf = NULL;
	}

	if (_selfID != NULL) {
		free(_selfID);
		_selfID = NULL;
	}
}

const char* CNode::GetLastErrMsg() {
	return _lastErrMsg.What();
}

int CNode::Recv(char *peerNodeID, size_t &peerNodeIDBufLen, void *dataBuf,
		size_t &dataLen, bool noWait) {
	zmq_msg_t zmsg;
	int flags = noWait ? ZMQ_DONTWAIT : 0;
	int ret = zmq_msg_init(&zmsg);
	if (ret != 0) {
		SET_ERR_MSG(_lastErrMsg, "init zmq msg failed")
		zmq_msg_close(&zmsg);
		return ret;
	}

	ret = zmq_msg_recv(&zmsg, _socket, flags);
	if (ret < 0) {
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg,
					"recv peer node id failed:" << strerror(errno))
		} else {
			zmq_msg_close(&zmsg);
			return 1;
		}
		zmq_msg_close(&zmsg);
		return ret;
	}

	const size_t peerNodeIDSize = zmq_msg_size(&zmsg);
	if (peerNodeIDSize + 1 > peerNodeIDBufLen) {
		SET_ERR_MSG(_lastErrMsg, "peer node buffer to short")
		return -1;
	}

	memcpy(peerNodeID, zmq_msg_data(&zmsg), peerNodeIDSize);
	peerNodeID[peerNodeIDSize] = '\0';
	peerNodeIDBufLen = peerNodeIDSize;

	int more;
	size_t moreLen = sizeof(more);

	zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
	if (0 == more) {
		SET_ERR_MSG(_lastErrMsg, "no more msg part")
		return -1;
	}

	ret = zmq_msg_init(&zmsg);
	if (ret != 0) {
		SET_ERR_MSG(_lastErrMsg, "init zmq msg failed")
		zmq_msg_close(&zmsg);
		return ret;
	}

	ret = zmq_msg_recv(&zmsg, _socket, flags);
	if (ret < 0) {
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg,
					"recv delimiter failed:" << strerror(errno))
		}
		zmq_msg_close(&zmsg);
		return ret;
	}

	if (zmq_msg_size(&zmsg) != 0) {
		SET_ERR_MSG(_lastErrMsg, "delimiter not empty")
		return -1;
	}

	zmq_msg_close(&zmsg);

	zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
	if (0 == more) {
		SET_ERR_MSG(_lastErrMsg, "no data msg part")
		return -1;
	}

	int bytes = zmq_recv(_socket, dataBuf, dataLen, flags);
	if (bytes < 0) {
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg, "recv data msg failed:" << strerror(errno))
		}
		return -1;
	}

	zmq_getsockopt(_socket, ZMQ_RCVMORE, &more, &moreLen);
	if (more != 0) {
		SET_ERR_MSG(_lastErrMsg, "invalid msg part")
		return -1;
	}

	dataLen = bytes;
	return 0;
}

int CNode::Send(const char *peerNodeID, size_t peerNodeIDLen, const char *data,
		size_t dataLen) {
	int ret = zmq_send(_socket, peerNodeID, peerNodeIDLen,
	ZMQ_DONTWAIT | ZMQ_SNDMORE);
	if (ret < 0) //identity should not be empty
			{
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg, "send peer node id failed");
		}
		return ret;
	}

	zmq_msg_t zmsg;
	ret = zmq_msg_init_size(&zmsg, 0);
	if (ret != 0) {
		SET_ERR_MSG(_lastErrMsg, "init delimiter msg failed!")
		zmq_msg_close(&zmsg);
		return -1;
	}

	ret = zmq_msg_send(&zmsg, _socket, ZMQ_DONTWAIT | ZMQ_SNDMORE);
	if (ret < 0) //empty delimiter
			{
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg,
					"send delimiter msg failed!" << strerror(errno))
		}
		zmq_msg_close(&zmsg);
		return ret;
	}
	zmq_msg_close(&zmsg);

	ret = zmq_send(_socket, data, dataLen, ZMQ_DONTWAIT);
	if (ret < 0) {
		if (errno != EAGAIN) {
			SET_ERR_MSG(_lastErrMsg, "send data msg failed!" << strerror(errno))
		}
		return ret;
	}

	return 0;
}

int CNode::Schedule(bool noWait) {
	int iRet = -1;
	size_t nodeIdBufLen = _peerNodeIDBufLen;
	size_t dataBufLen = _dataBufLen;
	iRet = Recv(_peerNodeIDBuf, nodeIdBufLen, _dataBuf, dataBufLen, noWait);

	if (iRet == 0 && _nodePort != NULL) {
		_nodePort->OnRecv(_peerNodeIDBuf, _dataBuf, dataBufLen);
	}

	return iRet;
}

int CNode::SetNodePort(INodePort *port) {
	if (port == NULL) {
		return -1;
	}

	_nodePort = port;
	return 0;
}

int CNode::_InitLocalData(const NodeInitParam& params) {
	_dataBufLen =
			params.dataBufLen > DEFAULT_NODE_DATA_BUF_LEN_MIN ?
					params.dataBufLen : DEFAULT_NODE_DATA_BUF_LEN;
	_dataBuf = malloc(_dataBufLen);
	if (_dataBuf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "malloc data buf :" << _dataBufLen)
		return -1;
	}

	_peerNodeIDBufLen =
			params.peerIdBufLen > DEFAULT_NODE_ID_BUF_LEN_MIN ?
					params.peerIdBufLen : DEFAULT_NODE_ID_BUF_LEN;
	_peerNodeIDBuf = static_cast<char*>(malloc(_peerNodeIDBufLen));
	if (_peerNodeIDBuf == NULL) {
		SET_ERR_MSG(_lastErrMsg,
				"malloc peer node id buf :" << _peerNodeIDBufLen)
		return -1;
	}

	_selfID = strdup(params.identity);
	_selfIDLen = strlen(_selfID);

	return 0;
}
