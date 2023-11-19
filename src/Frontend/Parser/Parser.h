//
// Created by yh on 2023/9/25.
//

#ifndef SYSY_COMPILER_PARSER_H
#define SYSY_COMPILER_PARSER_H

#include <iostream>
#include <fstream>
#include "../NonterminalCharacter/Nonterminals.h"
#include "../Lexer/Lexer.h"

class Parser {
public:
    CompUnit *parseCompUnit();

    Decl *parseDecl();

    ConstDecl *parseConstDecl();

    BType *parseBType();

    ConstDef *parseConstDef();

    ConstInitVal *parseConstInitVal();

    VarDecl *parseVarDecl();

    VarDef *parseVarDef();

    InitVal *parseInitVal();

    FuncDef *parseFuncDef();

    MainFuncDef *parseMainFuncDef();

    FuncType *parseFuncType();

    FuncFParams *parseFuncFParams();

    FuncFParam *parseFuncFParam();

    Block *parseBlock();

    BlockItem *parseBlockItem();

    Stmt *parseStmt();

    ForStmt *parseForStmt();

    Exp *parseExp();

    Cond *parseCond();

    LVal *parseLVal();

    PrimaryExp *parsePrimaryExp();

    UnaryExp *parseUnaryExp();

    UnaryOp *parseUnaryOp();

    FuncRParams *parseFuncRParams();

    MulExp *parseMulExp();

    AddExp *parseAddExp();

    RelExp *parseRelExp();

    EqExp *parseEqExp();

    LAndExp *parseLAndExp();

    LOrExp *parseLOrExp();

    ConstExp *parseConstExp();

    Number *parseNumber();
};

#endif // SYSY_COMPILER_PARSER_H
