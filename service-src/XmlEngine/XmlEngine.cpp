/*
 * XmlEngine.cpp
 *
 *  Created on: Aug 1, 2014
 *      Author: marv
 */

#include "XmlEngine.h"
#include "tinyxml/tinyxml.h"

XmlEngine::XmlEngine() {
}

XmlEngine::~XmlEngine() {
}

int XmlEngine::Initialize(void* arg, int arglen) {
	return 0;
}

int XmlEngine::Activate() {
	return 0;
}

int XmlEngine::Release() {
	return 0;
}

int XmlEngine::loadConfig(const string& filePath) {
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

int XmlEngine::getConfig(const string& group, const string& param,
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

bool XmlEngine::isLeafNode(TiXmlElement* elem) {
	if (elem && !elem->FirstChildElement()) {
		return true;
	}
	return false;
}
