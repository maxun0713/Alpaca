/*
 * LogEngine.h
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#ifndef LOGENGINE_H_
#define LOGENGINE_H_

#include <glog/logging.h>

class LogEngine {
public:
	LogEngine();
	virtual ~LogEngine();

	int Initialize(const char* app, const char* logDir);
};

#endif /* LOGENGINE_H_ */
