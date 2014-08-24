/*
 * XmlEngine.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: marv
 */

#ifndef XMLENGINE_H_
#define XMLENGINE_H_

#include "LastErrMsg.h"
#include <map>
#include <string>

class TiXmlElement;
namespace alpaca {

class ConfigParser {
public:
	ConfigParser();
	virtual ~ConfigParser();

	virtual int Initialize(void* arg, int arglen);
	virtual int Activate();
	virtual int Release();

	virtual int loadConfig(const std::string& filePath);

	virtual int getConfig(const std::string& group, const std::string& param,
			string& value);

private:
	bool isLeafNode(TiXmlElement* elem);
private:
	typedef std::map<std::string, std::string> ConfigGroupMap;
	typedef std::map<std::string, ConfigGroupMap> ConfigStorageMap;
	ConfigStorageMap _csMap;
	LastErrMsg _lastErrMsg;
};

}

#endif
