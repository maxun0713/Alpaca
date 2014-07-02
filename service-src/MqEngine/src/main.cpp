//
//  main.cpp
//  BueEngine
//
//  Created by marv on 14-5-10.
//  Copyright (c) 2014年 marv. All rights reserved.
//

#include "ServerNode.h"
#include "ClientNode.h"
#include <zmq.h>
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
int main(int argc, const char * argv[])
{
    ServerNode serv;
    ClientNode client;
    int ret;
    char peerNodeID[1024];
    size_t peerNodeIDBufLen = sizeof(peerNodeID);
    void* dataBuf = malloc(1024);
    size_t dataLen = 1024;
    void *context = zmq_ctx_new();
    if (context == NULL) {
        return -1;
    }
    
    NodeInitParam param;
    param.addr = "tcp://127.0.0.1:8888";
    param.context = context;
    param.identity = "SERVER";
    
    ret = serv.Initialize(param);
    cout << ret << endl;
    
    while (1) {
        ret = serv.Recv(peerNodeID, peerNodeIDBufLen, dataBuf, dataLen, true);
        if (ret != 0)
        {
            //cout << "recv error" << serv.What() << endl;
            //sleep(1);
        }
        peerNodeIDBufLen = 1024;
        dataLen = 1024;
    }
    
    return 0;
}

