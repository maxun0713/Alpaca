/*
 * EventEngine.h
 *
 *  Created on: 2014年5月1日
 *      Author: marv
 */

#include "Exporter.h"
#include "GateSrv.h"


extern "C" void* ExportModule(){
	return (void*)new GateSrv();
}
