// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_LOGFILE_H
#define MUDUO_BASE_LOGFILE_H

#include "muduo/base/Mutex.h"
#include "muduo/base/Types.h"

#include <memory>
// 实现日志滚动
namespace muduo
{

namespace FileUtil
{
class AppendFile;
}
/*
basename:日志文件的命名
flushInterval:日志写入的时间
checkEveryN: log写入N次来检查一下缓冲区？
rollSize：滚动条件的大小
*/
class LogFile : noncopyable
{
 public:
  LogFile(const string& basename,
          off_t rollSize,
          bool threadSafe = true,
          // 通过锁来保证的线程安全
          int flushInterval = 3,
          int checkEveryN = 1024);
  ~LogFile();

  void append(const char* logline, int len);
  void flush();
  bool rollFile();

 private:
  void append_unlocked(const char* logline, int len);

  static string getLogFileName(const string& basename, time_t* now);

  const string basename_;
  const off_t rollSize_;
  const int flushInterval_;
  const int checkEveryN_;

  int count_;
//   一个计数器，每次达到1024check一下需不需要换（滚动）一个文件，或者需不需要写入文件

  std::unique_ptr<MutexLock> mutex_;
  time_t startOfPeriod_;
//   开始记录日志时间（调整为0点时间）UNIX元年的秒数，当天的0点
  time_t lastRoll_;
//   上一次日志滚动时间（更换文件），
  time_t lastFlush_;
//   上一次日志写入时间
  std::unique_ptr<FileUtil::AppendFile> file_;

  const static int kRollPerSeconds_ = 60*60*24;
};

}  // namespace muduo
#endif  // MUDUO_BASE_LOGFILE_H
