/*
 * GatePortSink.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */
#include "GatePortSink.h"
#include "IBusEngine.h"
#include <iostream>
#include <string.h>
#include "MsgCoder.h"
#include "Message.pb.h"

using namespace std;

GatePortSink::GatePortSink() {
}

GatePortSink::~GatePortSink() {
}

void GatePortSink::OnRecv(const char *peerNode, void *data, size_t dataLen) {
	cout << "recv msg from " << peerNode << endl;
	uint32_t msgid = 99;
	char *pBuf = (char*)data;
	int bufLen = dataLen;
	MsgCoder coder;
	int iRet = coder.DecodeMsgBody(msgid , pBuf, bufLen);
	if (iRet == 0) {
		cout << msgid << endl;
	} else {
		cout << "decode failed" << endl;
	}

}
