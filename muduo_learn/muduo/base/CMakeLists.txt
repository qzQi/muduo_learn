#[[
set(base_SRCS
  AsyncLogging.cc
  Condition.cc
  CountDownLatch.cc
  CurrentThread.cc
  Date.cc
  Exception.cc
  FileUtil.cc
  LogFile.cc
  Logging.cc
  LogStream.cc
  ProcessInfo.cc
  Timestamp.cc
  Thread.cc
  ThreadPool.cc
  TimeZone.cc
  )
]]

  set(base_SRCS
  Timestamp.cc
  Exception.cc
  CurrentThread.cc
  Thread.cc
  CountDownLatch.cc
  Condition.cc
  ThreadPool.cc
  LogStream.cc
  Logging.cc
  LogFile.cc
  TimeZone.cc
  Date.cc
  FileUtil.cc
  ProcessInfo.cc
  )

# 用我们的源文件生成一个库lib 生成muduo_base库
add_library(muduo_base ${base_SRCS})
# 生成这个库可能需要链接的库
target_link_libraries(muduo_base pthread rt)

#add_library(muduo_base_cpp11 ${base_SRCS})
#target_link_libraries(muduo_base_cpp11 pthread rt)
#set_target_properties(muduo_base_cpp11 PROPERTIES COMPILE_FLAGS "-std=c++0x")


# 这个install标志是什么
install(TARGETS muduo_base DESTINATION lib)
#install(TARGETS muduo_base_cpp11 DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/muduo/base)

# 编译我们的tests文件夹，在build产生tests文件夹
# 编译tests
 
if(MUDUO_BUILD_EXAMPLES)
  add_subdirectory(tests)
endif()


