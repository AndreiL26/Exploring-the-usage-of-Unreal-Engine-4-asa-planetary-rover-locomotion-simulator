# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/andrei/benchmark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrei/benchmark/build

# Include any dependencies generated for this target.
include CMakeFiles/BENCHMARK_boxes_model_count.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BENCHMARK_boxes_model_count.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BENCHMARK_boxes_model_count.dir/flags.make

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o: CMakeFiles/BENCHMARK_boxes_model_count.dir/flags.make
CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o: ../boxes_model_count.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrei/benchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o -c /home/andrei/benchmark/boxes_model_count.cc

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrei/benchmark/boxes_model_count.cc > CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.i

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrei/benchmark/boxes_model_count.cc -o CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.s

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.requires:

.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.requires

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.provides: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.requires
	$(MAKE) -f CMakeFiles/BENCHMARK_boxes_model_count.dir/build.make CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.provides.build
.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.provides

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.provides.build: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o


CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o: CMakeFiles/BENCHMARK_boxes_model_count.dir/flags.make
CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o: ../boxes.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrei/benchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o -c /home/andrei/benchmark/boxes.cc

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrei/benchmark/boxes.cc > CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.i

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrei/benchmark/boxes.cc -o CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.s

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.requires:

.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.requires

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.provides: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.requires
	$(MAKE) -f CMakeFiles/BENCHMARK_boxes_model_count.dir/build.make CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.provides.build
.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.provides

CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.provides.build: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o


# Object files for target BENCHMARK_boxes_model_count
BENCHMARK_boxes_model_count_OBJECTS = \
"CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o" \
"CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o"

# External object files for target BENCHMARK_boxes_model_count
BENCHMARK_boxes_model_count_EXTERNAL_OBJECTS =

BENCHMARK_boxes_model_count: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o
BENCHMARK_boxes_model_count: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o
BENCHMARK_boxes_model_count: CMakeFiles/BENCHMARK_boxes_model_count.dir/build.make
BENCHMARK_boxes_model_count: libgtest.a
BENCHMARK_boxes_model_count: libgtest_main.a
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libSimTKsimbody.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libSimTKmath.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libSimTKcommon.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libblas.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/liblapack.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libblas.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_client.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_gui.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_sensors.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_rendering.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_physics.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_ode.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_transport.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_msgs.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_util.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_common.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_gimpact.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_opcode.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_opende_ou.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_ccd.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_system.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_regex.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libpthread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libprotobuf.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libsdformat.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreMain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_system.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libpthread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreTerrain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgrePaging.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libignition-transport4.so.4.0.0
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libignition-msgs1.so.1.0.0
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libignition-common1.so.1.1.1
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libignition-fuel_tools1.so.1.2.0
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_system.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libpthread.so
BENCHMARK_boxes_model_count: libgtest.a
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/liblapack.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_client.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_gui.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_sensors.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_rendering.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_physics.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_ode.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_transport.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_msgs.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_util.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_common.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_gimpact.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_opcode.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_opende_ou.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libgazebo_ccd.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_system.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_regex.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libpthread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libprotobuf.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libsdformat.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreMain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreTerrain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgrePaging.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_thread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_system.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_regex.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libpthread.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libprotobuf.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libsdformat.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreMain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgreTerrain.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libOgrePaging.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libprotobuf.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libignition-math4.so.4.0.0
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libuuid.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libuuid.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libswscale.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libswscale.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavdevice.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavdevice.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavformat.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavformat.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavcodec.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavcodec.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavutil.so
BENCHMARK_boxes_model_count: /usr/lib/x86_64-linux-gnu/libavutil.so
BENCHMARK_boxes_model_count: CMakeFiles/BENCHMARK_boxes_model_count.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrei/benchmark/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable BENCHMARK_boxes_model_count"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BENCHMARK_boxes_model_count.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BENCHMARK_boxes_model_count.dir/build: BENCHMARK_boxes_model_count

.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/build

CMakeFiles/BENCHMARK_boxes_model_count.dir/requires: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes_model_count.cc.o.requires
CMakeFiles/BENCHMARK_boxes_model_count.dir/requires: CMakeFiles/BENCHMARK_boxes_model_count.dir/boxes.cc.o.requires

.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/requires

CMakeFiles/BENCHMARK_boxes_model_count.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BENCHMARK_boxes_model_count.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/clean

CMakeFiles/BENCHMARK_boxes_model_count.dir/depend:
	cd /home/andrei/benchmark/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrei/benchmark /home/andrei/benchmark /home/andrei/benchmark/build /home/andrei/benchmark/build /home/andrei/benchmark/build/CMakeFiles/BENCHMARK_boxes_model_count.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BENCHMARK_boxes_model_count.dir/depend

