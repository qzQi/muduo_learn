// 为使用我们自己的线程库，仅需提供一个function<void()>函数就可以
// 不需要继承与override

#include"Thread.h"
#include<unistd.h>
#include<iostream>
#include<functional>

using namespace std;
using namespace std::placeholders;

// 回调函数形式--->  void()
// class Thread;

void call_back_1()
{
    cout<<"fucntion void()"<<endl;
}

void call_back_2(unsigned int i)
{
    while(i--)
    cout<<i<<"function void(int)"<<endl;
}

struct Functor
{
    Functor()=default;
    void operator()()
    {
        cout<<"test functor"<<endl;
    }
};

class Foo
{
public:
	void MemberFun()
	{
        cout<<"plain class mem func"<<endl;
	}
};

int main()
{
    Thread t1{call_back_1};
    Thread t2{bind(call_back_2,3)};
    Foo foo{};
    Thread t3{bind(&Foo::MemberFun,&foo)};
    Thread t4{Functor()};

	t1.Start();
	t2.Start();
	t3.Start();
	t4.Start();

	t1.Join();
	t2.Join();
	t3.Join();
	t4.Join();

    


}