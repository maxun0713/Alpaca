/*
 * LogEngine.h
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#ifndef LOGENGINE_H_
#define LOGENGINE_H_

#include <glog/logging.h>



#define LOG_INFO(what)     LOG(INFO)  << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|" <<what
#define LOG_WARNING(what)  LOG(WARN)  << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|" <<what
#define LOG_ERROR(what)    LOG(ERROR) << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|" <<what
#define LOG_FATAL(what)    LOG(FATAL) << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|" <<what
#define LOG_PERROR(what)   PLOG(ERROR) << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|" <<what

namespace alpaca {
class LogEngine {
public:
	LogEngine();
	virtual ~LogEngine();

	int Initialize(const char* app, const char* logDir);
};
}
#endif /* LOGENGINE_H_ */
