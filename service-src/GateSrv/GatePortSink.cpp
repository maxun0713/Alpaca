/*
 * GatePortSink.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */
#include "GatePortSink.h"
#include <iostream>
using namespace std;

GatePortSink::GatePortSink()
{
}



GatePortSink::~GatePortSink()
{
}



void GatePortSink::OnRecv(const char* peerNode, void* data, size_t dataLen)
{
	cout << data << endl;
}
