/**
 * @file MsgDispatcher.h
 * @brief   :
 * @author Marv
 * @version 1.0
 * @date 2014-08-31
 */

#ifndef  _MSGDISPATCHER_H
#define  _MSGDISPATCHER_H

#include "MsgHandler.h"
#include "LastErrMsg.h"

namespace alpaca {
class MsgDispatcher 
{
public:
    MsgDispatcher();
    virtual ~MsgDispatcher(); 

    int DispatchMsg(std::string groupName, uint32_t id,  void* msg, size_t msgLen, void* ctx);

    int Initialize(std::vector<MsgHandlerGroup> vtHandlerGroup);


private:
    typedef std::map<std::string, MsgHandlerGroup>  HandlerGroupMap;
    HandlerGroupMap  _groupMap;
    LastErrMsg       _lastErrMsg;
};







}
#endif
