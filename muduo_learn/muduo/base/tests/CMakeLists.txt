add_executable(timestamp_unittest Timestamp_unittest.cc)
target_link_libraries(timestamp_unittest muduo_base)

add_executable(atomic_unittest Atomic_unittest.cc)
# target_link_libraries(atomic_unittest muduo_base)
# 这个不链接也可以。

add_executable(exception_unittest Exception_test.cc)
target_link_libraries(exception_unittest muduo_base)

add_executable(thread_test Thread_test.cc)
target_link_libraries(thread_test muduo_base)

add_executable(mutex_test Mutex_test.cc)
target_link_libraries(mutex_test muduo_base)

add_executable(blockingqueue_test BlockingQueue_test.cc)
target_link_libraries(blockingqueue_test muduo_base)

add_executable(blockingqueue_bench BlockingQueue_bench.cc)
target_link_libraries(blockingqueue_bench muduo_base)

add_executable(boundedblockingqueue_test BoundedBlockingQueue_test.cc)
target_link_libraries(boundedblockingqueue_test muduo_base)

add_executable(threadpool_test ThreadPool_test.cc)
target_link_libraries(threadpool_test muduo_base)

add_executable(singleton_test Singleton_test.cc)
target_link_libraries(singleton_test muduo_base)

add_executable(threadlocalsingleton_test ThreadLocalSingleton_test.cc)
target_link_libraries(threadlocalsingleton_test muduo_base)

add_executable(threadlocal_test ThreadLocal_test.cc)
target_link_libraries(threadlocal_test muduo_base)

add_executable(log_test1 Log_test1.cc)
target_link_libraries(log_test1 muduo_base)

add_executable(log_test2 log_test2.cpp)
target_link_libraries(log_test2 muduo_base)

add_executable(logfile_test LogFile_test.cc)
target_link_libraries(logfile_test muduo_base)

add_executable(fileutil_test FileUtil_test.cc)
target_link_libraries(fileutil_test muduo_base)

add_executable(processinfo_test ProcessInfo_test.cc)
target_link_libraries(processinfo_test muduo_base)

add_executable(logging_test Logging_test.cc)
target_link_libraries(logging_test muduo_base)

if(ZLIB_FOUND)
  add_executable(gzipfile_test GzipFile_test.cc)
  target_link_libraries(gzipfile_test muduo_base z)
  add_test(NAME gzipfile_test COMMAND gzipfile_test)
endif()