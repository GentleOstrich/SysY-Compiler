//
// Created by yh on 2023/9/18.
//
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Frontend/Parser/Parser.h"
#include "Frontend/NonterminalCharacter/Nonterminals.h"
#include "IR/SymbolManager/SymbolTable.h"
#include "IR/Visitor.h"

std::string INFILEPATH = "testfile.txt";
std::string OUTFILEPATH = "translate.txt";
std::string ERROR_OUTFILEPATH = "error.txt";
std::string GENERATE_CODE = "llvm_ir.txt";

std::string source;
Parser parser;

CompUnit* compUnit;
Visitor visitor;


std::ifstream ifs(INFILEPATH);
std::ofstream ofs(OUTFILEPATH);
std::ofstream e_ofs(ERROR_OUTFILEPATH);
std::ofstream c_ofs(GENERATE_CODE);


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
    if (!1) {
        std::cout << "1" << std::endl;
    }
    if (ifs.is_open() && ofs.is_open() && e_ofs.is_open() && c_ofs.is_open()) {
        source = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
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