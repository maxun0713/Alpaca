/*
 * GatePortSink.h
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */

#ifndef GATEPORTSINK_H_
#define GATEPORTSINK_H_

namespace bus {
class INodePortSink;
}

class GatePortSink :public bus::INodePortSink
{
public:
	GatePortSink();
	virtual ~GatePortSink();

	virtual void OnRecv(const char* peerNode, void* data, size_t dataLen);
};









#endif
