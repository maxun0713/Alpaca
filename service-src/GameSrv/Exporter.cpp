/*
 * EventEngine.h
 *
 *  Created on: 2014年5月1日
 *      Author: marv
 */

#include "Exporter.h"
#include "GameSrv.h"


extern "C" void* ExportModule(){
	return (void*)new GameSrv();
}
