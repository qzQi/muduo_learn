# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/qizhiyun/muduo_code/poll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/qizhiyun/muduo_code/poll/build

# Include any dependencies generated for this target.
include CMakeFiles/echocli.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echocli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echocli.dir/flags.make

CMakeFiles/echocli.dir/echo_cli.cpp.o: CMakeFiles/echocli.dir/flags.make
CMakeFiles/echocli.dir/echo_cli.cpp.o: ../echo_cli.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/qizhiyun/muduo_code/poll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echocli.dir/echo_cli.cpp.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echocli.dir/echo_cli.cpp.o -c /home/qizhiyun/muduo_code/poll/echo_cli.cpp

CMakeFiles/echocli.dir/echo_cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echocli.dir/echo_cli.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/qizhiyun/muduo_code/poll/echo_cli.cpp > CMakeFiles/echocli.dir/echo_cli.cpp.i

CMakeFiles/echocli.dir/echo_cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echocli.dir/echo_cli.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/qizhiyun/muduo_code/poll/echo_cli.cpp -o CMakeFiles/echocli.dir/echo_cli.cpp.s

# Object files for target echocli
echocli_OBJECTS = \
"CMakeFiles/echocli.dir/echo_cli.cpp.o"

# External object files for target echocli
echocli_EXTERNAL_OBJECTS =

bin/echocli: CMakeFiles/echocli.dir/echo_cli.cpp.o
bin/echocli: CMakeFiles/echocli.dir/build.make
bin/echocli: CMakeFiles/echocli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/qizhiyun/muduo_code/poll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/echocli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echocli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echocli.dir/build: bin/echocli

.PHONY : CMakeFiles/echocli.dir/build

CMakeFiles/echocli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echocli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echocli.dir/clean

CMakeFiles/echocli.dir/depend:
	cd /home/qizhiyun/muduo_code/poll/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/qizhiyun/muduo_code/poll /home/qizhiyun/muduo_code/poll /home/qizhiyun/muduo_code/poll/build /home/qizhiyun/muduo_code/poll/build /home/qizhiyun/muduo_code/poll/build/CMakeFiles/echocli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echocli.dir/depend
