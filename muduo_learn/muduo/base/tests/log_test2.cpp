#include"muduo/base/Logging.h"
#include<errno.h>
#include<stdio.h>

using namespace muduo;

FILE* g_file;

void dummyOutput(const char* meg,int len)
{
    if(g_file){
        fwrite(meg,1,len,g_file);
    }
}

void dummyFlush()
{
    ::fflush(g_file);
}

int main()
{
    g_file=::fopen("/tmp/muduo_log","ae");
    Logger::setLogLevel(Logger::TRACE);
    // 设置日志级别

    Logger::setOutput(dummyOutput);
    Logger::setFlush(dummyFlush);

    LOG_TRACE<<"trace....";
    LOG_DEBUG<<"debug....";
    LOG_INFO<<"info....";
    fclose(g_file);
}