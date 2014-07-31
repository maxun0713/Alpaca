/*
 * XmlEngine.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: marv
 */

#ifndef XMLENGINE_H_
#define XMLENGINE_H_

#include "IModule.h"
#include "IXmlEngine.h"
#include <map>

using namespace std;;

class TiXmlElement;
class XmlEngine:public IXmlEngine
{
public:
	XmlEngine();
	virtual ~XmlEngine();

	virtual int Initialize(void* arg, int arglen) ;
	virtual int Activate() ;
	virtual int Release() ;

	virtual int loadConfig(const string& filePath) ;

	virtual int getConfig(const string& group, const string& param, string& value) ;

private:
	bool  isLeafNode(TiXmlElement* elem);
private:
	typedef map<string, string>  ConfigGroupMap;
	typedef map<string, ConfigGroupMap> ConfigStorageMap;
	ConfigStorageMap     _csMap;
};









#endif
