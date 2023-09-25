//
// Created by yh on 2023/9/18.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer/Lexer.h"
#include "Lexer/LexType.h"

#define TEST
using namespace std;

#ifdef TEST
string INFILEPATH = R"(/home/yh/SysY-Compiler/testfile.txt)";//
string OUTFILEPATH = R"(/home/yh/SysY-Compiler/output.txt)";//
#else
string INFILEPATH = "testfile.txt";
string OUTFILEPATH = "output.txt";
#endif
extern vector<pair<Token, int>> tokenVec;
int main() {
    Lexer lexer;
    ifstream ifs(INFILEPATH);
    ofstream ofs(OUTFILEPATH);
    string source;
    if (ifs.is_open() && ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        lexer.scan(source);
        for (auto &i : tokenVec) {
            cout << i.first.first << " " << LexType2String(i.first.second) << " " << i.second << endl;
        }
    }


    return 0;
}
