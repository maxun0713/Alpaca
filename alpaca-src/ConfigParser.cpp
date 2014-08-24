/*
 * XmlEngine.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: marv
 */

#include "ConfigParser.h"
#include "tinyxml/tinyxml.h"


using namespace std;

namespace alpaca {
ConfigParser::ConfigParser() {
}

ConfigParser::~ConfigParser() {
}

int ConfigParser::Initialize(void* arg, int arglen) {
	return 0;
}

int ConfigParser::Activate() {
	return 0;
}

int ConfigParser::Release() {
	return 0;
}

int ConfigParser::loadConfig(const string& filePath) {
	TiXmlDocument doc;
	if (!doc.LoadFile(filePath.c_str())) {
		SET_ERR_MSG(_lastErrMsg, "parse config")
		return -1;
	}

	TiXmlElement* rootElement = doc.RootElement();
	while (rootElement) {
		ConfigGroupMap groupMap;
		TiXmlElement* childElement = rootElement->FirstChildElement();
		while (childElement) {
			if (isLeafNode(childElement)) //leaf node
			{
				groupMap[childElement->Value()] = childElement->GetText();
				cout << rootElement->Value() << childElement->Value()
						<< childElement->GetText() << endl;
			} else {
				SET_ERR_MSG(_lastErrMsg, "support secondary config only")
				return -1;
			}
			childElement = childElement->NextSiblingElement();
		}

		if (!groupMap.empty()) {
			_csMap[rootElement->Value()] = groupMap;
		}

		rootElement = rootElement->NextSiblingElement();
	}
	return 0;
}

int ConfigParser::getConfig(const string& group, const string& param,
		string& value) {
	if (_csMap.find(group) == _csMap.end()) {
		return -1;
	}

	ConfigGroupMap& groupMap = _csMap[group];
	if (groupMap.find(param) == groupMap.end()) {
		return -1;
	}

	value = groupMap[param];
	return 0;
}

bool ConfigParser::isLeafNode(TiXmlElement* elem) {
	if (elem && !elem->FirstChildElement()) {
		return true;
	}
	return false;
}
}

