# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mpkow\CLionProjects\lexer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug

# Include any dependencies generated for this target.
include googletest\lib\CMakeFiles\gtest_main.dir\depend.make

# Include the progress variables for this target.
include googletest\lib\CMakeFiles\gtest_main.dir\progress.make

# Include the compile flags for this target's objects.
include googletest\lib\CMakeFiles\gtest_main.dir\flags.make

googletest\lib\CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj: googletest\lib\CMakeFiles\gtest_main.dir\flags.make
googletest\lib\CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj: ..\googletest\lib\src\gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest/lib/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj"
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\gtest_main.dir\src\gtest_main.cc.obj /Fd..\..\lib\gtest_mainpdb_debug_postfix-NOTFOUND.pdb /FS -c C:\Users\mpkow\CLionProjects\lexer\googletest\lib\src\gtest_main.cc
<<
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug

googletest\lib\CMakeFiles\gtest_main.dir\src\gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\gtest_main.dir\src\gtest_main.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mpkow\CLionProjects\lexer\googletest\lib\src\gtest_main.cc
<<
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug

googletest\lib\CMakeFiles\gtest_main.dir\src\gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\gtest_main.dir\src\gtest_main.cc.s /c C:\Users\mpkow\CLionProjects\lexer\googletest\lib\src\gtest_main.cc
<<
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug

# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

lib\gtest_main.lib: googletest\lib\CMakeFiles\gtest_main.dir\src\gtest_main.cc.obj
lib\gtest_main.lib: googletest\lib\CMakeFiles\gtest_main.dir\build.make
lib\gtest_main.lib: googletest\lib\CMakeFiles\gtest_main.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\lib\gtest_main.lib"
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	$(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean_target.cmake
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\lib.exe /nologo /machine:X86 /out:..\..\lib\gtest_main.lib @CMakeFiles\gtest_main.dir\objects1.rsp 
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug

# Rule to build all files generated by this target.
googletest\lib\CMakeFiles\gtest_main.dir\build: lib\gtest_main.lib

.PHONY : googletest\lib\CMakeFiles\gtest_main.dir\build

googletest\lib\CMakeFiles\gtest_main.dir\clean:
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib
	$(CMAKE_COMMAND) -P CMakeFiles\gtest_main.dir\cmake_clean.cmake
	cd C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug
.PHONY : googletest\lib\CMakeFiles\gtest_main.dir\clean

googletest\lib\CMakeFiles\gtest_main.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\mpkow\CLionProjects\lexer C:\Users\mpkow\CLionProjects\lexer\googletest\lib C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib C:\Users\mpkow\CLionProjects\lexer\cmake-build-debug\googletest\lib\CMakeFiles\gtest_main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : googletest\lib\CMakeFiles\gtest_main.dir\depend

