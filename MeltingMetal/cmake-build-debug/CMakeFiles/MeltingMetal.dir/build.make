# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lww/CLionProjects/MeltingMetal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lww/CLionProjects/MeltingMetal/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MeltingMetal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MeltingMetal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MeltingMetal.dir/flags.make

CMakeFiles/MeltingMetal.dir/main.cpp.o: CMakeFiles/MeltingMetal.dir/flags.make
CMakeFiles/MeltingMetal.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lww/CLionProjects/MeltingMetal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MeltingMetal.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MeltingMetal.dir/main.cpp.o -c /Users/lww/CLionProjects/MeltingMetal/main.cpp

CMakeFiles/MeltingMetal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MeltingMetal.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lww/CLionProjects/MeltingMetal/main.cpp > CMakeFiles/MeltingMetal.dir/main.cpp.i

CMakeFiles/MeltingMetal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MeltingMetal.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lww/CLionProjects/MeltingMetal/main.cpp -o CMakeFiles/MeltingMetal.dir/main.cpp.s

# Object files for target MeltingMetal
MeltingMetal_OBJECTS = \
"CMakeFiles/MeltingMetal.dir/main.cpp.o"

# External object files for target MeltingMetal
MeltingMetal_EXTERNAL_OBJECTS =

MeltingMetal: CMakeFiles/MeltingMetal.dir/main.cpp.o
MeltingMetal: CMakeFiles/MeltingMetal.dir/build.make
MeltingMetal: CMakeFiles/MeltingMetal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lww/CLionProjects/MeltingMetal/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MeltingMetal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MeltingMetal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MeltingMetal.dir/build: MeltingMetal

.PHONY : CMakeFiles/MeltingMetal.dir/build

CMakeFiles/MeltingMetal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MeltingMetal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MeltingMetal.dir/clean

CMakeFiles/MeltingMetal.dir/depend:
	cd /Users/lww/CLionProjects/MeltingMetal/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lww/CLionProjects/MeltingMetal /Users/lww/CLionProjects/MeltingMetal /Users/lww/CLionProjects/MeltingMetal/cmake-build-debug /Users/lww/CLionProjects/MeltingMetal/cmake-build-debug /Users/lww/CLionProjects/MeltingMetal/cmake-build-debug/CMakeFiles/MeltingMetal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MeltingMetal.dir/depend

