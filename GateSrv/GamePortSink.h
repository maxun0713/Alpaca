/*
 * GamePortSink.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef GatePORTSINK_H_
#define GatePORTSINK_H_

#include "IBusEngine.h"

using namespace alpaca;

class GamePortSink:public IPortSink
{
public:
	GamePortSink();
	virtual ~GamePortSink();

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);
};











#endif
