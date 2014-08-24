/*
 * IOHandler.h
 *
 *  Created on: 2014
 *      Author: marv
 */

#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <sys/socket.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

namespace alpaca {
class IOHandler {
public:
	IOHandler(){};
	virtual ~IOHandler(){};

	int virtual OnAcceptConn(struct evconnlistener* event_listener, int sock, struct sockaddr *addr, int len)=0;
	int virtual OnAcceptErr(struct evconnlistener* event_listener, int sock)=0;
	int virtual OnRecvData(struct bufferevent* bev)=0;
	int virtual OnConnClosed(struct bufferevent* bev)=0;
	int virtual OnEventErr(struct bufferevent* bev)=0;
};

}
#endif /* IOHANDLER_H_ */
