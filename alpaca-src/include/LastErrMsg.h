/*
 * LastErrMsg.h
 *
 *  Created on: 2014年4月17日
 *      Author: marv
 */

#ifndef LASTERRMSG_H_
#define LASTERRMSG_H_

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

namespace alpaca {
class LastErrMsg {
public:
	ostringstream _sstream;
	string _buf;

	LastErrMsg() {
	}
	;
	virtual ~LastErrMsg() {
	}
	;

	const char* What() {
		_buf = _sstream.str();
		return _buf.c_str();
	}

	void Clear() {
		_sstream.clear();
	}

};
}

#define SET_ERR_MSG(lasterrmsg, msg)   \
	do { \
		lasterrmsg.Clear(); \
		lasterrmsg._sstream << msg; \
		cout << lasterrmsg.What() << endl; \
	}while(0); \


#endif /* LASTERRMSG_H_ */
