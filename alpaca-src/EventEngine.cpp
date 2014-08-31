/*
 * EventEngine.cpp
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#include "EventEngine.h"
#include "EventCallback.h"
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <assert.h>

namespace alpaca {
EventEngine::EventEngine() :
	_manager(NULL), _evlistener(NULL), _evbase(NULL) , _cycle(0){
}

EventEngine::~EventEngine() {
}

int EventEngine::Initialize(void* arg, int arglen) {
    if(arg == NULL || arglen != sizeof(St_EvEngineInitParam)){
        SET_ERR_MSG(_lastErrMsg, "init param");
        return -1;
    }

    St_EvEngineInitParam* pParam = static_cast<St_EvEngineInitParam*>(arg);
    _cycle = pParam->cycle;
    assert(_cycle > 0);

	struct event_config* config = event_config_new();
	if (!config) {
		SET_ERR_MSG(_lastErrMsg, "allocate event_config failed");
		return -1;
	}

	if (event_config_avoid_method(config, "select")
			|| event_config_require_features(config, EV_FEATURE_O1)
			|| event_config_set_flag(config, EVENT_BASE_FLAG_NOLOCK)) {
		SET_ERR_MSG(_lastErrMsg, "set event_config failed");
		return -1;
	}

	_evbase = event_base_new_with_config(config);
	if (!_evbase) {
		SET_ERR_MSG(_lastErrMsg, "allocate event_base failed");
		return -1;
	}

	event_config_free(config);

	return 0;
}

int EventEngine::CreateListener(const char* ip, short port,
		IOHandler* iohandler) {
	struct sockaddr_in sockaddr;
	int socklen = sizeof(sockaddr);
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip, &sockaddr.sin_addr) == 0) //1 for succ, 0 for failure
	{
		SET_ERR_MSG	(_lastErrMsg, "set sockaddr failed" << strerror(errno))
		return -1;
	}

	_manager = iohandler;

	_evlistener = evconnlistener_new_bind(_evbase,
		accept_conn_cb, _manager, LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, 1024, (struct sockaddr*)&sockaddr, socklen);
	if(!_evlistener)
	{
		SET_ERR_MSG(_lastErrMsg, "allocate listener failed")
		return -1;
	}

	evconnlistener_set_error_cb(_evlistener, accept_conn_error_cb);
	return 0;
}

int EventEngine::Activate() {
    struct timeval tv;
    tv.tv_sec = _cycle / 1000;
    tv.tv_usec = (_cycle % 1000) * 1000;
	event_base_loopexit(_evbase, &tv);
    return event_base_dispatch(_evbase);
}

int EventEngine::Release() {
	event_base_loopbreak(_evbase);
	event_base_free(_evbase);
	evconnlistener_free(_evlistener);
	return 0;
}

int EventEngine::AddEvent(int fd, int flags, event_callback_fn fn, void* arg) {
	if (fd < 0 || fn == NULL) {
		return -1;
	}

	struct event *ev = event_new(_evbase, fd, flags, fn,
	           arg);

	if (!ev)
	{
		return -1;
	}

	event_add(ev, NULL);
	return 0;
}
}
