/*
 * SessionHandler.cpp
 *
 *  Created on: 2014-4-19
 *      Author: marv
 */

#include "SessionHandler.h"
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <errno.h>
#include "EventCallback.h"

SessionHandler::SessionHandler() {
	// TODO Auto-generated constructor stub

}

SessionHandler::~SessionHandler() {
	// TODO Auto-generated destructor stub
}


int SessionHandler::OnAcceptConn(struct evconnlistener* event_listener,
		int sock, struct sockaddr *addr, int len)
{
	struct event_base* base = evconnlistener_get_base(event_listener);
	struct bufferevent *bev = bufferevent_socket_new(
			base, sock, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(bev, bufevent_read_cb, bufevent_write_cb,
			bufevent_event_cb, this);

	bufferevent_enable(bev, EV_READ|EV_WRITE);
	return 0;
}


int SessionHandler::OnAcceptErr(struct evconnlistener* event_listener,
		int sock)
{
	int err = EVUTIL_SOCKET_ERROR();
	return err;
}


int SessionHandler::OnRecvData(struct bufferevent* bev)
{

	struct evbuffer* input = bufferevent_get_input(bev);
	char buf[1024];
	int n;

	while((n = evbuffer_remove(input, buf, sizeof(buf))) > 0){
		printf("%s\n", buf);
	}
	return -1;
}


int SessionHandler::OnConnClosed(struct bufferevent* bev)
{
	return 0;
}


int SessionHandler::OnSendData(struct bufferevent* bev)
{
	return 0;
}

int SessionHandler::OnEvent(struct bufferevent* bev, short event)
{
	return 0;
}
