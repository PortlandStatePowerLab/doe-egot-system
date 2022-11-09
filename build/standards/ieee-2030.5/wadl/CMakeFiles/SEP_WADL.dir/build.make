# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/narmada/dev/doe-egot-system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/narmada/dev/doe-egot-system/build

# Include any dependencies generated for this target.
include standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/depend.make

# Include the progress variables for this target.
include standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/progress.make

# Include the compile flags for this target's objects.
include standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/flags.make

standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.o: standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/flags.make
standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.o: ../standards/ieee-2030.5/wadl/wadl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SEP_WADL.dir/wadl.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/wadl/wadl.cpp

standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SEP_WADL.dir/wadl.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/wadl/wadl.cpp > CMakeFiles/SEP_WADL.dir/wadl.cpp.i

standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SEP_WADL.dir/wadl.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/wadl/wadl.cpp -o CMakeFiles/SEP_WADL.dir/wadl.cpp.s

# Object files for target SEP_WADL
SEP_WADL_OBJECTS = \
"CMakeFiles/SEP_WADL.dir/wadl.cpp.o"

# External object files for target SEP_WADL
SEP_WADL_EXTERNAL_OBJECTS =

standards/ieee-2030.5/wadl/libSEP_WADL.a: standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/wadl.cpp.o
standards/ieee-2030.5/wadl/libSEP_WADL.a: standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/build.make
standards/ieee-2030.5/wadl/libSEP_WADL.a: standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSEP_WADL.a"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && $(CMAKE_COMMAND) -P CMakeFiles/SEP_WADL.dir/cmake_clean_target.cmake
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SEP_WADL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/build: standards/ieee-2030.5/wadl/libSEP_WADL.a

.PHONY : standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/build

standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/clean:
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl && $(CMAKE_COMMAND) -P CMakeFiles/SEP_WADL.dir/cmake_clean.cmake
.PHONY : standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/clean

standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/depend:
	cd /home/narmada/dev/doe-egot-system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/narmada/dev/doe-egot-system /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/wadl /home/narmada/dev/doe-egot-system/build /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : standards/ieee-2030.5/wadl/CMakeFiles/SEP_WADL.dir/depend
