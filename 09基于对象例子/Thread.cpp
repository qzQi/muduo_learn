#include"Thread.h"

Thread::Thread(const ThreadFunc& func):func_(func),autoDelete_(false)
{}


void Thread::Start()
{
    pthread_create(&this->threadId_,NULL,ThreadRoutine,(void*)this);
    return ;
}

void Thread::Join()
{
    pthread_join(threadId_,NULL);
    return ;
}

void* Thread::ThreadRoutine(void *arg)
{
    Thread *thread=static_cast<Thread*>(arg);
    thread->Run();
    if(thread->autoDelete_)delete thread;
    return NULL;
}


void Thread::SetAutoDelete(bool autoDelete)
{
	autoDelete_ = autoDelete;
}

void Thread::Run()
{
	func_();//call back
}