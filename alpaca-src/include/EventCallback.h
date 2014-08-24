/*
 * EventCallback.h
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#ifndef EVENTCALLBACK_H_
#define EVENTCALLBACK_H_

#include <event2/util.h>
#include <event2/event.h>
#include <event2/listener.h>

void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t sock,
		struct sockaddr *addr, int len, void *ptr);

void accept_conn_error_cb(struct evconnlistener *listener, void* ctx);

void bufevent_read_cb(struct bufferevent* bev, void* ctx);

void bufevent_write_cb(struct bufferevent* bev, void* ctx);

void bufevent_event_cb(struct bufferevent* bev, short event, void* ctx);

#endif /* EVENTCALLBACK_H_ */
