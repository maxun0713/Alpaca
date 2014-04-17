/*
 * CommonDef.h
 *
 *  Created on: 2014年4月17日
 *      Author: marv
 */

#ifndef COMMONDEF_H_
#define COMMONDEF_H_

#include <glog/logging.h>

#ifndef RELEASE
#define T_ASSERT(cond, opt) if(!(cond)) \
		{\
			LOG_ERROR(#cond) ;  \
			opt; \
		}
#define T_ERROR_VAL(cond) T_ASSERT(cond, return -1)
#define T_ERROR_PTR(cond) T_ASSERT(cond, return NULL)
#define T_ERROR_VOID(cond) T_ASSERT(cond, return)

#else
#define T_ERROR_VAL(cond)
#define T_ERROR_PTR(cond)
#define T_ERROR_VOID(cond)
#endif



#endif /* COMMONDEF_H_ */
