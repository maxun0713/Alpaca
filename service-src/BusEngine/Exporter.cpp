/*
 * EventEngine.h
 *
 *  Created on: 2014年5月1日
 *      Author: marv
 */

#include "Exporter.h"
#include "BusEngine.h"


extern "C" void* ExportModule(){
	return (void*)new BusEngine();
}
