/*
 * LogEngine.cpp
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#include "LogEngine.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;

void SignalHandler(const char* data, int size)
{
	LOG(ERROR) << string(data, size) << endl;
}

LogEngine::LogEngine() {
	// TODO Auto-generated constructor stub

}

LogEngine::~LogEngine() {
	// TODO Auto-generated destructor stub
	google::ShutdownGoogleLogging();
}


int LogEngine::Initialize(const char* app, const char* logDir)
{
	if(access(logDir, F_OK))
	{
		cout << "LogDir "<< logDir << "  not exist ";
		mkdir(logDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	google::InitGoogleLogging(app);

	char tmp[256];
	snprintf(tmp, sizeof(tmp), "%s%s", logDir, "/INFO");
	google::SetLogDestination(google::INFO, tmp);

	snprintf(tmp, sizeof(tmp), "%s%s", logDir, "/ERROR");
	google::SetLogDestination(google::ERROR, tmp);

	//FLAGS_logbufsecs = 0;
	FLAGS_max_log_size = 10;  //shift log file when size > 10m
	FLAGS_stop_logging_if_full_disk = true;
	FLAGS_alsologtostderr = true;

	google::InstallFailureSignalHandler();
	google::InstallFailureWriter(SignalHandler);
	return 0;
}
