# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.3.6\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.3.6\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\University\Study\2023fall\Compiler\SysY-Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SysY-Compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SysY-Compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SysY-Compiler.dir/flags.make

CMakeFiles/SysY-Compiler.dir/src/main.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/main.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\main.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\main.cpp

CMakeFiles/SysY-Compiler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/main.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\main.cpp > CMakeFiles\SysY-Compiler.dir\src\main.cpp.i

CMakeFiles/SysY-Compiler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/main.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\main.cpp -o CMakeFiles\SysY-Compiler.dir\src\main.cpp.s

CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.obj: ../src/Lexer/Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\Lexer\Lexer.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Lexer\Lexer.cpp

CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Lexer\Lexer.cpp > CMakeFiles\SysY-Compiler.dir\src\Lexer\Lexer.cpp.i

CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Lexer\Lexer.cpp -o CMakeFiles\SysY-Compiler.dir\src\Lexer\Lexer.cpp.s

CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.obj: ../src/Parser/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\Parser\Parser.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Parser\Parser.cpp

CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Parser\Parser.cpp > CMakeFiles\SysY-Compiler.dir\src\Parser\Parser.cpp.i

CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\Parser\Parser.cpp -o CMakeFiles\SysY-Compiler.dir\src\Parser\Parser.cpp.s

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.obj: ../src/SymbolManager/Symbol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Symbol.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Symbol.cpp

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Symbol.cpp > CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Symbol.cpp.i

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Symbol.cpp -o CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Symbol.cpp.s

CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.obj: ../src/ErrorCheck/ErrorCheck.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\ErrorCheck\ErrorCheck.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\ErrorCheck\ErrorCheck.cpp

CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\ErrorCheck\ErrorCheck.cpp > CMakeFiles\SysY-Compiler.dir\src\ErrorCheck\ErrorCheck.cpp.i

CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\ErrorCheck\ErrorCheck.cpp -o CMakeFiles\SysY-Compiler.dir\src\ErrorCheck\ErrorCheck.cpp.s

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.obj: CMakeFiles/SysY-Compiler.dir/flags.make
CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.obj: ../src/SymbolManager/Func.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Func.cpp.obj -c D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Func.cpp

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Func.cpp > CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Func.cpp.i

CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\University\Study\2023fall\Compiler\SysY-Compiler\src\SymbolManager\Func.cpp -o CMakeFiles\SysY-Compiler.dir\src\SymbolManager\Func.cpp.s

# Object files for target SysY-Compiler
SysY__Compiler_OBJECTS = \
"CMakeFiles/SysY-Compiler.dir/src/main.cpp.obj" \
"CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.obj" \
"CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.obj" \
"CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.obj" \
"CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.obj" \
"CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.obj"

# External object files for target SysY-Compiler
SysY__Compiler_EXTERNAL_OBJECTS =

SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/main.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/Lexer/Lexer.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/Parser/Parser.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Symbol.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/ErrorCheck/ErrorCheck.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/src/SymbolManager/Func.cpp.obj
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/build.make
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/linklibs.rsp
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/objects1.rsp
SysY-Compiler.exe: CMakeFiles/SysY-Compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable SysY-Compiler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SysY-Compiler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SysY-Compiler.dir/build: SysY-Compiler.exe

.PHONY : CMakeFiles/SysY-Compiler.dir/build

CMakeFiles/SysY-Compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SysY-Compiler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SysY-Compiler.dir/clean

CMakeFiles/SysY-Compiler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\University\Study\2023fall\Compiler\SysY-Compiler D:\University\Study\2023fall\Compiler\SysY-Compiler D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug D:\University\Study\2023fall\Compiler\SysY-Compiler\cmake-build-debug\CMakeFiles\SysY-Compiler.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SysY-Compiler.dir/depend

