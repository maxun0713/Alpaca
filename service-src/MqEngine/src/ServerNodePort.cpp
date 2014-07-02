/*
 * ServerNodePort.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: marv
 */

#include "ServerNodePort.h"

ServerNodePort::ServerNodePort()
{
	// TODO Auto-generated constructor stub

}

ServerNodePort::~ServerNodePort()
{
	// TODO Auto-generated destructor stub
}

void ServerNodePort::OnRecv(const char* peerNode, void* data, size_t dataLen)
{
	set<IServerPortSink*>::iterator itor =  _portSinkSet.begin();
	for (; itor != _portSinkSet.end(); itor ++)
	{
		(*itor)->OnRecv(peerNode, data, dataLen);
	}
}
