/*
 * EventCallback.cpp
 *
 *  Created on: 2014
 *      Author: marv
 */

#include "EventCallback.h"
#include "IOHandler.h"
#include <event2/bufferevent.h>

using namespace alpaca ;
void
accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr)
{
	IOHandler* handler = static_cast<IOHandler*>(ptr);
	if(handler)  handler->OnAcceptConn(listener, sock, addr, len);
}


void
accept_conn_error_cb(struct evconnlistener *listener, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnAcceptErr(listener, evconnlistener_get_fd(listener));
}


void
bufevent_read_cb(struct bufferevent* bev, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnRecvData(bev);
}

// temporary useless
void
bufevent_write_cb(struct bufferevent* bev, void* ctx)
{
//	IOHandler* handler = static_cast<IOHandler*>(ctx);
//	if(handler) handler->OnSendData(bev);
}

void
bufevent_event_cb(struct bufferevent* bev, short event, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);

	if(handler)
	{
		if(event & BEV_EVENT_EOF)
		{
			handler->OnConnClosed(bev);
		}
		else if(event & BEV_EVENT_ERROR)
		{
			handler->OnEventErr(bev);
		}
	}
}

