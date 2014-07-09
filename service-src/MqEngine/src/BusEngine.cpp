/*
 * BusEngine.cpp
 *
 *  Created on: Jul 3, 2014
 *      Author: marv
 */

#include "BusEngine.h"

BusEngine::BusEngine() {
	// TODO Auto-generated constructor stub

}

BusEngine::~BusEngine() {
	// TODO Auto-generated destructor stub
}

int BusEngine::Initialize(void *arg, int arglen)
{
	return 0;
}



INodePort* BusEngine::CreateServerNodePort(const char *addr, const char *identity, size_t dataBufLen, size_t peerIdBufLen)
{
	return 0;
}



int BusEngine::Activate()
{
	return 0;
}



int BusEngine::Release()
{
	return 0;
}



INodePort* BusEngine::CreateClientNodePort(const char *addr, const char *identity, size_t dataBufLen, size_t peerIdBufLen)
{
	return NULL;
}



int BusEngine::Schedule(bool onlyServer)
{
	return 0;
}






