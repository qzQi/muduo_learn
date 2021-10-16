该文件的布局模仿muduo源代码的布局，通过修改原来的cmake文件来使用muduo的cmake文件。

muduo_learn/muduo  :我们要分析的,库的主体
muduo_learn/muduo/base：类的基础库
muduo_learn/muduo/base/test：对base库的测试程序。
muduo_learn/muduo/net




配置完这些我们就可以来完成代码了。

这个库的构建文件。
/muduo_learn/CMakeLists.txt
/muduo_learn/build.sh
build.sh定义了我们的安装目录在哪个地方，这里我们在上级build目录下安装。
生成的makefile与cmakefile也都在那，我们可以在那里
make 
make clean 
make install


用来构建base部分
muduo_learn/muduo/base/CMakeLists.txt：

