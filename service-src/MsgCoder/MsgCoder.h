/*
 * MsgCoder.h
 *
 *  Created on: 2014年4月27日
 *      Author: marv
 */

#ifndef MSGCODER_H_
#define MSGCODER_H_

#include "BaseMsgCoder.h"
#include <google/protobuf/message.h>

class MsgCoder: public BaseMsgCoder {
public:
	MsgCoder();
	virtual ~MsgCoder();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	int EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg,
			char*&buf, int& bufLen);
	int DecodeMsgBody(uint32_t& msgID, google::protobuf::Message* msg,
			char*&buf, int& bufLen);

private:
	LastErrMsg _lastErrMsg;

};

#endif /* MSGCODER_H_ */
