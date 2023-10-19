//
// Created by yh on 2023/9/25.
//
#include "../Lexer/Lexer.h"

#ifndef SYSY_COMPILER_PARSER_H
#define SYSY_COMPILER_PARSER_H


class Parser {
public:
    int parseCompUnit();

    int parseDecl();

    int parseConstDecl();

    int parseBType();

    int parseConstDef();

    int parseConstInitVal();

    int parseVarDecl();

    int parseVarDef();

    int parseInitVal();

    int parseFuncDef();

    int parseMainFuncDef();

    int parseFuncType();

    int parseFuncFParams(int tempSymbolId);

    int parseFuncFParam();

    int parseBlock(int funcType);

    int parseBlockItem(int FuncType);

    int parseStmt(int funcType, int isFor);

    int parseForStmt();

    int parseExp();

    int parseCond();

    int parseLVal(int change);

    int parsePrimaryExp();

    int parseNumber();

    int parseUnaryExp();

    int parseUnaryOp();

    int parseFuncRParams(string funcName, int tempFuncLineNum);

    int parseMulExp();

    int parseAddExp();

    int parseRelExp();

    int parseEqExp();

    int parseLAndExp();

    int parseLOrExp();

    int parseConstExp();

};


#endif //SYSY_COMPILER_PARSER_H
