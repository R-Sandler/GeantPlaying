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
CMAKE_SOURCE_DIR = /home/l3375/GeantPlaying/CopyExample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/l3375/GeantPlaying/CopyExample/build

# Include any dependencies generated for this target.
include CMakeFiles/NE697G4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NE697G4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NE697G4.dir/flags.make

CMakeFiles/NE697G4.dir/src/ne697g4.cc.o: CMakeFiles/NE697G4.dir/flags.make
CMakeFiles/NE697G4.dir/src/ne697g4.cc.o: ../src/ne697g4.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/l3375/GeantPlaying/CopyExample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NE697G4.dir/src/ne697g4.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NE697G4.dir/src/ne697g4.cc.o -c /home/l3375/GeantPlaying/CopyExample/src/ne697g4.cc

CMakeFiles/NE697G4.dir/src/ne697g4.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NE697G4.dir/src/ne697g4.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/l3375/GeantPlaying/CopyExample/src/ne697g4.cc > CMakeFiles/NE697G4.dir/src/ne697g4.cc.i

CMakeFiles/NE697G4.dir/src/ne697g4.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NE697G4.dir/src/ne697g4.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/l3375/GeantPlaying/CopyExample/src/ne697g4.cc -o CMakeFiles/NE697G4.dir/src/ne697g4.cc.s

CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.requires:

.PHONY : CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.requires

CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.provides: CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.requires
	$(MAKE) -f CMakeFiles/NE697G4.dir/build.make CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.provides.build
.PHONY : CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.provides

CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.provides.build: CMakeFiles/NE697G4.dir/src/ne697g4.cc.o


# Object files for target NE697G4
NE697G4_OBJECTS = \
"CMakeFiles/NE697G4.dir/src/ne697g4.cc.o"

# External object files for target NE697G4
NE697G4_EXTERNAL_OBJECTS =

NE697G4: CMakeFiles/NE697G4.dir/src/ne697g4.cc.o
NE697G4: CMakeFiles/NE697G4.dir/build.make
NE697G4: lib/libne697g4.so
NE697G4: /usr/local/lib/libG4Tree.so
NE697G4: /usr/local/lib/libG4GMocren.so
NE697G4: /usr/local/lib/libG4visHepRep.so
NE697G4: /usr/local/lib/libG4RayTracer.so
NE697G4: /usr/local/lib/libG4VRML.so
NE697G4: /usr/local/lib/libG4OpenGL.so
NE697G4: /usr/local/lib/libG4gl2ps.so
NE697G4: /usr/local/lib/libG4interfaces.so
NE697G4: /usr/local/lib/libG4persistency.so
NE697G4: /usr/local/lib/libG4error_propagation.so
NE697G4: /usr/local/lib/libG4readout.so
NE697G4: /usr/local/lib/libG4physicslists.so
NE697G4: /usr/local/lib/libG4parmodels.so
NE697G4: /usr/local/lib/libG4FR.so
NE697G4: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.9.5
NE697G4: /usr/lib/x86_64-linux-gnu/libGLU.so
NE697G4: /usr/lib/x86_64-linux-gnu/libGL.so
NE697G4: /usr/local/lib/libG4vis_management.so
NE697G4: /usr/local/lib/libG4modeling.so
NE697G4: /usr/lib/x86_64-linux-gnu/libXm.so
NE697G4: /usr/lib/x86_64-linux-gnu/libXmu.so
NE697G4: /usr/lib/x86_64-linux-gnu/libXext.so
NE697G4: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.9.5
NE697G4: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.9.5
NE697G4: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.9.5
NE697G4: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.9.5
NE697G4: /usr/lib/x86_64-linux-gnu/libXt.so
NE697G4: /usr/lib/x86_64-linux-gnu/libSM.so
NE697G4: /usr/lib/x86_64-linux-gnu/libICE.so
NE697G4: /usr/lib/x86_64-linux-gnu/libX11.so
NE697G4: /usr/local/lib/libG4run.so
NE697G4: /usr/local/lib/libG4event.so
NE697G4: /usr/local/lib/libG4tracking.so
NE697G4: /usr/local/lib/libG4processes.so
NE697G4: /usr/local/lib/libG4analysis.so
NE697G4: /usr/lib/x86_64-linux-gnu/libexpat.so
NE697G4: /usr/local/lib/libG4digits_hits.so
NE697G4: /usr/local/lib/libG4track.so
NE697G4: /usr/local/lib/libG4particles.so
NE697G4: /usr/local/lib/libG4geometry.so
NE697G4: /usr/local/lib/libG4materials.so
NE697G4: /usr/local/lib/libG4graphics_reps.so
NE697G4: /usr/local/lib/libG4intercoms.so
NE697G4: /usr/local/lib/libG4global.so
NE697G4: /usr/local/lib/libG4clhep.so
NE697G4: /usr/local/lib/libG4zlib.so
NE697G4: CMakeFiles/NE697G4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/l3375/GeantPlaying/CopyExample/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NE697G4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NE697G4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NE697G4.dir/build: NE697G4

.PHONY : CMakeFiles/NE697G4.dir/build

CMakeFiles/NE697G4.dir/requires: CMakeFiles/NE697G4.dir/src/ne697g4.cc.o.requires

.PHONY : CMakeFiles/NE697G4.dir/requires

CMakeFiles/NE697G4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NE697G4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NE697G4.dir/clean

CMakeFiles/NE697G4.dir/depend:
	cd /home/l3375/GeantPlaying/CopyExample/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/l3375/GeantPlaying/CopyExample /home/l3375/GeantPlaying/CopyExample /home/l3375/GeantPlaying/CopyExample/build /home/l3375/GeantPlaying/CopyExample/build /home/l3375/GeantPlaying/CopyExample/build/CMakeFiles/NE697G4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NE697G4.dir/depend

