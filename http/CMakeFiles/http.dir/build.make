# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/parallels/workspace/restserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parallels/workspace/restserver

# Include any dependencies generated for this target.
include http/CMakeFiles/http.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include http/CMakeFiles/http.dir/compiler_depend.make

# Include the progress variables for this target.
include http/CMakeFiles/http.dir/progress.make

# Include the compile flags for this target's objects.
include http/CMakeFiles/http.dir/flags.make

http/CMakeFiles/http.dir/http_server/Server.cpp.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/http_server/Server.cpp.o: http/http_server/Server.cpp
http/CMakeFiles/http.dir/http_server/Server.cpp.o: http/CMakeFiles/http.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/workspace/restserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object http/CMakeFiles/http.dir/http_server/Server.cpp.o"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT http/CMakeFiles/http.dir/http_server/Server.cpp.o -MF CMakeFiles/http.dir/http_server/Server.cpp.o.d -o CMakeFiles/http.dir/http_server/Server.cpp.o -c /home/parallels/workspace/restserver/http/http_server/Server.cpp

http/CMakeFiles/http.dir/http_server/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/http_server/Server.cpp.i"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/parallels/workspace/restserver/http/http_server/Server.cpp > CMakeFiles/http.dir/http_server/Server.cpp.i

http/CMakeFiles/http.dir/http_server/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/http_server/Server.cpp.s"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/parallels/workspace/restserver/http/http_server/Server.cpp -o CMakeFiles/http.dir/http_server/Server.cpp.s

http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o: http/http_client/HttpClient.cpp
http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o: http/CMakeFiles/http.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/workspace/restserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o -MF CMakeFiles/http.dir/http_client/HttpClient.cpp.o.d -o CMakeFiles/http.dir/http_client/HttpClient.cpp.o -c /home/parallels/workspace/restserver/http/http_client/HttpClient.cpp

http/CMakeFiles/http.dir/http_client/HttpClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/http_client/HttpClient.cpp.i"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/parallels/workspace/restserver/http/http_client/HttpClient.cpp > CMakeFiles/http.dir/http_client/HttpClient.cpp.i

http/CMakeFiles/http.dir/http_client/HttpClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/http_client/HttpClient.cpp.s"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/parallels/workspace/restserver/http/http_client/HttpClient.cpp -o CMakeFiles/http.dir/http_client/HttpClient.cpp.s

http/CMakeFiles/http.dir/HttpErrMsg.cpp.o: http/CMakeFiles/http.dir/flags.make
http/CMakeFiles/http.dir/HttpErrMsg.cpp.o: http/HttpErrMsg.cpp
http/CMakeFiles/http.dir/HttpErrMsg.cpp.o: http/CMakeFiles/http.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/parallels/workspace/restserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object http/CMakeFiles/http.dir/HttpErrMsg.cpp.o"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT http/CMakeFiles/http.dir/HttpErrMsg.cpp.o -MF CMakeFiles/http.dir/HttpErrMsg.cpp.o.d -o CMakeFiles/http.dir/HttpErrMsg.cpp.o -c /home/parallels/workspace/restserver/http/HttpErrMsg.cpp

http/CMakeFiles/http.dir/HttpErrMsg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpErrMsg.cpp.i"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/parallels/workspace/restserver/http/HttpErrMsg.cpp > CMakeFiles/http.dir/HttpErrMsg.cpp.i

http/CMakeFiles/http.dir/HttpErrMsg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpErrMsg.cpp.s"
	cd /home/parallels/workspace/restserver/http && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/parallels/workspace/restserver/http/HttpErrMsg.cpp -o CMakeFiles/http.dir/HttpErrMsg.cpp.s

http: http/CMakeFiles/http.dir/http_server/Server.cpp.o
http: http/CMakeFiles/http.dir/http_client/HttpClient.cpp.o
http: http/CMakeFiles/http.dir/HttpErrMsg.cpp.o
http: http/CMakeFiles/http.dir/build.make
.PHONY : http

# Rule to build all files generated by this target.
http/CMakeFiles/http.dir/build: http
.PHONY : http/CMakeFiles/http.dir/build

http/CMakeFiles/http.dir/clean:
	cd /home/parallels/workspace/restserver/http && $(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean.cmake
.PHONY : http/CMakeFiles/http.dir/clean

http/CMakeFiles/http.dir/depend:
	cd /home/parallels/workspace/restserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parallels/workspace/restserver /home/parallels/workspace/restserver/http /home/parallels/workspace/restserver /home/parallels/workspace/restserver/http /home/parallels/workspace/restserver/http/CMakeFiles/http.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : http/CMakeFiles/http.dir/depend
