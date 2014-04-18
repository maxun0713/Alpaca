//============================================================================
// Name        : EventEngine.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "EventEngine.h"
#include "SessionHandler.h"
int main() {
	EventEngine engine;
	SessionHandler handler;

	engine.Initialize(NULL, 0);
	engine.CreateListener("127.0.0.1", 123, (IOHandler*)&handler);
	engine.Activate();
	return 0;
}
