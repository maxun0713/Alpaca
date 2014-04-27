/*
 * SessionManager.cpp
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#include "SessionManager.h"
#include "LogEngine.h"
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <errno.h>
#include "LogEngine.h"
#include "EventCallback.h"

#define SIMPLE_BEV_CHECK if(!bev) {\
	LOG_ERROR("bufferevent null error");\
	return -1;\
}

SessionManager::SessionManager() {
	// TODO Auto-generated constructor stub

}

SessionManager::~SessionManager() {
	// TODO Auto-generated destructor stub
	CLIENT_SESSION_MAP_ITER iter = _sessionMap.begin();
	for(; iter!= _sessionMap.end(); iter++)
	{
		if(iter->second)
		{
			delete iter->second;
		}
	}
}


int SessionManager::SendData(struct bufferevent* bev, char* data, int len){
	SIMPLE_BEV_CHECK
	return bufferevent_write(bev, data, len);
}

int SessionManager::AddClientSession(int fd, struct bufferevent* bev, struct sockaddr *addr, int len)
{
	SIMPLE_BEV_CHECK

	CLIENT_SESSION_MAP_ITER iter = _sessionMap.find(fd);
	if(iter == _sessionMap.end())
	{
		CLIENT_SESSION* client = new CLIENT_SESSION();
		client->fd = fd;
		client->bev = bev;
		client->timestamp = time(NULL);
		_sessionMap.insert(make_pair(fd, client));

		struct sockaddr_in* paddr = (struct sockaddr_in*)addr;
		inet_ntop(AF_INET, (void*)&paddr->sin_addr, client->addr_p, sizeof(client->addr_p));
		LOG_INFO("Accept new connection from " << client->addr_p<< " sockfd: " << fd
			<< ", " << _sessionMap.size() << " client(s) in total");
		return 0;
	}
	else
	{
		LOG_ERROR("AddClientSession failed, duplicate fd" << fd);
		return -1;
	}
}


int SessionManager::RemoveClientSession(int fd)
{
	CLIENT_SESSION_MAP_ITER iter = _sessionMap.find(fd);
	if(iter ==_sessionMap.end())
	{
		LOG_ERROR("Remove Client Session failed, client fd" << fd);
		return -1;
	}

	CLIENT_SESSION* session = iter->second;
	_sessionMap.erase(iter);
	if(session)
	{
		LOG_INFO("End connection from " << session->addr_p << " sockfd: " << fd
				<< ", " << _sessionMap.size() << " client(s) in total");
		delete session;
	}

	return 0;
}


int SessionManager::OnAcceptConn(struct evconnlistener* event_listener,
		int sock, struct sockaddr *addr, int len)
{

	struct event_base* base = evconnlistener_get_base(event_listener);
	struct bufferevent *bev = bufferevent_socket_new(
			base, sock, BEV_OPT_CLOSE_ON_FREE);
	SIMPLE_BEV_CHECK

	//not need to set write callback
	bufferevent_setcb(bev, bufevent_read_cb, NULL,
			bufevent_event_cb, this);

	//short for msg header len
	bufferevent_setwatermark(bev, EV_READ, sizeof(short), 0);
	bufferevent_setwatermark(bev, EV_WRITE, sizeof(short), 0);

	bufferevent_enable(bev, EV_READ|EV_WRITE);

	int fd = bufferevent_getfd(bev);
	return AddClientSession(fd, bev, addr, len);
}


int SessionManager::OnAcceptErr(struct evconnlistener* event_listener,
		int sock)
{
	int err = EVUTIL_SOCKET_ERROR();
	LOG_ERROR("accept new connection failed" << strerror(err));
	return err;
}


int SessionManager::OnRecvData(struct bufferevent* bev)
{
	SIMPLE_BEV_CHECK
	struct evbuffer* input = bufferevent_get_input(bev);
	char buf[1024];
	int n;

	while((n = evbuffer_remove(input, buf, sizeof(buf))) > 0){
		printf("%s\n", buf);
		bufferevent_write(bev, buf, n);
	}
	return -1;
}


int SessionManager::OnConnClosed(struct bufferevent* bev)
{
	int fd = bufferevent_getfd(bev);
	return RemoveClientSession(fd);
}


int SessionManager::OnEventErr(struct bufferevent* bev)
{
	SIMPLE_BEV_CHECK

	int fd = bufferevent_getfd(bev);
	LOG_ERROR("Got a error on socket(:" << fd << ") " << EVUTIL_SOCKET_ERROR());
	return RemoveClientSession(fd);

	return -1;
}
