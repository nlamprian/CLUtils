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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paign10/github_repos/CLUtils

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paign10/github_repos/CLUtils/build

# Include any dependencies generated for this target.
include test/CMakeFiles/clUtils_tests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/clUtils_tests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/clUtils_tests.dir/flags.make

test/CMakeFiles/clUtils_tests.dir/tests.cpp.o: test/CMakeFiles/clUtils_tests.dir/flags.make
test/CMakeFiles/clUtils_tests.dir/tests.cpp.o: ../test/tests.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/paign10/github_repos/CLUtils/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/clUtils_tests.dir/tests.cpp.o"
	cd /home/paign10/github_repos/CLUtils/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/clUtils_tests.dir/tests.cpp.o -c /home/paign10/github_repos/CLUtils/test/tests.cpp

test/CMakeFiles/clUtils_tests.dir/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clUtils_tests.dir/tests.cpp.i"
	cd /home/paign10/github_repos/CLUtils/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/paign10/github_repos/CLUtils/test/tests.cpp > CMakeFiles/clUtils_tests.dir/tests.cpp.i

test/CMakeFiles/clUtils_tests.dir/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clUtils_tests.dir/tests.cpp.s"
	cd /home/paign10/github_repos/CLUtils/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/paign10/github_repos/CLUtils/test/tests.cpp -o CMakeFiles/clUtils_tests.dir/tests.cpp.s

test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.requires:
.PHONY : test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.requires

test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.provides: test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/clUtils_tests.dir/build.make test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.provides.build
.PHONY : test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.provides

test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.provides.build: test/CMakeFiles/clUtils_tests.dir/tests.cpp.o

# Object files for target clUtils_tests
clUtils_tests_OBJECTS = \
"CMakeFiles/clUtils_tests.dir/tests.cpp.o"

# External object files for target clUtils_tests
clUtils_tests_EXTERNAL_OBJECTS =

bin/clUtils_tests: test/CMakeFiles/clUtils_tests.dir/tests.cpp.o
bin/clUtils_tests: test/CMakeFiles/clUtils_tests.dir/build.make
bin/clUtils_tests: lib/libCLUtils.a
bin/clUtils_tests: /usr/local/lib/libgtest.a
bin/clUtils_tests: /usr/local/lib/libgtest_main.a
bin/clUtils_tests: /opt/AMDAPPSDK-2.9-1/lib/x86_64/libOpenCL.so
bin/clUtils_tests: test/CMakeFiles/clUtils_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/clUtils_tests"
	cd /home/paign10/github_repos/CLUtils/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clUtils_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/clUtils_tests.dir/build: bin/clUtils_tests
.PHONY : test/CMakeFiles/clUtils_tests.dir/build

test/CMakeFiles/clUtils_tests.dir/requires: test/CMakeFiles/clUtils_tests.dir/tests.cpp.o.requires
.PHONY : test/CMakeFiles/clUtils_tests.dir/requires

test/CMakeFiles/clUtils_tests.dir/clean:
	cd /home/paign10/github_repos/CLUtils/build/test && $(CMAKE_COMMAND) -P CMakeFiles/clUtils_tests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/clUtils_tests.dir/clean

test/CMakeFiles/clUtils_tests.dir/depend:
	cd /home/paign10/github_repos/CLUtils/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paign10/github_repos/CLUtils /home/paign10/github_repos/CLUtils/test /home/paign10/github_repos/CLUtils/build /home/paign10/github_repos/CLUtils/build/test /home/paign10/github_repos/CLUtils/build/test/CMakeFiles/clUtils_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/clUtils_tests.dir/depend

