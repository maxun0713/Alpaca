/*
 * ModuleLoader.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef MODULEMANAGER_H_
#define MODULEMANAGER_H_

#include "IModule.h"
#include <string>
#include <map>

using namespace std;

typedef map<string, IModule*> MODULE_MAP;
//used to manage modules of a same directory
class ModuleManager {
public:
	ModuleManager(const char* dir);
	virtual ~ModuleManager();

	int LoadModule(const char* module_name);
	IModule* GetModule(const char* module_name);
private:
	string _modDir;
	MODULE_MAP	modMap;
};

#endif /* MODULEMANAGER_H_ */
