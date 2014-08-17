/*
 * MsgCoder.cpp
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */

#include "MsgCoder.h"
#include <limits.h>

MsgCoder::MsgCoder() {
}

MsgCoder::~MsgCoder() {
	// TODO Auto-generated destructor stub
}

int MsgCoder::Initialize(void *arg, int arglen) {
	return 0;
}

int MsgCoder::Activate() {
	return 0;
}

int MsgCoder::Release() {
	delete this;
	return 0;
}

int MsgCoder::EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg,
		char*& buf, int& bufLen) {
	if (buf == NULL || bufLen < int(sizeof(uint16_t) + sizeof(uint32_t)) || msg
			== NULL) {
		SET_ERR_MSG(_lastErrMsg, "encode msg failed, bufLen:" << bufLen
				<< ",msgID " << msgID);
		return -1;
	}

	int msgLen = msg->ByteSize();
	int bufLenNeed = msgLen + sizeof(uint16_t) + sizeof(uint32_t);
	bool succ;
	if (bufLenNeed > SHRT_MAX || bufLenNeed > bufLen) {
		SET_ERR_MSG(_lastErrMsg, "encode msg failed, bufLen:" << bufLen
				<< ", need " << bufLenNeed);
		return -1;
	}

	if (EncodeUShort(bufLenNeed, buf, bufLen))
		return -1;
	if (EncodeUInt(msgID, buf, bufLen))
		return -1;
	succ = msg->SerializeToArray(buf, bufLen);
	bufLen = bufLenNeed;
	return succ ? 0 : -1;
}

int MsgCoder::DecodeMsgBody(uint32_t& msgID, google::protobuf::Message* msg,
		char*& buf, int& bufLen) {
	uint16_t packLen;
	if (DecodeUShort(packLen, buf, bufLen))
		return -1;
	if (DecodeUInt(msgID, buf, bufLen))
		return -2;

	bool succ = msg->ParseFromArray(buf, bufLen);

	return succ ? 0 : -3;
}
