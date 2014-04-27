/*
 * MsgCoder.h
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */

#ifndef MSGCODER_H_
#define MSGCODER_H_

#include "LastErrMsg.h"
#include <google/protobuf/message.h>

class MsgCoder {
public:
	MsgCoder();
	virtual ~MsgCoder();

	int EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg, char*&buf, int& bufLen);
	int DecodeMsgBody(uint32_t& msgID, google::protobuf::Message*& msg, char*&buf, int& bufLen);

	int EncodeInt(uint32_t value, char*& buf, int& bufLen);
	int DecodeInt(uint32_t& value, char*& buf, int& bufLen);

	int EncodeShort(uint16_t value, char*& buf, int& bufLen);
	int DecodeShort(uint16_t& value, char*& buf, int& bufLen);

private:
	LastErrMsg _lastErrMsg;

};


#endif /* MSGCODER_H_ */
