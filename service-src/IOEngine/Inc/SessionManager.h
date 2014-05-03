/*
 * SessionManager.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_

#include "IOHandler.h"
#include <map>
#include <event2/bufferevent.h>
#include <string.h>
using namespace std;

struct ClientSession
{
	int    fd;
	struct bufferevent* bev;
	time_t timestamp;
	char addr_p[16];

	ClientSession():fd(-1),bev(NULL),timestamp(0)
	{
		memset(addr_p, 0, sizeof(addr_p));
	}
	~ClientSession()
	{
		bufferevent_free(bev);
	}
};

typedef struct ClientSession CLIENT_SESSION;
typedef map<int, CLIENT_SESSION*> CLIENT_SESSION_MAP;
typedef CLIENT_SESSION_MAP::iterator CLIENT_SESSION_MAP_ITER;
class SessionManager: public IOHandler{
public:
	SessionManager();
	virtual ~SessionManager();

	int virtual OnAcceptConn(struct evconnlistener* event_listener, int sock, struct sockaddr *addr, int len);
	int virtual OnAcceptErr(struct evconnlistener* event_listener,int sock);
	int virtual OnRecvData(struct bufferevent* bev);
	int virtual OnConnClosed(struct bufferevent* bev);
	int virtual OnEventErr(struct bufferevent* bev);
public:
	int AddClientSession(int fd, struct bufferevent* bev, struct sockaddr *addr, int len);
	int RemoveClientSession(int fd);

	int virtual SendData(struct bufferevent* bev, char* data, int len);

private:
	CLIENT_SESSION_MAP   _sessionMap;
};

#endif /* SESSIONMANAGER_H_ */
