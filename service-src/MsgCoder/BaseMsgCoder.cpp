/*
 * BaseMsgCoder.cpp
 *
 *  Created on: Aug 17, 2014
 *      Author: marv
 */

#include "BaseMsgCoder.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

BaseMsgCoder::BaseMsgCoder() {

}

BaseMsgCoder::~BaseMsgCoder() {

}

int BaseMsgCoder::EncodeInt(int32_t value, char *& buf, int & bufLen) {
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

int BaseMsgCoder::DecodeInt(int32_t & value, char *& buf, int & bufLen) {
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

int BaseMsgCoder::EncodeUInt(uint32_t value, char*& buf, int& bufLen) {
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

int BaseMsgCoder::DecodeUInt(uint32_t& value, char*& buf, int& bufLen) {
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

int BaseMsgCoder::EncodeUShort(uint16_t value, char*& buf, int& bufLen) {
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



int BaseMsgCoder::DecodeUShort(uint16_t& value, char*& buf, int& bufLen) {
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
