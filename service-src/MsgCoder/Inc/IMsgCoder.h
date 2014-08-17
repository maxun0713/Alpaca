/*
 * IMsgCoder.h
 *
 *  Created on: Aug 17, 2014
 *      Author: marv
 */

#ifndef IMSGCODER_H_
#define IMSGCODER_H_

#include <stdint.h>

namespace google{
	namespace protobuf{
		class Message;
	}
};
class IModule;
class IMsgCoder: public IModule {
public:
	virtual ~IMsgCoder() {
	}

	virtual int EncodeInt(int32_t value, char*& buf, int& bufLen) = 0;
	virtual int DecodeInt(int32_t& value, char*& buf, int& bufLen) = 0;

	virtual int EncodeUInt(uint32_t value, char*& buf, int& bufLen) = 0;
	virtual int DecodeUInt(uint32_t& value, char*& buf, int& bufLen) = 0;

	virtual int EncodeUShort(uint16_t value, char*& buf, int& bufLen) = 0;
	virtual int DecodeUShort(uint16_t& value, char*& buf, int& bufLen) = 0;

	virtual int EncodeMsgBody(uint32_t msgID, google::protobuf::Message* msg,
			char*&buf, int& bufLen) = 0;
	virtual int DecodeMsgBody(uint32_t& msgID, google::protobuf::Message* msg,
			char*&buf, int& bufLen) = 0;
};

#endif /* IMSGCODER_H_ */
