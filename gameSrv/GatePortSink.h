/*
 * GatePortSink.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef GatePORTSINK_H_
#define GatePORTSINK_H_

#include "BusEngine.h"
using namespace alpaca;

class GatePortSink:public IPortSink
{
public:
	GatePortSink();
	virtual ~GatePortSink();

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);
};











#endif
