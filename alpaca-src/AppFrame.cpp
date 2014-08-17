/*
 * AppFrame.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: marv
 */

#include "AppFrame.h"
#include "CommonDef.h"
#include "DefaultConfig.h"

AppFrame::AppFrame() :
	_appMod(NULL) {
	// TODO Auto-generated constructor stub
}

AppFrame::~AppFrame() {
	// TODO Auto-generated destructor stub
}

int AppFrame::Initialize(void *arg, int arglen) {
	T_ERROR_VAL(_modMgr.Initialize((void*)FRAME_SERVICE_PATH, strlen(FRAME_SERVICE_PATH)) == 0)

	_appMod = static_cast<IServer*> (_modMgr.LoadModule(APP_MOD));
	T_ERROR_VAL(_appMod != NULL)

	T_ERROR_VAL(_appMod->Initialize(NULL, 0) == 0)
	return 0;
}

int AppFrame::Release() {
	T_ERROR_VAL(_modMgr.Release() == 0)
	T_ERROR_VAL(_appMod->Release() == 0)
	return 0;
}

int AppFrame::Activate() {
	T_ERROR_VAL(_modMgr.Activate() == 0)
	T_ERROR_VAL(_appMod->Activate() == 0)
	return 0;
}

int AppFrame::Run() {
	return _appMod->OnProc(NULL);
}

