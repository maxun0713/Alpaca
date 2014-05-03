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


int ModuleManager::Initialize(void* mod_dir, int arglen)
{
	T_ERROR_VAL(mod_dir)

	strncpy(_dir, (char*)mod_dir, arglen);
	return 0;
}


int ModuleManager::Activate()
{
	return 0;
}


int ModuleManager::Release()
{
	HANDLE_ITER iter = _handlerStorage.begin();
	for(; iter != _handlerStorage.end(); iter++)
	{
		dlclose(*iter);
	}

	MODULE_ITER modIter = _moduleMap.begin();
	IModule* mod;
	for(; modIter != _moduleMap.end(); modIter++)
	{
		mod = modIter->second;
		if(mod)
		{
			mod->Release();
		}
	}

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
	char tmp[MAX_MODULE_NAME] = {0 };
	snprintf(tmp, MAX_MODULE_NAME, "%s/%s.so", _dir,
			mod_name );

	handle = dlopen(tmp, RTLD_LAZY | RTLD_GLOBAL);
	T_ERROR_PTR_WITH_DL_ERR_INFO(handle)
	_handlerStorage.push_back(handle);

	inst = (exportFunc)dlsym(handle, EXPORT_FUNC_SYMBOL);
	T_ERROR_PTR_WITH_DL_ERR_INFO(inst)

	mod = inst();
	T_ERROR_PTR(mod);
	_moduleMap.insert(make_pair(mod_name, mod) );

	return mod;
}
