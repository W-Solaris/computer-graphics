# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/wucunhao/Graphics/computer-graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wucunhao/Graphics/computer-graphics/build

# Include any dependencies generated for this target.
include CMakeFiles/PA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA.dir/flags.make

CMakeFiles/PA.dir/src/image.cpp.o: CMakeFiles/PA.dir/flags.make
CMakeFiles/PA.dir/src/image.cpp.o: ../src/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PA.dir/src/image.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA.dir/src/image.cpp.o -c /home/wucunhao/Graphics/computer-graphics/src/image.cpp

CMakeFiles/PA.dir/src/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA.dir/src/image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wucunhao/Graphics/computer-graphics/src/image.cpp > CMakeFiles/PA.dir/src/image.cpp.i

CMakeFiles/PA.dir/src/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA.dir/src/image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wucunhao/Graphics/computer-graphics/src/image.cpp -o CMakeFiles/PA.dir/src/image.cpp.s

CMakeFiles/PA.dir/src/main.cpp.o: CMakeFiles/PA.dir/flags.make
CMakeFiles/PA.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PA.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA.dir/src/main.cpp.o -c /home/wucunhao/Graphics/computer-graphics/src/main.cpp

CMakeFiles/PA.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wucunhao/Graphics/computer-graphics/src/main.cpp > CMakeFiles/PA.dir/src/main.cpp.i

CMakeFiles/PA.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wucunhao/Graphics/computer-graphics/src/main.cpp -o CMakeFiles/PA.dir/src/main.cpp.s

CMakeFiles/PA.dir/src/mesh.cpp.o: CMakeFiles/PA.dir/flags.make
CMakeFiles/PA.dir/src/mesh.cpp.o: ../src/mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PA.dir/src/mesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA.dir/src/mesh.cpp.o -c /home/wucunhao/Graphics/computer-graphics/src/mesh.cpp

CMakeFiles/PA.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA.dir/src/mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wucunhao/Graphics/computer-graphics/src/mesh.cpp > CMakeFiles/PA.dir/src/mesh.cpp.i

CMakeFiles/PA.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA.dir/src/mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wucunhao/Graphics/computer-graphics/src/mesh.cpp -o CMakeFiles/PA.dir/src/mesh.cpp.s

CMakeFiles/PA.dir/src/scene_parser.cpp.o: CMakeFiles/PA.dir/flags.make
CMakeFiles/PA.dir/src/scene_parser.cpp.o: ../src/scene_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PA.dir/src/scene_parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA.dir/src/scene_parser.cpp.o -c /home/wucunhao/Graphics/computer-graphics/src/scene_parser.cpp

CMakeFiles/PA.dir/src/scene_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA.dir/src/scene_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wucunhao/Graphics/computer-graphics/src/scene_parser.cpp > CMakeFiles/PA.dir/src/scene_parser.cpp.i

CMakeFiles/PA.dir/src/scene_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA.dir/src/scene_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wucunhao/Graphics/computer-graphics/src/scene_parser.cpp -o CMakeFiles/PA.dir/src/scene_parser.cpp.s

CMakeFiles/PA.dir/src/texture.cpp.o: CMakeFiles/PA.dir/flags.make
CMakeFiles/PA.dir/src/texture.cpp.o: ../src/texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PA.dir/src/texture.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA.dir/src/texture.cpp.o -c /home/wucunhao/Graphics/computer-graphics/src/texture.cpp

CMakeFiles/PA.dir/src/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA.dir/src/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wucunhao/Graphics/computer-graphics/src/texture.cpp > CMakeFiles/PA.dir/src/texture.cpp.i

CMakeFiles/PA.dir/src/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA.dir/src/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wucunhao/Graphics/computer-graphics/src/texture.cpp -o CMakeFiles/PA.dir/src/texture.cpp.s

# Object files for target PA
PA_OBJECTS = \
"CMakeFiles/PA.dir/src/image.cpp.o" \
"CMakeFiles/PA.dir/src/main.cpp.o" \
"CMakeFiles/PA.dir/src/mesh.cpp.o" \
"CMakeFiles/PA.dir/src/scene_parser.cpp.o" \
"CMakeFiles/PA.dir/src/texture.cpp.o"

# External object files for target PA
PA_EXTERNAL_OBJECTS =

../bin/PA: CMakeFiles/PA.dir/src/image.cpp.o
../bin/PA: CMakeFiles/PA.dir/src/main.cpp.o
../bin/PA: CMakeFiles/PA.dir/src/mesh.cpp.o
../bin/PA: CMakeFiles/PA.dir/src/scene_parser.cpp.o
../bin/PA: CMakeFiles/PA.dir/src/texture.cpp.o
../bin/PA: CMakeFiles/PA.dir/build.make
../bin/PA: deps/vecmath/libvecmath.a
../bin/PA: CMakeFiles/PA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wucunhao/Graphics/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../bin/PA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA.dir/build: ../bin/PA

.PHONY : CMakeFiles/PA.dir/build

CMakeFiles/PA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA.dir/clean

CMakeFiles/PA.dir/depend:
	cd /home/wucunhao/Graphics/computer-graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wucunhao/Graphics/computer-graphics /home/wucunhao/Graphics/computer-graphics /home/wucunhao/Graphics/computer-graphics/build /home/wucunhao/Graphics/computer-graphics/build /home/wucunhao/Graphics/computer-graphics/build/CMakeFiles/PA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PA.dir/depend

