project(SysY-Compiler)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)


add_executable(SysY-Compiler src/main.cpp src/Lexer/Lexer.cpp src/Lexer/Lexer.h src/Parser/Parser.cpp src/Parser/Parser.h src/Lexer/LexType.h src/SymbolManager/Symbol.cpp src/SymbolManager/Symbol.h src/ErrorCheck/ErrorCheck.cpp src/ErrorCheck/ErrorCheck.h src/SymbolManager/Func.cpp)