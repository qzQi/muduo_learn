#include "muduo/base/LogFile.h"
#include "muduo/base/Logging.h"
 
#include <unistd.h>
// 测试日志滚动
std::unique_ptr<muduo::LogFile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
  // 实现文件的自动滚动
  // 单个文件；多个文件写入（我们类的）缓冲区？
  // ::fwrite(msg,1,len,File*);
}

void flushFunc()
{
  g_logFile->flush();
}

int main(int argc, char* argv[])
{
  char name[256] = { '\0' };
  strncpy(name, argv[0], sizeof name - 1);

  g_logFile.reset(new muduo::LogFile(::basename(name), 200*1000));
  // g_logFile=std::make_unique(muduo::LogFile(::basename(name),200*1024));
  // 指定basename以及单个文件的大小，basename函数

  LOG_INFO<<"在此之前的日志没有set，还是--stdout，类的static set生效后会影响接下来所有的";

// Logger类的设置，就是在本次对象析构后
  muduo::Logger::setOutput(outputFunc);
  muduo::Logger::setFlush(flushFunc);

  muduo::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
// 10000条日志信息
  for (int i = 0; i < 10000; ++i)
  {
    LOG_INFO << line << i;

    usleep(1000);
  }
}
