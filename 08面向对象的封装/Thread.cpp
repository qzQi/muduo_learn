#include<iostream>
using namespace std;

#include"Thread.h"

Thread::Thread():autoDel_(false)
{
    cout<<"thread lib ..."<<endl;
}

Thread::~Thread()
{
    cout<<"end of thread lib"<<endl;
}

// 创建线程
void Thread::start()
{
    pthread_create(&this->pid_,NULL,ThreadRoutine,(void*)this);
    return;
}

void Thread::join()
{
    pthread_join(this->pid_,NULL);
}

void* Thread::ThreadRoutine(void* arg)
{
    Thread* th=static_cast<Thread*>(arg);
    th->run();
    if(th->autoDel_)delete th;
    return NULL;
}

void Thread::SetAutoDel()
{
    this->autoDel_=true;
}
