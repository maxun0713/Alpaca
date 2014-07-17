/*
 * ModuleLoader.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include "IModule.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef IModule* (*exportFunc)(void);
#define DIR_MAX_LENGTH 128
#define MAX_MODULE_NAME 128
#define EXPORT_FUNC_SYMBOL "ExportModule"


class ModuleManager:public IModule {
public:
	ModuleManager();
	virtual ~ModuleManager();

	virtual int Initialize(void* mod_dir, int arglen);
	virtual int Activate() ;
	virtual int Release() ;

	IModule* LoadModule(const char* mod_name);
private:
	IModule* _Query(const char* mod_name);
	IModule* _TryOpen(const char* mod_name);
private:
	char _dir[DIR_MAX_LENGTH];
	typedef vector<void*> HANDLER_STORAGE;
	typedef HANDLER_STORAGE::iterator HANDLE_ITER;
	HANDLER_STORAGE  _handlerStorage;
};

#endif /* MODULEMANAGER_H_ */
