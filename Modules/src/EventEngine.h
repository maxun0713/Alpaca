/*
 * EventEngine.h
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#ifndef EVENTENGINE_H_
#define EVENTENGINE_H_

#include "IModule.h"
#include "IOHandler.h"
#include <string>


struct evconnlistener;
struct event_base;
class EventEngine : public IModule{
public:
	EventEngine();
	virtual ~EventEngine();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	virtual int CreateListener(const char* ip, short port, IOHandler* iohandler);

private:
	struct evconnlistener*  _evlistener;
	struct event_base*		_evbase;
};

#endif /* EVENTENGINE_H_ */
