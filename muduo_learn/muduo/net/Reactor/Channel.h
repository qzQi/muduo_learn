#ifndef REACTOR_CHANNEL_h
#define REACTOR_CHANNEL_H
/*
目的：提供对我们fd的抽象，把我们所关心的fd与它的回调函数关联在一块。
模块化
*/
#include"muduo/base/noncopyable.h"
#include"muduo/base/Timestamp.h"

#include<functional>
#include<memory>

namespace muduo
{
namespace reactor
{
class EventLoop;

class Channel :noncoppyable
{
public:
  typedef std::function<void()> EventCallback;
  typedef std::function<void(Timestamp)> ReadEventCallback;

  Channel(EventLoop* loop, int fd);
  ~Channel();


}


} // namespace reactor



} // namespace muduo


#endif