/*
 * EventEngine.h
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#ifndef EVENTENGINE_H_
#define EVENTENGINE_H_

#include <event2/util.h>
#include <event2/event.h>
#include "IModule.h"
#include "IOHandler.h"

namespace alpaca {

typedef struct {
    time_t   cycle;
} St_EvEngineInitParam;

class EventEngine: public IModule {
public:
	EventEngine();
	virtual ~EventEngine();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	virtual int
			CreateListener(const char* ip, short port, IOHandler* iohandler);

	virtual int AddEvent(int fd, int flags, event_callback_fn fn, void* arg);

private:
	IOHandler* _manager;
	struct evconnlistener* _evlistener;
	struct event_base* _evbase;

    time_t  _cycle;

};
}
#endif /* EVENTENGINE_H_ */
