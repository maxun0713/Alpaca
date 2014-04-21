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
#include "SessionManager.h"

int main() {
	EventEngine engine;
	SessionManager mgr;

	engine.Initialize(NULL, 0);
	engine.CreateListener("127.0.0.1", 27017, (IOHandler*)&mgr);
	engine.Activate();
	return 0;
}
