/*
 * IModule.h
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#ifndef IMODULE_H_
#define IMODULE_H_

class IModule {
public:
	IModule();
	virtual ~IModule();

	virtual int Create() = 0 ;
	virtual int Initialize(void* param) = 0;
	virtual int Release() = 0;
};

#endif /* IMODULE_H_ */
