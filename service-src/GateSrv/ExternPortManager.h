/*
 * ExternPortManager
 *
 *  Created on: Aug 7, 2014
 *      Author: marv
 */

#ifndef EXTERNPORTMANAGER_H_
#define EXTERNPORTMANAGER_H_

#include "IOEngine/Inc/IOHandler.h"
#include <map>
#include <event2/bufferevent.h>
#include <string.h>

using namespace std;

namespace bus {
class IBusEngine;
};


class ExternPortManager : public IOHandler
{
public:
	ExternPortManager(bus::IBusEngine *busEngine, bool onlyServer);
	virtual ~ExternPortManager();

	int virtual OnAcceptConn(struct evconnlistener* event_listener, int sock,
			struct sockaddr *addr, int len);
	int virtual OnAcceptErr(struct evconnlistener* event_listener, int sock);
	int virtual OnRecvData(struct bufferevent* bev);
	int virtual OnConnClosed(struct bufferevent* bev);
	int virtual OnEventErr(struct bufferevent* bev);

private:
	bus::IBusEngine  *_busEngine;
	bool              _onlyServer;
};







#endif
