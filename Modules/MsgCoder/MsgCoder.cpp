/*
 * MsgCoder.cpp
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */

#include "MsgCoder.h"
#include <arpa/inet.h>
#include <limits.h>

MsgCoder::MsgCoder() {
	// TODO Auto-generated constructor stub

}

MsgCoder::~MsgCoder() {
	// TODO Auto-generated destructor stub
}



int MsgCoder::EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg,
		char*& buf, int& bufLen) {
	if(buf == NULL || bufLen < int(sizeof(uint16_t) + sizeof(uint32_t) )
			|| msg == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "encode msg failed, bufLen:" <<
				bufLen << ",msgID " << msgID);
		return -1;
	}

	int msgLen = msg->ByteSize();
	int bufLenNeed = msgLen + sizeof(uint16_t) + sizeof(uint32_t);
	bool succ;
	if(bufLenNeed  > SHRT_MAX || bufLenNeed > bufLen)
	{
		SET_ERR_MSG(_lastErrMsg, "encode msg failed, bufLen:" <<
				bufLen << ", need " << bufLenNeed);
		return -1;
	}

	if(EncodeShort(bufLenNeed, buf, bufLen)) return -1;
	if(EncodeInt(msgID, buf, bufLen)) return -1;
	succ = msg->SerializeToArray(buf, bufLen);

	return succ ? 0 : -1;
}



int MsgCoder::DecodeMsgBody(uint32_t& msgID,
		google::protobuf::Message*& msg, char*& buf, int& bufLen) {
	uint16_t packLen;
	if(DecodeShort(packLen, buf, bufLen)) return -1;
	if(DecodeInt(msgID, buf, bufLen)) return -1;

	msg = (google::protobuf::Message* )buf;

	return 0;
}

int MsgCoder::EncodeInt(uint32_t value, char*& buf, int& bufLen) {
	if(bufLen < (int)sizeof(uint32_t) || buf == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "encode int failed, bufLen:" << bufLen);
		return -1;
	}

	uint32_t tmp = htonl(value);
	memcpy(buf, &tmp, sizeof(tmp));

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::DecodeInt(uint32_t& value, char*& buf, int& bufLen) {
	if(bufLen < (int)sizeof(uint32_t) || buf == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "decode int failed, bufLen:" << bufLen);
		return -1;
	}

	uint32_t tmp;
	memcpy(&tmp, buf, sizeof(tmp));
	value = ntohl(tmp);

	buf += sizeof(uint32_t);
	bufLen -= sizeof(uint32_t);
	return 0;
}

int MsgCoder::EncodeShort(uint16_t value, char*& buf, int& bufLen) {
	if(bufLen < (int)sizeof(uint32_t) || buf == NULL)
	{
		SET_ERR_MSG(_lastErrMsg, "encode short failed, bufLen:" << bufLen);
		return -1;
	}

	uint16_t tmp = htons(value);
	memcpy(buf, &tmp, sizeof(tmp));

	buf += sizeof(uint16_t);
	bufLen -= sizeof(uint16_t);
	return 0;
}

int MsgCoder::DecodeShort(uint16_t& value, char*& buf, int& bufLen) {
	if(bufLen < (int)sizeof(uint16_t) || buf == NULL)
	{
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
