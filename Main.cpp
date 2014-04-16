/*
 * Main.cpp
 *
 *  Created on: 2014年4月16日
 *      Author: marv
 */

#include "LogEngine.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	LogEngine engine;
	engine.Initialize(argv[0], "/home/marv");


	return 0;
}
