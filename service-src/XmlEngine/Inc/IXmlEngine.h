/*
 * IXmlEngine.h
 *
 *  Created on: Aug 1, 2014
 *      Author: marv
 */

#ifndef IXMLENGINE_H_
#define IXMLENGINE_H_

#include <string>
using namespace std;

class IModule;
class IXmlEngine: public IModule {
public:
	virtual ~IXmlEngine() {
	}
	;

	virtual int loadConfig(const string& filePath) = 0;

	virtual int getConfig(const string& group, const string& param,
			string& value) = 0;
};

#endif /* IXMLENGINE_H_ */
