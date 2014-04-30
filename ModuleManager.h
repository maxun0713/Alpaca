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

using namespace std;

typedef IModule* (*exportFunc)(void);
#define DIR_MAX_LENGTH 128
#define MAX_MODULE_NAME 128
#define EXPORT_FUNC_SYMBOL "ExportModule"

class ModuleManager {
public:
	ModuleManager();
	virtual ~ModuleManager();

	int Initialize(const char* mod_dir);

	IModule* LoadModule(const char* mod_name);
private:
	IModule* _Query(const char* mod_name);
	IModule* _TryOpen(const char* mod_name);
private:
	char _dir[DIR_MAX_LENGTH];
	typedef map<string, IModule*> MODULE_MAP;
	typedef MODULE_MAP::iterator MODULE_ITER;
	MODULE_MAP	_moduleMap;
};

#endif /* MODULEMANAGER_H_ */
