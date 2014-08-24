/*
 * GamePortSink.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: marv
 */
#include "GamePortSink.h"
#include <iostream>
using namespace std;

GamePortSink::GamePortSink() {
}

GamePortSink::~GamePortSink() {
}

void GamePortSink::OnRecv(const char* peerNode, void* data, size_t dataLen) {
	cout << data << endl;
}
