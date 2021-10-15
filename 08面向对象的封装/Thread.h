#ifndef THREAD_H
#define THREAD_H

#include<pthread.h>
class Thread
{
private:
    pthread_t pid_;
    bool autoDel_;
    virtual void run()=0;
    //交由用户改写，用时回调
    static void* ThreadRoutine(void* arg);
    // 
public:
    Thread();
    virtual ~Thread();

    void start();
    void join();

    void SetAutoDel();
};

#endif