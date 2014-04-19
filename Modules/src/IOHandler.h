/*
 * IOHandler.h
 *
 *  Created on: 2014
 *      Author: marv
 */

#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <sys/socket.h>

struct event_listener;
class IOHandler {
public:
	IOHandler(){};
	virtual ~IOHandler(){};

	int virtual OnAcceptConn(struct evconnlistener* event_listener, int sock, struct sockaddr *addr, int len)=0;
	int virtual OnAcceptErr(struct evconnlistener* event_listener, int sock)=0;
	int virtual OnRecvData(struct bufferevent* bev)=0;
	int virtual OnConnClosed(struct bufferevent* bev)=0;
	int virtual OnSendData(struct bufferevent* bev)=0;
	int virtual OnEvent(struct bufferevent* bev, short event)=0;
};

#endif /* IOHANDLER_H_ */
