//
// Created by lyh on 10/12/2023.
//
#include "../SymbolManager/Symbol.h"
#include "../Lexer/Lexer.h"
#include "ErrorCheck.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

#define tkWord token.second
#define printError(lineNum, type, info) e_ofs << lineNum << " " << type << " " << info << endl
#define LineNum lexer.getLineNum()

extern Lexer lexer;
extern Token token;
extern ofstream e_ofs;
extern int symbolId;
extern vector<Symbol> symbols;
extern stack<int> symbolTable;
ErrorCheck errorCheck;

int ErrorCheck::bCheck(string word, bool fun){
    for (int i = symbolId - 1 ; i >= symbolTable.top(); i-- ) {
        if (symbols[i].word == word && ((symbols[i].type != -1 && !fun) || (symbols[i].type == -1 && fun))){
            printError(LineNum, "b", "名字重定义");
            return 1;
        }
    }
    return 0;
}

int ErrorCheck::cCheck(string word, bool fun){
    for (int i = symbolId - 1; i >= 0; i--) {
        if (symbols[i].word == word && ((symbols[i].type != -1 && !fun) || (symbols[i].type == -1 && fun))){
            return 0;
        }
    }
    printError(LineNum, "b", "未定义的名字");
    return 1;
}

int ErrorCheck::dCheck(string word, int num){
    for (int i = symbolId - 1; i >= 0; i--) {
        if (symbols[i].word == word && symbols[i].type == -1){
            if (symbols[i].paramNum != num) {
                printError(LineNum, "d", "函数参数个数不匹配");
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1;
}

int ErrorCheck::eCheck(){
    return 0;
}

int ErrorCheck::fCheck(){
    return 0;
}

int ErrorCheck::gCheck(){
    return 0;
}
int ErrorCheck::hCheck(){
    return 0;
}

int ErrorCheck::lCheck(){
    return 0;
}

int ErrorCheck::mCheck(){
    return 0;
}