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
include standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/depend.make

# Include the progress variables for this target.
include standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/progress.make

# Include the compile flags for this target's objects.
include standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.o: ../standards/ieee-2030.5/tests/xml/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/main.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/main.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/main.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/main.cpp > CMakeFiles/xml_tests.dir/main.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/main.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/main.cpp -o CMakeFiles/xml_tests.dir/main.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/dcap_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/dcap_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dcap_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/dcap_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dcap_tests.cpp > CMakeFiles/xml_tests.dir/dcap_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/dcap_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dcap_tests.cpp -o CMakeFiles/xml_tests.dir/dcap_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/sdev_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/sdev_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sdev_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/sdev_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sdev_tests.cpp > CMakeFiles/xml_tests.dir/sdev_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/sdev_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sdev_tests.cpp -o CMakeFiles/xml_tests.dir/sdev_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/edev_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/edev_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/edev_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/edev_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/edev_tests.cpp > CMakeFiles/xml_tests.dir/edev_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/edev_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/edev_tests.cpp -o CMakeFiles/xml_tests.dir/edev_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/rg_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/rg_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rg_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/rg_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rg_tests.cpp > CMakeFiles/xml_tests.dir/rg_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/rg_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rg_tests.cpp -o CMakeFiles/xml_tests.dir/rg_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/dstat_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/dstat_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dstat_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/dstat_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dstat_tests.cpp > CMakeFiles/xml_tests.dir/dstat_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/dstat_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/dstat_tests.cpp -o CMakeFiles/xml_tests.dir/dstat_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/fsa_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/fsa_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/fsa_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/fsa_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/fsa_tests.cpp > CMakeFiles/xml_tests.dir/fsa_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/fsa_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/fsa_tests.cpp -o CMakeFiles/xml_tests.dir/fsa_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/frp_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/frp_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frp_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/frp_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frp_tests.cpp > CMakeFiles/xml_tests.dir/frp_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/frp_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frp_tests.cpp -o CMakeFiles/xml_tests.dir/frp_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/frq_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/frq_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frq_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/frq_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frq_tests.cpp > CMakeFiles/xml_tests.dir/frq_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/frq_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/frq_tests.cpp -o CMakeFiles/xml_tests.dir/frq_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/sub_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/sub_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sub_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/sub_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sub_tests.cpp > CMakeFiles/xml_tests.dir/sub_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/sub_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/sub_tests.cpp -o CMakeFiles/xml_tests.dir/sub_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/ntfy_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/ntfy_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/ntfy_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/ntfy_tests.cpp > CMakeFiles/xml_tests.dir/ntfy_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/ntfy_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/ntfy_tests.cpp -o CMakeFiles/xml_tests.dir/ntfy_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/rsps_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/rsps_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsps_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/rsps_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsps_tests.cpp > CMakeFiles/xml_tests.dir/rsps_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/rsps_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsps_tests.cpp -o CMakeFiles/xml_tests.dir/rsps_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/rsp_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/rsp_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsp_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/rsp_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsp_tests.cpp > CMakeFiles/xml_tests.dir/rsp_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/rsp_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/rsp_tests.cpp -o CMakeFiles/xml_tests.dir/rsp_tests.cpp.s

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.o: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/flags.make
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.o: ../standards/ieee-2030.5/tests/xml/tm_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.o"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/xml_tests.dir/tm_tests.cpp.o -c /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/tm_tests.cpp

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xml_tests.dir/tm_tests.cpp.i"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/tm_tests.cpp > CMakeFiles/xml_tests.dir/tm_tests.cpp.i

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xml_tests.dir/tm_tests.cpp.s"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml/tm_tests.cpp -o CMakeFiles/xml_tests.dir/tm_tests.cpp.s

# Object files for target xml_tests
xml_tests_OBJECTS = \
"CMakeFiles/xml_tests.dir/main.cpp.o" \
"CMakeFiles/xml_tests.dir/dcap_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/sdev_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/edev_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/rg_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/dstat_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/fsa_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/frp_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/frq_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/sub_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/rsps_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/rsp_tests.cpp.o" \
"CMakeFiles/xml_tests.dir/tm_tests.cpp.o"

# External object files for target xml_tests
xml_tests_EXTERNAL_OBJECTS =

bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/main.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dcap_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sdev_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/edev_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rg_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/dstat_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/fsa_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frp_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/frq_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/sub_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/ntfy_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsps_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/rsp_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/tm_tests.cpp.o
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/build.make
bin/xml_tests: lib/libgtest.a
bin/xml_tests: lib/libgtest_main.a
bin/xml_tests: standards/ieee-2030.5/xml/libXML_Validator.a
bin/xml_tests: utilities/libutilities.a
bin/xml_tests: lib/libgtest.a
bin/xml_tests: /usr/lib/libxerces-c.so
bin/xml_tests: standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/narmada/dev/doe-egot-system/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable ../../../../bin/xml_tests"
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xml_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/build: bin/xml_tests

.PHONY : standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/build

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/clean:
	cd /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml && $(CMAKE_COMMAND) -P CMakeFiles/xml_tests.dir/cmake_clean.cmake
.PHONY : standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/clean

standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/depend:
	cd /home/narmada/dev/doe-egot-system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/narmada/dev/doe-egot-system /home/narmada/dev/doe-egot-system/standards/ieee-2030.5/tests/xml /home/narmada/dev/doe-egot-system/build /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml /home/narmada/dev/doe-egot-system/build/standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : standards/ieee-2030.5/tests/xml/CMakeFiles/xml_tests.dir/depend
