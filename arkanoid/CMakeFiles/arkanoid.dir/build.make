# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\IPS\Projects\CppDistro\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\IPS\Projects\CppDistro\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\IPS\Projects\CppDistro\myGeme\Arkanoid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\IPS\Projects\CppDistro\myGeme\Arkanoid

# Include any dependencies generated for this target.
include arkanoid/CMakeFiles/arkanoid.dir/depend.make

# Include the progress variables for this target.
include arkanoid/CMakeFiles/arkanoid.dir/progress.make

# Include the compile flags for this target's objects.
include arkanoid/CMakeFiles/arkanoid.dir/flags.make

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj: arkanoid/CMakeFiles/arkanoid.dir/flags.make
arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj: arkanoid/CMakeFiles/arkanoid.dir/includes_CXX.rsp
arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj: arkanoid/arkanoid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\IPS\Projects\CppDistro\myGeme\Arkanoid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj"
	cd /d C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid && C:\IPS\Projects\CppDistro\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\arkanoid.dir\arkanoid.cpp.obj -c C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid\arkanoid.cpp

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arkanoid.dir/arkanoid.cpp.i"
	cd /d C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid && C:\IPS\Projects\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid\arkanoid.cpp > CMakeFiles\arkanoid.dir\arkanoid.cpp.i

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arkanoid.dir/arkanoid.cpp.s"
	cd /d C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid && C:\IPS\Projects\CppDistro\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid\arkanoid.cpp -o CMakeFiles\arkanoid.dir\arkanoid.cpp.s

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.requires:

.PHONY : arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.requires

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.provides: arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.requires
	$(MAKE) -f arkanoid\CMakeFiles\arkanoid.dir\build.make arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.provides.build
.PHONY : arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.provides

arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.provides.build: arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj


# Object files for target arkanoid
arkanoid_OBJECTS = \
"CMakeFiles/arkanoid.dir/arkanoid.cpp.obj"

# External object files for target arkanoid
arkanoid_EXTERNAL_OBJECTS =

arkanoid/arkanoid.exe: arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj
arkanoid/arkanoid.exe: arkanoid/CMakeFiles/arkanoid.dir/build.make
arkanoid/arkanoid.exe: C:/IPS/Projects/CppDistro/MinGW/lib/libsfml-window-s.a
arkanoid/arkanoid.exe: C:/IPS/Projects/CppDistro/MinGW/lib/libsfml-graphics-s.a
arkanoid/arkanoid.exe: C:/IPS/Projects/CppDistro/MinGW/lib/libsfml-system-s.a
arkanoid/arkanoid.exe: C:/IPS/Projects/CppDistro/MinGW/lib/libfreetype.a
arkanoid/arkanoid.exe: C:/IPS/Projects/CppDistro/MinGW/lib/libjpeg.a
arkanoid/arkanoid.exe: arkanoid/CMakeFiles/arkanoid.dir/linklibs.rsp
arkanoid/arkanoid.exe: arkanoid/CMakeFiles/arkanoid.dir/objects1.rsp
arkanoid/arkanoid.exe: arkanoid/CMakeFiles/arkanoid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\IPS\Projects\CppDistro\myGeme\Arkanoid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable arkanoid.exe"
	cd /d C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\arkanoid.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
arkanoid/CMakeFiles/arkanoid.dir/build: arkanoid/arkanoid.exe

.PHONY : arkanoid/CMakeFiles/arkanoid.dir/build

arkanoid/CMakeFiles/arkanoid.dir/requires: arkanoid/CMakeFiles/arkanoid.dir/arkanoid.cpp.obj.requires

.PHONY : arkanoid/CMakeFiles/arkanoid.dir/requires

arkanoid/CMakeFiles/arkanoid.dir/clean:
	cd /d C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid && $(CMAKE_COMMAND) -P CMakeFiles\arkanoid.dir\cmake_clean.cmake
.PHONY : arkanoid/CMakeFiles/arkanoid.dir/clean

arkanoid/CMakeFiles/arkanoid.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\IPS\Projects\CppDistro\myGeme\Arkanoid C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid C:\IPS\Projects\CppDistro\myGeme\Arkanoid C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid C:\IPS\Projects\CppDistro\myGeme\Arkanoid\arkanoid\CMakeFiles\arkanoid.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : arkanoid/CMakeFiles/arkanoid.dir/depend

