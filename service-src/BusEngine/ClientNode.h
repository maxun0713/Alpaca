//
//  ClientNode.h
//  mqengine
//
//  Created by marv on 14-6-29.
//  Copyright (c) 2014年 marv. All rights reserved.
//

#ifndef __mqengine__ClientNode__
#define __mqengine__ClientNode__

#include "Node.h"
#include <iostream>

class ClientNode:public CNode
{
public:
    ClientNode();
    virtual ~ClientNode();
    
    virtual int Initialize(const NodeInitParam &params);
};


#endif /* defined(__mqengine__ClientNode__) */
