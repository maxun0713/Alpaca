/*
 * ServerNodePort.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: marv
 */

#include "ServerNodePort.h"
#include <string.h>

ServerNodePort::ServerNodePort()
{
	// TODO Auto-generated constructor stub
}


ServerNodePort::~ServerNodePort()
{
	// TODO Auto-generated destructor stub
}

int ServerNodePort::RemovePortSink(IPortSink *sink)
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

int ServerNodePort::AddPortSink(IPortSink *sink)
{
	int iRet = -1;
	if (sink == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "port sink null")
		return iRet;
	}

	_portSinkSet.insert(sink);
	_node.SetNodePort(this);
	return 0;
}

int ServerNodePort::Send(const char *peerNodeID, const char *data, size_t dataLen)
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



int ServerNodePort::Release()
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


int ServerNodePort::Initialize(void *arg, int arglen)
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


void ServerNodePort::OnRecv(const char *peerNode, void *data, size_t dataLen)
{
	set<IPortSink*>::iterator itor;
	for (itor = _portSinkSet.begin(); itor != _portSinkSet.end(); itor++)
	{
		(*itor)->OnRecv(peerNode, data, dataLen);
	}

}

const char* ServerNodePort::GetLastErrMsg()
{
	return _lastErrMsg.What();
}


int ServerNodePort::Activate()
{
	return 0;
}


int ServerNodePort::Schedule(bool noWait)
{
	int iRet = _node.Schedule(noWait);
	if (iRet < 0)
	{
		SET_ERR_MSG(_lastErrMsg, _node.GetLastErrMsg());
	}

	return iRet;
}


