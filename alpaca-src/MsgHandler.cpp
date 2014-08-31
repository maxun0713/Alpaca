/**
 * @file MsgHandler.cpp
 * @brief   
 * @author Marv
 * @version 1.0
 * @date 2014-08-31
 */

#include "MsgHandler.h"

namespace alpaca {

MsgHandler::MsgHandler(uint32_t id):_id(id){
}

MsgHandler::~MsgHandler(){
}

uint32_t MsgHandler::GetMsgId(){
    return _id;
}

int MsgHandler::Handle(void* msgData, size_t dataLen, void* ctx) {
    return 0;
}

MsgHandlerGroup::MsgHandlerGroup(std::string name):_groupName(name){
}

MsgHandlerGroup::~MsgHandlerGroup(){
}

int MsgHandlerGroup::Handle(uint32_t id, void* msgData, size_t dataLen, void*ctx){
    HandlerMap::iterator itor = _handlerMap.find(id);
    if (itor != _handlerMap.end()){
        return -1;
    } else {
        return itor->second.Handle(msgData, dataLen, ctx);
    } 
};    

int MsgHandlerGroup::Initialize(std::vector<MsgHandler> vtHhandler){
    for (size_t i = 0; i < vtHhandler.size(); i++){
        _handlerMap.insert(std::make_pair(vtHhandler[i].GetMsgId(), vtHhandler[i]) );
    }
    
    return 0;
}

std::string MsgHandlerGroup::GetGroupName(){
    return _groupName;
}

















}
