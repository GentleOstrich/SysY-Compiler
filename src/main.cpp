//
// Created by yh on 2023/9/18.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Parser/Parser.h"
#include "NonterminalCharacter/Nonterminals.h"
#include "SymbolManager/SymbolTable.h"
#include "Visitor/Visitor.h"
using namespace std;

string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
string ERROR_OUTFILEPATH = "error.txt";
string GENERATE_CODE = "generate_code.txt";

string source = "";
Parser parser;

CompUnit* compUnit;
SymbolTable symbolTable;
Visitor visitor;


ifstream ifs(INFILEPATH);
ofstream ofs(OUTFILEPATH);
ofstream e_ofs(ERROR_OUTFILEPATH);
ofstream c_ofs(GENERATE_CODE);

//#define ERROR_CHECK
#ifdef ERROR_CHECK
struct Error {
    int line;
    char c;
};

Error errors[1000];
int e = 0;

bool cmp(Error error1, Error error2) {
    return error1.line < error2.line;
}
#endif
int main() {
    if (ifs.is_open() && ofs.is_open() && e_ofs.is_open() && c_ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        compUnit = parser.parseCompUnit();
        visitor.handleCompUnit(compUnit);
#ifdef ERROR_CHECK
        stable_sort(errors, errors + e, cmp);
        for (int i = 0; i < e; ++i) {
            e_ofs << errors[i].line << " " << errors[i].c << endl;
        }
#endif
    }
    return 0;
}