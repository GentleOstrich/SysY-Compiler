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

    void handleCompUnit(Node *compUnit);

    void handleVarDef(Node *varDef, bool isGlobal);

    void handleConstDef(Node *constDef, bool isGlobal);

    void handleFuncDef(Node *funcDef);

    void handleFuncFParam(Node *funcFParam, Value **param);

    void handleDecl(Node *funcFParam, bool isGlobal);

    void handleMainFuncDef(Node *mainFuncFParam);

    void handleConstDecl(Node *constDecl, bool isGlobal);

    void handleVarDecl(Node *varDecl, bool isGlobal);

    void handleBType(Node *BType);

    int handleConstInitVal(Node *constInitVal, std::vector<Value *> *constInitVals, bool isGlobal);

    int handleInitVal(Node *initVal, std::vector<Value *> *initVals, bool isGlobal);

    int handleFuncFParams(Node *funcFParams);

    int handleFuncType(Node *funcType);

    void handleBlock(Node *block);

    void handleBlockItem(Node *blockItem);

    void handleStmt(Node *stmt);

    void handleForStmt(Node *forStmt);

    int handleExp(Node *exp, Value **expInstruction, bool isGlobal);

    Instruction *handleCond(Node *cond, Value **c);

    int handleLVal(Node *lVal, Value **lValInstruction);

    int handlePrimaryExp(Node *primaryExp, Value **primaryInstruction, bool isGlobal);

    void handleNumber(Node *number);

    int handleUnaryExp(Node *unaryExp, Value **unaryInstruction, bool isGlobal);

    int handleUnaryOp(Node *unaryOp);

    void handleFuncRParams(Node *funcRParams, Value **callInstruction);

    int handleMulExp(Node *mulExp, Value **mulInstruction, bool isGlobal);

    int handleAddExp(Node *addExp, Value **addInstruction, bool isGlobal);

    void handleRelExp(Node *relExp, Value **rel);

    Instruction *handleEqExp(Node *eqExp, Value **eq, bool isBr); // 返回生成的br指令

    Instruction *handleLAndExp(Node *lAndExp);

    Instruction *handleLOrExp(Node *lOrExp);

    int handleConstExp(Node *constExp, Value **constExpInstruction, bool isGlobal);
};

#endif // SYSY_COMPILER_VISITOR_H
