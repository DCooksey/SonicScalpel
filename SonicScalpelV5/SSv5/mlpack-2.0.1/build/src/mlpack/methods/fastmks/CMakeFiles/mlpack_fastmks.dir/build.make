# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build"

# Include any dependencies generated for this target.
include src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/depend.make

# Include the progress variables for this target.
include src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/progress.make

# Include the compile flags for this target's objects.
include src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/flags.make

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/flags.make
src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o: ../src/mlpack/methods/fastmks/fastmks_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o"
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o -c "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/src/mlpack/methods/fastmks/fastmks_main.cpp"

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.i"
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/src/mlpack/methods/fastmks/fastmks_main.cpp" > CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.i

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.s"
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/src/mlpack/methods/fastmks/fastmks_main.cpp" -o CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.s

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.requires:
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.requires

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.provides: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.requires
	$(MAKE) -f src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/build.make src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.provides.build
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.provides

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.provides.build: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o

# Object files for target mlpack_fastmks
mlpack_fastmks_OBJECTS = \
"CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o"

# External object files for target mlpack_fastmks
mlpack_fastmks_EXTERNAL_OBJECTS =

bin/mlpack_fastmks: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o
bin/mlpack_fastmks: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/build.make
bin/mlpack_fastmks: lib/libmlpack.so.2.0
bin/mlpack_fastmks: /usr/lib/libarmadillo.so
bin/mlpack_fastmks: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
bin/mlpack_fastmks: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
bin/mlpack_fastmks: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
bin/mlpack_fastmks: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../bin/mlpack_fastmks"
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mlpack_fastmks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/build: bin/mlpack_fastmks
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/build

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/requires: src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/fastmks_main.cpp.o.requires
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/requires

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/clean:
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" && $(CMAKE_COMMAND) -P CMakeFiles/mlpack_fastmks.dir/cmake_clean.cmake
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/clean

src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/depend:
	cd "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1" "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/src/mlpack/methods/fastmks" "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build" "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks" "/home/dean/Dropbox/University Work/GOLDSMITHS/YEAR THREE/Final Project/SonicScalpelV5/SSv5/mlpack-2.0.1/build/src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/mlpack/methods/fastmks/CMakeFiles/mlpack_fastmks.dir/depend
