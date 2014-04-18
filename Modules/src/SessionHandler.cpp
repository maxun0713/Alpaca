/*
 * SessionHandler.cpp
 *
 *  Created on: 2014-4-19
 *      Author: marv
 */

#include "SessionHandler.h"

SessionHandler::SessionHandler() {
	// TODO Auto-generated constructor stub

}

SessionHandler::~SessionHandler() {
	// TODO Auto-generated destructor stub
}


int SessionHandler::OnAcceptConn(struct evconnlistener* event_listener,
		int sock, struct sockaddr *addr, int len)
{
	return 0;
}


int SessionHandler::OnAcceptErr(int sock)
{
	return -1;
}


int SessionHandler::OnRecvData()
{
	return -1;
}


int SessionHandler::OnConnClosed()
{
	return 0;
}


int SessionHandler::OnSendData()
{
	return 0;
}
