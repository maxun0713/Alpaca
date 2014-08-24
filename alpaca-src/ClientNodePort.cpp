/*
 * ClientNodePort.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: marv
 */

#include "ClientNodePort.h"
#include <string.h>

namespace alpaca {
ClientNodePort::ClientNodePort() {
	// TODO Auto-generated constructor stub

}

ClientNodePort::~ClientNodePort() {
	// TODO Auto-generated destructor stub
}

int ClientNodePort::RemovePortSink(IPortSink *sink)
{
	int iRet = -1;

	if (sink == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "port sink null")
		return iRet;
	}

	set<IPortSink*>::iterator itor = _portSinkSet.find(sink);
	if (itor != _portSinkSet.end())
	{
		_portSinkSet.erase(itor);
		iRet = 0;
	}

	return iRet;
}

int ClientNodePort::AddPortSink(IPortSink *sink)
{
	int iRet = -1;
	if (sink == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "port sink null")
		return iRet;
	}

	_portSinkSet.insert(sink);
	return 0;
}

int ClientNodePort::Send(const char *peerNodeID, const char *data, size_t dataLen)
{
	int iRet = -1;

	if (peerNodeID == NULL || data == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "parameter error" << peerNodeID << "|" << data)
		return iRet;
	}

	iRet = _node.Send(peerNodeID, strlen(peerNodeID), data, dataLen);
	if (iRet != 0)
	{
		SET_ERR_MSG(_lastErrMsg, _node.GetLastErrMsg())
	}

	return iRet;
}



int ClientNodePort::Release()
{
	set<IPortSink*>::iterator itor;
	IPortSink* sink;
	for (itor = _portSinkSet.begin(); itor != _portSinkSet.end(); itor++)
	{
		sink = *itor;
		delete sink;
	}

	delete this;
	return 0;
}


int ClientNodePort::Initialize(void *arg, int arglen)
{
	int iRet = -1;
	if (arg == NULL || arglen != sizeof(NodeInitParam) )
	{
		SET_ERR_MSG(_lastErrMsg, "parameter error")
		return iRet;
	}

	const NodeInitParam*  p = (NodeInitParam*)arg;
	iRet =  _node.Initialize(*p);
	if (iRet != 0)
	{
		SET_ERR_MSG(_lastErrMsg, _node.GetLastErrMsg());
		return iRet;
	}

	_node.SetNodePort(this);
	return iRet;
}


void ClientNodePort::OnRecv(const char *peerNode, void *data, size_t dataLen)
{
	set<IPortSink*>::iterator itor;
	for (itor = _portSinkSet.begin(); itor != _portSinkSet.end(); itor++)
	{
		(*itor)->OnRecv(peerNode, data, dataLen);
	}

}

const char* ClientNodePort::GetLastErrMsg()
{
	return _lastErrMsg.What();
}


int ClientNodePort::Activate()
{
	return 0;
}


int ClientNodePort::Schedule(bool noWait)
{
	int iRet = _node.Schedule(noWait);
	if (iRet < 0)
	{
		SET_ERR_MSG(_lastErrMsg, _node.GetLastErrMsg());
	}

	return iRet;
}


int ClientNodePort::GetPortOpt(int option_name, void *&option_value, size_t *&option_len)
{
	return _node.GetNodeOpt(option_name, option_value, option_len);
}

}
