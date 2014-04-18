/*
 * IOHandler.h
 *
 *  Created on: 2014年4月18日
 *      Author: marv
 */

#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <sys/socket.h>
class IOHandler {
public:
	IOHandler();
	virtual ~IOHandler();

	int virtual OnAcceptConn(int sock, struct sockaddr *addr, int len)=0;
	int virtual OnAcceptErr(int sock)=0;
	int virtual OnRecvData()=0;
	int virtual OnConnClosed()=0;
	int virtual OnSendData()=0;
};

#endif /* IOHANDLER_H_ */
