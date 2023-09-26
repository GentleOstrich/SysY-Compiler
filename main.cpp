//
// Created by yh on 2023/9/18.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer/Lexer.h"
#include "Lexer/LexType.h"
#include "Parser/Parser.h"

#define TEST
using namespace std;

#ifdef TEST
string INFILEPATH = R"(D:\University\Study\2023fall\compiler\SysY-Compiler\testfile.txt)";//
string OUTFILEPATH = R"(D:\University\Study\2023fall\compiler\SysY-Compiler\output.txt)";//
#else
string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
#endif

string source;
Lexer lexer;
Parser parser;

int main() {

    ifstream ifs(INFILEPATH);
    ofstream ofs(OUTFILEPATH);
    if (ifs.is_open() && ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());


    }
    return 0;
}
