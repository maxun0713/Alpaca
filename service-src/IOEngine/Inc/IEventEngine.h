/*
 * IEventEngine.h
 *
 *  Created on: 2014年5月4日
 *      Author: marv
 */

#ifndef IEVENTENGINE_H_
#define IEVENTENGINE_H_


class IOHandler;
class IModule;
class IEventEngine : public IModule{
public:
	virtual ~IEventEngine() {}

	virtual int Initialize(void* arg, int arglen) = 0;
	virtual int Activate() = 0;
	virtual int Release() = 0;

	virtual int CreateListener(const char* ip, short port, IOHandler* iohandler) = 0;

	virtual struct bufferevent* AddEvent(int fd, IOHandler* iohandler) = 0;
};



#endif /* IEVENTENGINE_H_ */
