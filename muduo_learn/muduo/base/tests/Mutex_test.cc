#include "muduo/base/CountDownLatch.h"
#include "muduo/base/Mutex.h"
#include "muduo/base/Thread.h"
#include "muduo/base/Timestamp.h"

#include <vector>
#include <stdio.h>
// #include <thread>
// #include <mutex>

using namespace muduo;
// using namespace std;

MutexLock g_mutex;
// std::mutex g_mutex;

std::vector<int> g_vec;
const int kCount = 10*1000*1000;
// 实验目的：测试一下锁的效率，已经多个线程争锁的效率。
// 我们自己实验下，c++锁的效率。
// 经过测试差不了太多。
void threadFunc()
{
  for (int i = 0; i < kCount; ++i)
  {
    MutexLockGuard lock(g_mutex);
    g_vec.push_back(i);
  }
}

int foo() __attribute__ ((noinline));

int g_count = 0;
int foo()
{
  MutexLockGuard lock(g_mutex);
  if (!g_mutex.isLockedByThisThread())
  {
    printf("FAIL\n");
    return -1;
  }

  ++g_count;
  return 0;
}

int main()
{
  MCHECK(foo());
  if (g_count != 1)
  {
    printf("MCHECK calls twice.\n");
    abort();
  }

  const int kMaxThreads = 8;
  g_vec.reserve(kMaxThreads * kCount);

  Timestamp start(Timestamp::now());
  for (int i = 0; i < kCount; ++i)
  {
    g_vec.push_back(i);
  }

  printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

  start = Timestamp::now();
  threadFunc();
  printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

  for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads)
  {
    std::vector<std::unique_ptr<Thread>> threads;
    g_vec.clear();
    start = Timestamp::now();
    for (int i = 0; i < nthreads; ++i)
    {
      // threads.emplace_back(new Thread(&threadFunc));
      threads.emplace_back(std::make_unique<Thread>(&threadFunc));
      // 算了我们的muduo项目使用c++编译的，make unique不能用。
      threads.back()->start();
    }
    for (int i = 0; i < nthreads; ++i)
    {
      threads[i]->join();
    }
    printf("%d thread(s) with lock %f\n", nthreads, timeDifference(Timestamp::now(), start));
  }
}


#if 0
void threadfunc()
{
  for(int i=0;i<kCount;i++){
    lock_guard<std::mutex> loc(g_mutex);
    g_vec.push_back(i);
  }
}

int main()
{
  const int kMaxThreads = 8;
  g_vec.reserve(kMaxThreads * kCount);

  Timestamp start(Timestamp::now());
  for (int i = 0; i < kCount; ++i)
  {
    g_vec.push_back(i);
  }

  printf("single thread without lock %f\n", timeDifference(Timestamp::now(), start));

  start = Timestamp::now();
  threadfunc();
  printf("single thread with lock %f\n", timeDifference(Timestamp::now(), start));

  for (int nthreads = 1; nthreads < kMaxThreads; ++nthreads)
  {
    std::vector<std::unique_ptr<thread>> threads;
    g_vec.clear();
    start = Timestamp::now();
    for (int i = 0; i < nthreads; ++i)
    {
      // threads.emplace_back(new Thread(&threadFunc));
      threads.emplace_back(std::make_unique<thread>(threadfunc));
      // 算了我们的muduo项目使用c++编译的，make unique不能用。
      // threads.back()->start();
    }
    for (int i = 0; i < nthreads; ++i)
    {
      threads[i]->join();
    }
    printf("%d thread(s) with lock %f\n", nthreads, timeDifference(Timestamp::now(), start));
  }
}

#endif