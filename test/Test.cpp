
#include "Thread.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace alpaca;
using namespace std;

class SampleThread : public AL_Thread
{
public:
    virtual void run()
    {
        system("touch dummy");
    };

};

TEST(AlpacaTest, ThreadTest)
{
    AL_ThreadControl control;
    SampleThread thread;
    EXPECT_EQ(0, thread.start(control));
   // EXPECT_EQ(true,thread.isRunning());
    EXPECT_EQ(0, control.join());
//    EXPECT_EQ(false,thread.isRunning());
}
