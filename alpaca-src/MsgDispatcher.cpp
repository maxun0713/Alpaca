/**
 * @file MsgDispatcher.cpp
 * @brief   
 * @author Marv
 * @version 1.0
 * @date 2014-08-31
 */


#include "MsgDispatcher.h"

namespace alpaca {

MsgDispatcher::MsgDispatcher(){
}

MsgDispatcher::~MsgDispatcher(){
}

int MsgDispatcher::DispatchMsg(std::string groupName, uint32_t id, void* msg, size_t msgLen, void* ctx){
    HandlerGroupMap::iterator itor = _groupMap.find(groupName);
    if (itor != _groupMap.end())
    {
        return itor->second.Handle(id, msg, msgLen, ctx);
    }

    
    SET_ERR_MSG(_lastErrMsg, "no msggroup " << groupName);
    return -1;
}

int MsgDispatcher::Initialize(std::vector<MsgHandlerGroup> vtHandlerGroup){
    for (size_t i = 0; i< vtHandlerGroup.size(); i++){
        _groupMap.insert(std::make_pair(vtHandlerGroup[i].GetGroupName(), vtHandlerGroup[i]));
    }

    return 0;
}



}
