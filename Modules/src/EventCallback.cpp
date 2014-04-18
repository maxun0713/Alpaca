/*
 * EventCallback.cpp
 *
 *  Created on: 2014楠�锟�4锟斤拷锟�18锟斤拷锟�
 *      Author: marv
 */

#include "EventCallback.h"
#include "IOHandler.h"


void
accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr)
{
//	if(listener)
//	{
//		struct event_base *base = evconnlistener_get_base(listener);
//		IOHandler* handler = static_cast<IOHandler*>(ptr);
		IOHandler* handler = static_cast<IOHandler*>(ptr);
		if(handler)  handler->OnAcceptConn(listener, sock, addr, len);
//	}
}


void
accept_conn_error_cb(struct evconnlistener *listener, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnAcceptErr(evconnlistener_get_fd(listener));
}


void
bufevent_read_cb(struct bufferevent* bev, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnRecvData();
}

void
bufevent_write_cb(struct bufferevent* bev, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnSendData();
}

void
bufevent_event_cb(struct bufferevent* bev, short event, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnRecvData();
}
