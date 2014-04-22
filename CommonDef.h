/*
 * CommonDef.h
 *
 *  Created on: 2014年4月17日
 *      Author: marv
 */

#ifndef COMMONDEF_H_
#define COMMONDEF_H_

#include "LogEngine.h"


#define T_ASSERT(cond, opt) if(!(cond)) \
		{\
			LOG_ERROR(#cond) ;  \
			opt; \
		}
#define T_ASSERT_WITH_ERR_INFO(cond, opt) if(!(cond)) \
		{\
			PLOG(ERROR) << (#cond) ;  \
			opt; \
		}
#define T_ERROR_VAL(cond) T_ASSERT(cond, return -1)
#define T_ERROR_PTR(cond) T_ASSERT(cond, return NULL)
#define T_ERROR_VOID(cond) T_ASSERT(cond, return)
#define T_ERROR_VAL_WITH_ERR_INFO(cond)  T_ASSERT_WITH_ERR_INFO(cond, return -1)
#define T_ERROR_PTR_WITH_ERR_INFO(cond)  T_ASSERT_WITH_ERR_INFO(cond, return NULL)
#define T_ERROR_VOID_WITH_ERR_INFO(cond)  T_ASSERT_WITH_ERR_INFO(cond, return )





#endif /* COMMONDEF_H_ */
