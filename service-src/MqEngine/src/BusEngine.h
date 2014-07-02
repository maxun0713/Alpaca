/*
 * BusEngine.h
 *
 *  Created on: Jul 3, 2014
 *      Author: marv
 */

#ifndef BUSENGINE_H_
#define BUSENGINE_H_

#include "IModule.h"
#include "IBusEngine.h"
using namespace bus;
class BusEngine : public IBusEngine {
public:
	BusEngine();
	virtual ~BusEngine();
};

#endif /* BUSENGINE_H_ */
