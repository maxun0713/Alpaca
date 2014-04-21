/*
 * Util.h
 *
 *  Created on: 2014年4月17日
 *      Author: marv
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "CommonDef.h"
#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/file.h>
#include <signal.h>

int SavePid(const char* app)
{
	T_ERROR_VAL(app)

	pid_t pid = getpid();
	char tmp[64];
	snprintf(tmp, sizeof(tmp), "%s.pid", app);
	FILE *fp = fopen(tmp, "w");
	T_ERROR_VAL(fp)

	int n = snprintf(tmp, sizeof(tmp), "%d", pid);
	fwrite(tmp, sizeof(char), n, fp);
	fclose(fp);
	return 0;
}


int Deamonlize(int nochdir, int noclose)
{
	return daemon(nochdir, noclose);
}


int SetSystemParms()
{
	struct rlimit rlim_core;

	/* Soft limit */
	rlim_core.rlim_cur = RLIM_INFINITY;
	/* Hard limit (ceiling for rlim_cur) */
	rlim_core.rlim_max = RLIM_INFINITY;

	return setrlimit(RLIMIT_CORE, &rlim_core);
}


int Lock(const char* app)
{
	FILE* fp = NULL;
	T_ERROR_VAL(app)

	char tmp[64];
	snprintf(tmp, sizeof(tmp), "%s.lock", app);
	fp = fopen(tmp, "w");

	T_ERROR_VAL(fp)
	T_ERROR_VAL(flock(fp->_fileno, LOCK_EX | LOCK_NB) == 0)

	fclose(fp);
	return 0;
}


int UnLock(const char* app)
{
	char tmp[64];
	snprintf(tmp, sizeof(tmp), "%s.lock", app);
	return unlink(tmp);
}


int BlockSignal()
{
	struct sigaction sig;
	memset(&sig, 0, sizeof(sig));
	sigemptyset(&sig.sa_mask);
	sig.sa_handler = SIG_IGN;

	T_ERROR_VAL(sigaction(SIGPIPE, &sig, NULL) == 0)
	T_ERROR_VAL(sigaction(SIGHUP, &sig, NULL) == 0)

	return 0;
}

#endif /* UTIL_H_ */
