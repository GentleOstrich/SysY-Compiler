//
// Created by yh on 2023/9/25.
//

#ifndef SYSY_COMPILER_PARSER_H
#define SYSY_COMPILER_PARSER_H

#include <iostream>
#include <fstream>
#include <memory>
#include "../NonterminalCharacter/Nonterminals.h"
#include "../Lexer/Lexer.h"

class Parser
{
public:
    std::unique_ptr<CompUnit> parseCompUnit();

    std::unique_ptr<Decl> parseDecl();

    std::unique_ptr<ConstDecl> parseConstDecl();

    std::unique_ptr<BType> parseBType();

    std::unique_ptr<ConstDef> parseConstDef();

    std::unique_ptr<ConstInitVal> parseConstInitVal();

    std::unique_ptr<VarDecl> parseVarDecl();

    std::unique_ptr<VarDef> parseVarDef();

    std::unique_ptr<InitVal> parseInitVal();

    std::unique_ptr<FuncDef> parseFuncDef();

    std::unique_ptr<MainFuncDef> parseMainFuncDef();

    std::unique_ptr<FuncType> parseFuncType();

    std::unique_ptr<FuncFParams> parseFuncFParams();

    std::unique_ptr<FuncFParam> parseFuncFParam();

    std::unique_ptr<Block> parseBlock();

    std::unique_ptr<BlockItem> parseBlockItem();

    std::unique_ptr<Stmt> parseStmt();

    std::unique_ptr<ForStmt> parseForStmt();

    std::unique_ptr<Exp> parseExp();

    std::unique_ptr<Cond> parseCond();

    std::unique_ptr<LVal> parseLVal();

    std::unique_ptr<PrimaryExp> parsePrimaryExp();

    std::unique_ptr<UnaryExp> parseUnaryExp();

    std::unique_ptr<UnaryOp> parseUnaryOp();

    std::unique_ptr<FuncRParams> parseFuncRParams();

    std::unique_ptr<MulExp> parseMulExp();

    std::unique_ptr<AddExp> parseAddExp();

    std::unique_ptr<RelExp> parseRelExp();

    std::unique_ptr<EqExp> parseEqExp();

    std::unique_ptr<LAndExp> parseLAndExp();

    std::unique_ptr<LOrExp> parseLOrExp();

    std::unique_ptr<ConstExp> parseConstExp();

    std::unique_ptr<Number> parseNumber();
};

#endif // SYSY_COMPILER_PARSER_H
