/*
 * GatePortSink.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */
#include "GatePortSink.h"
#include "BusEngine/Inc/IBusEngine.h"
#include <iostream>
#include <string.h>
using namespace bus;
using namespace std;

GatePortSink::GatePortSink()
{
}



GatePortSink::~GatePortSink()
{
}



void GatePortSink::OnRecv(const char *peerNode, void *data, size_t dataLen)
{
	cout << peerNode[0] << peerNode[1] << peerNode[2] << endl;
}
