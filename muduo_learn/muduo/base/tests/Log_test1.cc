#include"muduo/base/Logging.h"
#include<errno.h>

using namespace muduo;

int main()
{
    // 输出到stdout默认
    LOG_TRACE<<"trace";
    LOG_DEBUG<<"debug...";
    // 在源文件设定的当前的log级别是info，前两个不会输出
    LOG_INFO<<"info...";
    LOG_WARN<<"warn...";
    LOG_ERROR<<"error";
    // LOG_FATAL<<"fatal_err...";
    errno=13;
    LOG_SYSERR<<"syserr...";
    // LOG_SYSFATAL<<"sysfatal...";
    printf("system run good\n");
    // 如何输出到文件，构造的时候吧？  logg文件set 函数
    return 0;
}