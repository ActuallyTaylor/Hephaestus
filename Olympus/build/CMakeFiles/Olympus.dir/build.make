# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.23.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.23.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build

# Include any dependencies generated for this target.
include CMakeFiles/Olympus.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Olympus.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Olympus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Olympus.dir/flags.make

CMakeFiles/Olympus.dir/main.cpp.o: CMakeFiles/Olympus.dir/flags.make
CMakeFiles/Olympus.dir/main.cpp.o: ../main.cpp
CMakeFiles/Olympus.dir/main.cpp.o: CMakeFiles/Olympus.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Olympus.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Olympus.dir/main.cpp.o -MF CMakeFiles/Olympus.dir/main.cpp.o.d -o CMakeFiles/Olympus.dir/main.cpp.o -c /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/main.cpp

CMakeFiles/Olympus.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Olympus.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/main.cpp > CMakeFiles/Olympus.dir/main.cpp.i

CMakeFiles/Olympus.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Olympus.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/main.cpp -o CMakeFiles/Olympus.dir/main.cpp.s

# Object files for target Olympus
Olympus_OBJECTS = \
"CMakeFiles/Olympus.dir/main.cpp.o"

# External object files for target Olympus
Olympus_EXTERNAL_OBJECTS =

Olympus: CMakeFiles/Olympus.dir/main.cpp.o
Olympus: CMakeFiles/Olympus.dir/build.make
Olympus: Hephaestus/libHephaestus.a
Olympus: Hephaestus/Library/openal-soft/libopenal.1.21.1.dylib
Olympus: /usr/local/lib/libglfw.3.3.dylib
Olympus: /usr/local/lib/libGLEW.2.2.0.dylib
Olympus: /usr/local/lib/libfreetype.dylib
Olympus: CMakeFiles/Olympus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Olympus"
	/usr/local/Cellar/cmake/3.23.1/bin/cmake -E copy_directory /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/Resources /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Olympus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Olympus.dir/build: Olympus
.PHONY : CMakeFiles/Olympus.dir/build

CMakeFiles/Olympus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Olympus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Olympus.dir/clean

CMakeFiles/Olympus.dir/depend:
	cd /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build /Users/zacharylineman/Developer/GitHub/Hephaestus/Olympus/build/CMakeFiles/Olympus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Olympus.dir/depend
