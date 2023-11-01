//
// Created by yh on 2023/9/18.
//
#include<algorithm>
#include <iostream>
#include <fstream>
#include "Parser/Parser.h"

using namespace std;

string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
string ERROR_OUTFILEPATH = "error.txt";

string source = "";
Parser parser;
ifstream ifs(INFILEPATH);
ofstream ofs(OUTFILEPATH);
ofstream e_ofs(ERROR_OUTFILEPATH);

struct Error {
    int line;
    char c;
};
Error errors[1000];
int e = 0;

bool cmp(Error error1, Error error2) {
    return error1.line < error2.line;
}

int main() {
    if (ifs.is_open() && ofs.is_open() && e_ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        parser.parseCompUnit();
        stable_sort(errors, errors + e, cmp);
        for (int i = 0; i < e; ++i) {
            e_ofs << errors[i].line << " " << errors[i].c << endl;
        }
    }
    return 0;
}