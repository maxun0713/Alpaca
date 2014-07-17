/*
 * AppFrame.h
 *
 *  Created on: Jul 18, 2014
 *      Author: marv
 */

#ifndef APPFRAME_H_
#define APPFRAME_H_

#include "IModule.h"
#include "ModuleManager.h"
#include "IServer.h"

class AppFrame : public IModule{
public:
	AppFrame();
	virtual ~AppFrame();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;

	virtual int Run();

private:
	ModuleManager  _modMgr;
	IServer* 	   _appMod;
};

#endif /* APPFRAME_H_ */
