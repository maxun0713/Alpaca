/*
 * Node.cpp
 *
 *  Created on: 2014年5月11日
 *      Author: marv
 */

#include "Node.h"

Node::Node():_socket(NULL)
{
    // TODO Auto-generated constructor stub

}

Node::~Node()
{
    // TODO Auto-generated destructor stub
}

const char* Node::What()
{
    return _lasgErrMsg.What();
}
