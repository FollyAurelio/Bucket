# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /sbin/cmake

# The command to remove a file.
RM = /sbin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pancake/Documents/Bucket/lib/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pancake/Documents/Bucket/lib/glfw

# Include any dependencies generated for this target.
include tests/CMakeFiles/empty.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/empty.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/empty.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/empty.dir/flags.make

tests/CMakeFiles/empty.dir/codegen:
.PHONY : tests/CMakeFiles/empty.dir/codegen

tests/CMakeFiles/empty.dir/empty.c.o: tests/CMakeFiles/empty.dir/flags.make
tests/CMakeFiles/empty.dir/empty.c.o: tests/empty.c
tests/CMakeFiles/empty.dir/empty.c.o: tests/CMakeFiles/empty.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pancake/Documents/Bucket/lib/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/empty.dir/empty.c.o"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/empty.dir/empty.c.o -MF CMakeFiles/empty.dir/empty.c.o.d -o CMakeFiles/empty.dir/empty.c.o -c /home/pancake/Documents/Bucket/lib/glfw/tests/empty.c

tests/CMakeFiles/empty.dir/empty.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/empty.dir/empty.c.i"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pancake/Documents/Bucket/lib/glfw/tests/empty.c > CMakeFiles/empty.dir/empty.c.i

tests/CMakeFiles/empty.dir/empty.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/empty.dir/empty.c.s"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pancake/Documents/Bucket/lib/glfw/tests/empty.c -o CMakeFiles/empty.dir/empty.c.s

tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: tests/CMakeFiles/empty.dir/flags.make
tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: deps/tinycthread.c
tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o: tests/CMakeFiles/empty.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pancake/Documents/Bucket/lib/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o -MF CMakeFiles/empty.dir/__/deps/tinycthread.c.o.d -o CMakeFiles/empty.dir/__/deps/tinycthread.c.o -c /home/pancake/Documents/Bucket/lib/glfw/deps/tinycthread.c

tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/empty.dir/__/deps/tinycthread.c.i"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pancake/Documents/Bucket/lib/glfw/deps/tinycthread.c > CMakeFiles/empty.dir/__/deps/tinycthread.c.i

tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/empty.dir/__/deps/tinycthread.c.s"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && /sbin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pancake/Documents/Bucket/lib/glfw/deps/tinycthread.c -o CMakeFiles/empty.dir/__/deps/tinycthread.c.s

# Object files for target empty
empty_OBJECTS = \
"CMakeFiles/empty.dir/empty.c.o" \
"CMakeFiles/empty.dir/__/deps/tinycthread.c.o"

# External object files for target empty
empty_EXTERNAL_OBJECTS =

tests/empty: tests/CMakeFiles/empty.dir/empty.c.o
tests/empty: tests/CMakeFiles/empty.dir/__/deps/tinycthread.c.o
tests/empty: tests/CMakeFiles/empty.dir/build.make
tests/empty: tests/CMakeFiles/empty.dir/compiler_depend.ts
tests/empty: src/libglfw3.a
tests/empty: /usr/lib/libm.so
tests/empty: /usr/lib/librt.a
tests/empty: tests/CMakeFiles/empty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/pancake/Documents/Bucket/lib/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable empty"
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/empty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/empty.dir/build: tests/empty
.PHONY : tests/CMakeFiles/empty.dir/build

tests/CMakeFiles/empty.dir/clean:
	cd /home/pancake/Documents/Bucket/lib/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/empty.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/empty.dir/clean

tests/CMakeFiles/empty.dir/depend:
	cd /home/pancake/Documents/Bucket/lib/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pancake/Documents/Bucket/lib/glfw /home/pancake/Documents/Bucket/lib/glfw/tests /home/pancake/Documents/Bucket/lib/glfw /home/pancake/Documents/Bucket/lib/glfw/tests /home/pancake/Documents/Bucket/lib/glfw/tests/CMakeFiles/empty.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/empty.dir/depend

