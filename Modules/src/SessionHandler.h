/*
 * SessionHandler.h
 *
 *  Created on: 2014-4-19
 *      Author: marv
 */

#ifndef SESSIONHANDLER_H_
#define SESSIONHANDLER_H_

#include "IOHandler.h"


class SessionHandler {
public:
	SessionHandler();
	virtual ~SessionHandler();

	int virtual OnAcceptConn(struct evconnlistener* event_listener, int sock, struct sockaddr *addr, int len);
	int virtual OnAcceptErr(int sock);
	int virtual OnRecvData();
	int virtual OnConnClosed();
	int virtual OnSendData();
};

#endif /* SESSIONHANDLER_H_ */
