/*
 * MsgCoder.cpp
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */

#include "MsgCoder.h"
#include <limits.h>
#include <arpa/inet.h>
#include <string.h>

namespace alpaca {
MsgCoder::MsgCoder() {
}

MsgCoder::~MsgCoder() {
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

int MsgCoder::DecodeMsgBody(uint32_t& msgID,
		char*& buf, int& bufLen) {
	uint16_t packLen;
	if (DecodeUShort(packLen, buf, bufLen))
		return -1;
	if (DecodeUInt(msgID, buf, bufLen))
		return -2;

	return 0 ;
}

int MsgCoder::EncodeInt(int32_t value, char *& buf, int & bufLen) {
	if (bufLen < (int) sizeof(int32_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "encode int failed, bufLen:" << bufLen);
		return -1;
	}

	int32_t tmp = htonl(value);
	memcpy(buf, &tmp, sizeof(tmp));

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::DecodeInt(int32_t & value, char *& buf, int & bufLen) {
	if (bufLen < (int) sizeof(int32_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "decode int failed, bufLen:" << bufLen);
		return -1;
	}

	int32_t tmp;
	memcpy(&tmp, buf, sizeof(tmp));
	value = ntohl(tmp);

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::EncodeUInt(uint32_t value, char*& buf, int& bufLen) {
	if (bufLen < (int) sizeof(uint32_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "encode uint failed, bufLen:" << bufLen);
		return -1;
	}

	uint32_t tmp = htonl(value);
	memcpy(buf, &tmp, sizeof(tmp));

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::DecodeUInt(uint32_t& value, char*& buf, int& bufLen) {
	if (bufLen < (int) sizeof(uint32_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "decode uint failed, bufLen:" << bufLen);
		return -1;
	}

	uint32_t tmp;
	memcpy(&tmp, buf, sizeof(tmp));
	value = ntohl(tmp);

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::EncodeUShort(uint16_t value, char*& buf, int& bufLen) {
	if (bufLen < (int) sizeof(uint32_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "encode short failed, bufLen:" << bufLen);
		return -1;
	}

	uint16_t tmp = htons(value);
	memcpy(buf, &tmp, sizeof(tmp));

	buf += sizeof(uint16_t);
	bufLen -= sizeof(uint16_t);
	return 0;
}

int MsgCoder::DecodeUShort(uint16_t& value, char*& buf, int& bufLen) {
	if (bufLen < (int) sizeof(uint16_t) || buf == NULL) {
		SET_ERR_MSG(_lastErrMsg, "decode short failed, bufLen:" << bufLen);
		return -1;
	}

	uint16_t tmp;
	memcpy(&tmp, buf, sizeof(tmp));
	value = ntohs(tmp);

	buf += sizeof(uint16_t);
	bufLen -= sizeof(uint16_t);
	return 0;
}
}
