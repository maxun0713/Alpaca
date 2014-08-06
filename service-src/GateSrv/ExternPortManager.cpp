/*
 * BusIoManager.cpp
 *
 *  Created on: Aug 7, 2014
 *      Author: marv
 */

#include "ExternPortManager.h"
#include "BusEngine/Inc/IBusEngine.h"

using namespace bus;

ExternPortManager::ExternPortManager(bus::IBusEngine *busEngine, bool onlyServer) :
	_busEngine(busEngine), _onlyServer(onlyServer) {
}

ExternPortManager::~ExternPortManager() {
}

int ExternPortManager::OnAcceptConn(struct evconnlistener* event_listener,
		int sock, struct sockaddr *addr, int len) {
	return 0;
}

int ExternPortManager::OnAcceptErr(struct evconnlistener* event_listener,
		int sock) {
	return 0;
}

int ExternPortManager::OnRecvData(struct bufferevent* bev) {
	if (_busEngine)
	{
		return _busEngine->Schedule(_onlyServer);
	}
}

int ExternPortManager::OnConnClosed(struct bufferevent* bev) {
	return 0;
}

int ExternPortManager::OnEventErr(struct bufferevent* bev) {
	return 0;
}
