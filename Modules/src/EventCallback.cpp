/*
 * EventCallback.cpp
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#include "EventCallback.h"
#include "IOHandler.h"

void
accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr)
{
	IOHandler* handler = static_cast<IOHandler*>(ptr);
	if(handler)  handler->OnAcceptConn(sock, addr, len);
}


void
accept_conn_error_cb(struct evconnlistener *listener, void* ctx)
{
	IOHandler* handler = static_cast<IOHandler*>(ctx);
	if(handler) handler->OnAcceptErr(evconnlistener_get_fd(listener));
}
