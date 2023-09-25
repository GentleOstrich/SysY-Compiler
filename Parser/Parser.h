//
// Created by yh on 2023/9/25.
//
#include "../Lexer/Lexer.h"

#ifndef SYSY_COMPILER_PARSER_H
#define SYSY_COMPILER_PARSER_H


class Parser {
public:
    int CompUnit();

    int Decl();

    int ConstDecl();

    int BType();

    int ConstDef();

    int ConstInitVal();

    int VarDecl();

    int VarDef();

    int InitVal();

    int FuncDef();

    int MainFuncDef();

    int FuncType();

    int FuncFParams();

    int FuncFParam();

    int Block();

    int BlockItem();

    int Stmt();

    int ForStmt();

    int Exp();

    int Cond();

    int LVal();

    int PrimaryExp();

    int Number();

    int UnaryExp();

    int UnaryOp();

    int FuncRParams();

    int MulExp();

    int AddExp();

    int RelExp();

    int EqExp();

    int LAndExp();

    int LOrExp();

    int ConstExp();

};


#endif //SYSY_COMPILER_PARSER_H
