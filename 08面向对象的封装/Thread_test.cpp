// 使用我们自己的线程库，override run();


#include "Thread.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class TestThread : public Thread
{
public:
	TestThread(int count) : count_(count)
	{
		cout<<"TestThread ..."<<endl;
	}

	~TestThread()
	{
		cout<<"~TestThread ..."<<endl;
	}

private:
// 我们用户自己编写的run函数，作为回调函数，被我们的wrapper_thread调用。
	void run()//这玩意第一个参数默认为*this，无法pthread_create
	{
		while (count_--)
		{
			cout<<"this is a test ..."<<endl;
			sleep(1);
		}
	}

	int count_;
};

int main(void)
{
	/*
	TestThread t(5);
	t.Start();

	t.Join();
	这部分代码的问题就是线程的声明结束了，但是线程对象没有销毁
	autodelete的用途，线程结束自动销毁对象。
	*/

	TestThread* t2 = new TestThread(5);
	t2->SetAutoDel();
    
    t2->start();
    t2->join();
	// C语言貌似没join也会执行，但是有join后就在join执行？对吗？

	for (; ; )
		pause();

	return 0;
}
