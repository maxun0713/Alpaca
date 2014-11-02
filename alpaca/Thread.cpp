#include "Thread.h"
#include "CoreTypes.h"
#include <time.h>

namespace alpaca
{

AL_ThreadControl::AL_ThreadControl():_id(0)
{
}

AL_ThreadControl::AL_ThreadControl(pthread_t id):_id(id)
{
}

int AL_ThreadControl::join()
{
    if (pthread_self() ==  _id)
    {
        return AL_ERROR;   
    }

    void* ignore = 0;
    return pthread_join(_id, &ignore);
}

int AL_ThreadControl::detach()
{
    if (pthread_self() ==  _id)
    {
        return AL_ERROR;   
    }

    return pthread_detach(_id);
}

pthread_t AL_ThreadControl::getId() const 
{
    return _id;
}

void AL_ThreadControl::yield()
{
    sched_yield();
}

void AL_ThreadControl::sleep(long millsecond)
{
    struct timespec time_eval;
    time_eval.tv_sec = millsecond/1000;
    time_eval.tv_nsec = (millsecond % 1000) * 1000;
    nanosleep(&time_eval, NULL);
}

AL_Thread::AL_Thread():_running(false),_id(0)
{
}

AL_Thread::~AL_Thread()
{
}

int AL_Thread:: start(AL_ThreadControl& control )
{
    //todo thread safe?
    if (_running)
    {
        return AL_ERROR;
    }

    int ret = pthread_create(&_id, 
            0, 
            (void *(*)(void *))threadEntry,
            (void*)this);

    if (ret ==0)
    {
        control = AL_ThreadControl(_id);
    }

    return 0;
}

int AL_Thread:: getThreadControl(AL_ThreadControl& control)
{
    control = AL_ThreadControl(_id);
    return 0;
}

bool AL_Thread::isRunning () const
{
    return _running;
}

void AL_Thread::threadEntry(AL_Thread* pThread)
{

   pThread->_running = true; 
   // notify all
   pThread->run();

   pThread->_running = false; 
}








}

