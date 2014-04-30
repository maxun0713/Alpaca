/*
 * ModuleManager.cpp
 *
 *  Created on: 2014年4月21日
 *      Author: marv
 */

#include "ModuleManager.h"
#include "CommonDef.h"
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

ModuleManager::ModuleManager() {
	memset(_dir, 0, DIR_MAX_LENGTH);
}

ModuleManager::~ModuleManager() {
	// TODO Auto-generated destructor stub
}

int ModuleManager::Initialize(const char* mod_dir) {
	T_ERROR_VAL(mod_dir)

	strncpy(_dir, mod_dir, DIR_MAX_LENGTH);
	return 0;
}


IModule* ModuleManager::LoadModule(const char* module_name)
{
	T_ERROR_PTR(module_name)

	IModule* mod = _Query(module_name);
	if(mod == NULL)
	{
		return _TryOpen(module_name);
	}

	return mod;
}


IModule* ModuleManager::_Query(const char* mod_name) {
	T_ERROR_PTR(mod_name)

	MODULE_ITER iter = _moduleMap.find(mod_name);
	if(iter != _moduleMap.end())
	{
		return iter->second;
	}

	return NULL;
}

IModule* ModuleManager::_TryOpen(const char* mod_name) {
	T_ERROR_PTR(mod_name)

	void* handle;
	exportFunc inst;
	IModule* mod;
	char tmp[MAX_MODULE_NAME];
	snprintf("%s/%s", MAX_MODULE_NAME, (char*)_dir,
			(char*)mod_name );

	handle = dlopen(tmp, RTLD_NOW | RTLD_GLOBAL);
	T_ERROR_PTR_WITH_DL_ERR_INFO(handle)

	inst = (exportFunc)dlsym(handle, EXPORT_FUNC_SYMBOL);
	T_ERROR_PTR_WITH_DL_ERR_INFO(inst)

	mod = inst();

	_moduleMap.insert(make_pair(mod_name, mod) );

	return NULL;
}
