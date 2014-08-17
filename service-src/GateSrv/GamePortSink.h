/*
 * GamePortSink.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef GatePORTSINK_H_
#define GatePORTSINK_H_

#include "BusEngine/Inc/IBusEngine.h"

using namespace bus;

class GamePortSink:public bus::IPortSink
{
public:
	GamePortSink();
	virtual ~GamePortSink();

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);
};











#endif
