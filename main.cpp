//
// Created by yh on 2023/9/18.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer/Lexer.h"
#include "Lexer/LexType.h"
#include "Parser/Parser.h"
#include "ErrorCheck/ErrorCheck.h"
#include "SymbolManager/Symbol.h"
#include "SymbolManager/SymbolTable.h"

#define TEST
using namespace std;

#ifdef TEST
string INFILEPATH = R"(D:\University\Study\2023fall\compiler\SysY-Compiler\testfile.txt)";//
string OUTFILEPATH = R"(D:\University\Study\2023fall\Compiler\SysY-Compiler\output.txt)";//
string ERROR_OUTFILEPATH = R"(D:\University\Study\2023fall\Compiler\SysY-Compiler\error.txt)";//
#else
string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
string ERROR_OUTFILEPATH = "error.txt";
#endif

string source = "";
Lexer lexer;
Parser parser;

int symbolTableId = 0;

ErrorCheck errorCheck;
vector<SymbolTable> symbolTables;

ifstream ifs(INFILEPATH);
ofstream ofs(OUTFILEPATH);
ofstream e_ofs(ERROR_OUTFILEPATH);

int main() {
    SymbolTable root(0,0,-1);
    symbolTables.push_back(root);

    if (ifs.is_open() && ofs.is_open() && e_ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        parser.parseCompUnit();
    }
    return 0;
}
