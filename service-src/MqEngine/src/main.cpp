//
//  main.cpp
//  BueEngine
//
//  Created by marv on 14-5-10.
//  Copyright (c) 2014年 marv. All rights reserved.
//

#include <iostream>
#include <zmq.h>
#include <assert.h>
using namespace std;
int main(int argc, const char * argv[])
{
    void *context = zmq_ctx_new();
    void *frontend = zmq_socket(context, ZMQ_ROUTER);
    int rc = zmq_setsockopt(frontend, ZMQ_IDENTITY, "S",
                          1);
    cout << rc << endl;
    rc = zmq_bind(frontend, "tcp://127.0.0.1:8888");
    cout << rc << endl;
    
    while (1) {
        zmq_msg_t remote;
        zmq_msg_t delimiter;
        zmq_msg_t body;
        int more;
        int ret;
        size_t moreLen = sizeof(more);
        while (1) {
            zmq_msg_init(&remote);
            zmq_msg_recv(&remote, frontend, 0);
            cout << (char*)zmq_msg_data(&remote) << endl;
            cout << zmq_msg_size(&remote) << endl;
            ret = zmq_getsockopt(frontend, ZMQ_RCVMORE, &more, &moreLen);
            if(ret != 0 || !more)
            {
                zmq_msg_close(&remote);
                break;
            }
            
            zmq_msg_init(&delimiter);
            zmq_msg_recv(&delimiter, frontend, 0);
            cout << (char*)zmq_msg_data(&delimiter) << endl;
            cout << zmq_msg_size(&delimiter) << endl;
            ret = zmq_getsockopt(frontend, ZMQ_RCVMORE, &more, &moreLen);
            if(ret != 0 || !more)
            {
                zmq_msg_close(&remote);
                zmq_msg_close(&delimiter);
                break;
            }
            
            zmq_msg_init(&body);
            zmq_msg_recv(&body, frontend, 0);
            cout << (char*)zmq_msg_data(&body) << endl;
            cout << zmq_msg_size(&body) << endl;
            zmq_getsockopt(frontend, ZMQ_RCVMORE, &more, &moreLen);
            if(!more)
            {
                zmq_msg_close(&remote);
                zmq_msg_close(&delimiter);
                break;
            }
            
            zmq_msg_close(&remote);
            zmq_msg_close(&delimiter);
            zmq_msg_close(&body);

        }
    }

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

