/**
 * @file MsgHandlerGroup.h
 * @brief  消息处理基类  
 * @author Marv
 * @version 1.0
 * @date 2014-08-31
 */


#ifndef MSGHANDLERGROUP_H
#define MSGHANDLERGROUP_H

#include <stdint.h>
#include <string>
#include <map>
#include <vector>

namespace alpaca {

class MsgHandler
{
public:
    MsgHandler(uint32_t id);
    virtual ~MsgHandler();

    int Handle(void* msgData, size_t dataLen, void* ctx) ;

    uint32_t GetMsgId();

private:
    uint32_t _id;        
};

class MsgHandlerGroup
{
public:
    MsgHandlerGroup(std::string name);
    virtual ~MsgHandlerGroup();

    int Handle(uint32_t id, void* msgData, size_t dataLen, void*ctx);

    virtual int Initialize(std::vector<MsgHandler>) ;    

    std::string GetGroupName();
private:
    std::string  _groupName;
    typedef std::map<uint32_t, MsgHandler> HandlerMap  ;
    HandlerMap   _handlerMap;
};

}




#endif
