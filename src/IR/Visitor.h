//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_VISITOR_H
#define SYSY_COMPILER_VISITOR_H

#include <iostream>
#include <fstream>
#include "../Frontend/NonterminalCharacter/Nonterminals.h"
#include "SymbolManager/SymbolTable.h"
#include "BuildFactory.h"

using namespace std;
extern CompUnit *compUnit;

class Visitor {
public:
    SymbolTable *symbolTable;

    BuildFactory *buildFactory;

    Visitor();

    void visitCompUnit(Node *compUnit);

    void visitVarDef(Node *varDef, bool isGlobal);

    void visitConstDef(Node *constDef, bool isGlobal);

    void visitFuncDef(Node *funcDef);

    void visitFuncFParam(Node *funcFParam, Value **param);

    void visitDecl(Node *funcFParam, bool isGlobal);

    void visitMainFuncDef(Node *mainFuncFParam);

    void visitConstDecl(Node *constDecl, bool isGlobal);

    void visitVarDecl(Node *varDecl, bool isGlobal);

    void visitBType(Node *BType);

    int visitConstInitVal(Node *constInitVal, std::vector<Value *> *constInitVals, bool needNum);

    int visitInitVal(Node *initVal, std::vector<Value *> *initVals, bool needNum);

    int visitFuncFParams(Node *funcFParams);

    int visitFuncType(Node *funcType);

    void visitBlock(Node *block);

    int visitBlockItem(Node *blockItem);

    void visitStmt(Node *stmt);

    void visitForStmt(Node *forStmt);

    int visitExp(Node *exp, Value **expInstruction, bool needNum);

    Instruction *visitCond(Node *cond, Value **c);

    int visitLVal(Node *lVal, Value **lValInstruction);

    int visitPrimaryExp(Node *primaryExp, Value **primaryInstruction, bool needNum);

    void handleNumber(Node *number);

    int visitUnaryExp(Node *unaryExp, Value **unaryInstruction, bool needNum);

    int visitUnaryOp(Node *unaryOp);

    void handleFuncRParams(Node *funcRParams, Value **callInstruction);

    int visitMulExp(Node *mulExp, Value **mulInstruction, bool needNum);

    int visitAddExp(Node *addExp, Value **addInstruction, bool isGlobal);

    void visitRelExp(Node *relExp, Value **rel);

    Instruction *visitEqExp(Node *eqExp, Value **eq, bool isBr); // 返回生成的br指令

    Instruction *visitLAndExp(Node *lAndExp);

    Instruction *visitLOrExp(Node *lOrExp);

    int visitConstExp(Node *constExp, Value **constExpInstruction, bool needNum);

    Module *getModule();
};

#endif // SYSY_COMPILER_VISITOR_H
