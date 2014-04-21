/*
 * ModuleLoader.h
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#ifndef MODULELOADER_H_
#define MODULELOADER_H_

#include "IModule.h"
#include <string>
#include <map>

using namespace std;

typedef map<string, IModule*> MODULE_MAP;
//used to manage modules of a same directory
class ModuleLoader {
public:
	ModuleLoader(const char* dir);
	virtual ~ModuleLoader();

	int LoadModule(const char* module_name);
	IModule* GetModule(const char* module_name);
private:
	string _modDir;
	MODULE_MAP	modMap;
};

#endif /* MODULELOADER_H_ */
