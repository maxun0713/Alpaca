/*
 * ServerFrame.cpp
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#include "ServerFrame.h"
#include "DefaultConfig.h"
ServerFrame::ServerFrame():_modManager(FRAME_SERVICE_PATH) {
	// TODO Auto-generated constructor stub
}

ServerFrame::~ServerFrame() {
	// TODO Auto-generated destructor stub
}

uint64_t ServerFrame::OnTimer()
{
	sleep(1);
	return 0;
}


SERVER_STATUS ServerFrame::OnProc(void* arg)
{
	_engine.Activate();
	return SERVER_STATUS_PAUSED;
}


int ServerFrame::Initialize(void* arg, int arglen)
{
	_engine.Initialize(NULL, 0);
	_engine.CreateListener("127.0.0.1", 27017, (IOHandler*)&_mgr);
	return 0;
}


int ServerFrame::Activate()
{

	return 0;
}


int ServerFrame::Release()
{
	return 0;
}
