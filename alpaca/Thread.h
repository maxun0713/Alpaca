/**
 * @file Thread.h
 * @brief   
 * @author Marv
 * @version 1.0
 * @date 2014-11-02
 */

#ifndef _THREAD_H   
#define _THREAD_H

#include <pthread.h>

namespace alpaca {

class AL_ThreadControl
{
public:
    AL_ThreadControl();

    explicit AL_ThreadControl(pthread_t id);

    int join();

    int detach();

    pthread_t getId() const;

    void yield();

    void sleep(long millsecond);

private:
    pthread_t _id;    
};


class AL_Runnable
{
public:
    virtual ~AL_Runnable(){};

    virtual void run() = 0;
};


class AL_Thread : public AL_Runnable
{
public:
    AL_Thread();

    virtual ~AL_Thread();

    int start(AL_ThreadControl& control);

    int getThreadControl(AL_ThreadControl& control);

    bool isRunning() const; 

protected:    
    static void threadEntry(AL_Thread* pThread);

    virtual void run() = 0;

    bool _running;
    
    pthread_t _id;
};

};

#endif
