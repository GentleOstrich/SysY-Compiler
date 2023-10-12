//
// Created by lyh on 10/12/2023.
//
#include "../SymbolManager/Symbol.h"
#include "../SymbolManager/SymbolTable.h"
#include "../Lexer/Lexer.h"
#include "ErrorCheck.h"
#define tkWord token.second
#define printError(lineNum, type, info) e_ofs << lineNum << " " << type << " " << info << endl

extern vector<SymbolTable> symbolTables;
extern int symbolId;
extern int symbolTableId;
extern Lexer lexer;

int ErrorCheck::bCheck(){
    if (symbolTables[symbolId].exist(tkWord)) {
        printError(lexer.getLineNum,"b","名字重定义");
        return 1;
    } else {
        return 0;
    }   
}

int ErrorCheck::cCheck(){
    return 0;
}

int ErrorCheck::dCheck(){
    return 0;
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