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
CMAKE_SOURCE_DIR = /Users/lww/CLionProjects/attributeLines

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lww/CLionProjects/attributeLines/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/attributeLines.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/attributeLines.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/attributeLines.dir/flags.make

CMakeFiles/attributeLines.dir/main.cpp.o: CMakeFiles/attributeLines.dir/flags.make
CMakeFiles/attributeLines.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lww/CLionProjects/attributeLines/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/attributeLines.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/attributeLines.dir/main.cpp.o -c /Users/lww/CLionProjects/attributeLines/main.cpp

CMakeFiles/attributeLines.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/attributeLines.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lww/CLionProjects/attributeLines/main.cpp > CMakeFiles/attributeLines.dir/main.cpp.i

CMakeFiles/attributeLines.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/attributeLines.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lww/CLionProjects/attributeLines/main.cpp -o CMakeFiles/attributeLines.dir/main.cpp.s

# Object files for target attributeLines
attributeLines_OBJECTS = \
"CMakeFiles/attributeLines.dir/main.cpp.o"

# External object files for target attributeLines
attributeLines_EXTERNAL_OBJECTS =

attributeLines: CMakeFiles/attributeLines.dir/main.cpp.o
attributeLines: CMakeFiles/attributeLines.dir/build.make
attributeLines: CMakeFiles/attributeLines.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lww/CLionProjects/attributeLines/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable attributeLines"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/attributeLines.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/attributeLines.dir/build: attributeLines

.PHONY : CMakeFiles/attributeLines.dir/build

CMakeFiles/attributeLines.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/attributeLines.dir/cmake_clean.cmake
.PHONY : CMakeFiles/attributeLines.dir/clean

CMakeFiles/attributeLines.dir/depend:
	cd /Users/lww/CLionProjects/attributeLines/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lww/CLionProjects/attributeLines /Users/lww/CLionProjects/attributeLines /Users/lww/CLionProjects/attributeLines/cmake-build-debug /Users/lww/CLionProjects/attributeLines/cmake-build-debug /Users/lww/CLionProjects/attributeLines/cmake-build-debug/CMakeFiles/attributeLines.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/attributeLines.dir/depend

