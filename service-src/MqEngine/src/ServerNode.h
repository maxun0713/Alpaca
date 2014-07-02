/*
 * ServerNode.h
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#ifndef SERVERNODE_H_
#define SERVERNODE_H_

#include "Node.h"

class ServerNode: public CNode
{
public:
    ServerNode();
    virtual ~ServerNode();

    int  Initialize(const NodeInitParam& params);

};

#endif /* SERVERNODE_H_ */
