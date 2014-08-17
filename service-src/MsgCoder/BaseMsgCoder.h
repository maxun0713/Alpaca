/*
 * BaseMsgCoder.h
 *
 *  Created on: Aug 17, 2014
 *      Author: marv
 */

#ifndef BASEMSGCODER_H_
#define BASEMSGCODER_H_

#include "IModule.h"
#include "Inc/IMsgCoder.h"
#include "LastErrMsg.h"

class BaseMsgCoder {
public:
	BaseMsgCoder();
	virtual ~BaseMsgCoder();

	int EncodeInt(int32_t value, char*& buf, int& bufLen);
	int DecodeInt(int32_t& value, char*& buf, int& bufLen);

	int EncodeUInt(uint32_t value, char*& buf, int& bufLen);
	int DecodeUInt(uint32_t& value, char*& buf, int& bufLen);

	int EncodeUShort(uint16_t value, char*& buf, int& bufLen);
	int DecodeUShort(uint16_t& value, char*& buf, int& bufLen);

protected:

	LastErrMsg _lastErrMsg;

};

#endif /* BASEMSGCODER_H_ */
