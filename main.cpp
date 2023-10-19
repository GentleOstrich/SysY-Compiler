//
// Created by yh on 2023/9/18.
//
#include<algorithm>
#include <iostream>
#include <fstream>
#include "Parser/Parser.h"

using namespace std;

#define TEST
//#define Linux

#ifdef TEST
    #ifdef Linux
        string INFILEPATH = R"(/home/yh/SysY-Compiler/testfile.txt)";//
        string OUTFILEPATH = R"(/home/yh/SysY-Compiler/output.txt)";//
        string ERROR_OUTFILEPATH = R"(/home/yh/SysY-Compiler/error.txt)";//
    #else
        string INFILEPATH = R"(D:\University\Study\2023fall\compiler\SysY-Compiler\testfile.txt)";//
        string OUTFILEPATH = R"(D:\University\Study\2023fall\Compiler\SysY-Compiler\output.txt)";//
        string ERROR_OUTFILEPATH = R"(D:\University\Study\2023fall\Compiler\SysY-Compiler\error.txt)";//
    #endif
#else
string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
string ERROR_OUTFILEPATH = "error.txt";
#endif

string source = "";

Parser parser;

ifstream ifs(INFILEPATH);
ofstream ofs(OUTFILEPATH);
ofstream e_ofs(ERROR_OUTFILEPATH);

struct Error {
    int line;
    char c;
};

bool cmp(Error error1, Error error2) {
    return error1.line < error2.line;
}

Error errors[1000];
int e;

int main() {
    if (ifs.is_open() && ofs.is_open() && e_ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        parser.parseCompUnit();
    }

    stable_sort(errors, errors+e, cmp);

    for (int i = 0; i < e; ++ i) {
        e_ofs << errors[i].line << " " << errors[i].c << endl;
    }

    return 0;
}
