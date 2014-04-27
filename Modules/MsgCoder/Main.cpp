/*
 * Main.cpp
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */




#include "MsgCoder.h"
#include "test.pb.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main()
{
	MsgCoder coder;
	char buf[1024];
	char* pbuf = buf;
	int bufLen = sizeof(buf);
	int ret;
	uint32_t value, tmp = 100;
	TestMsg test;
	google::protobuf::Message* pMsg;
	bool succ;

	ret = coder.EncodeInt(tmp, pbuf, bufLen);
	pbuf = buf;
	bufLen = sizeof(buf);
	ret = coder.DecodeInt(value, pbuf, bufLen);

	pbuf = buf;
	bufLen = sizeof(buf);

	test.set_dumb(1);
	ret = coder.EncodeMsgBody(tmp, &test, pbuf, bufLen);

	test.Clear();
	pbuf = buf;
	bufLen = sizeof(buf);
	ret = coder.DecodeMsgBody(value, pMsg, pbuf, bufLen);
	succ = test.ParseFromArray(pMsg, bufLen);

	cout << test.dumb() << endl;

	return 0;
}
