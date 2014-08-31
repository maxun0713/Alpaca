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

namespace alpaca {
class MsgCoder {
public:
	MsgCoder();
	virtual ~MsgCoder();

	int EncodeInt(int32_t value, char*& buf, int& bufLen);
	int DecodeInt(int32_t& value, char*& buf, int& bufLen);

	int EncodeUInt(uint32_t value, char*& buf, int& bufLen);
	int DecodeUInt(uint32_t& value, char*& buf, int& bufLen);

	int EncodeUShort(uint16_t value, char*& buf, int& bufLen);
	int DecodeUShort(uint16_t& value, char*& buf, int& bufLen);

	int EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg,
			char*&buf, int& bufLen);
	int DecodeMsgBody(uint32_t& msgID,
			char*&buf, int& bufLen);

private:
	LastErrMsg _lastErrMsg;

};

}
#endif /* MSGCODER_H_ */
