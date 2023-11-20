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

    void handleFuncFParam(Node *funcFParam);

    void handleDecl(Node *funcFParam, bool isConst);

    void handleMainFuncDef(Node *mainFuncFParam);

    void handleConstDecl(Node *constDecl, bool isGlobal);

    void handleVarDecl(Node *varDecl, bool isGlobal);

    void handleBType(Node *BType);

    int handleConstInitVal(Node *constInitVal, Value **constInitInstruction);

    int handleInitVal(Node *initVal, Value **initValInstruction);

    int handleFuncFParams(Node *funcFParams);

    void handleFuncType(Node *funcType);

    void handleBlock(Node *block);

    void handleBlockItem(Node *blockItem);

    void handleStmt(Node *stmt);

    void handleForStmt(Node *forStmt);

    int handleExp(Node *exp, Value **expInstruction);

    void handleCond(Node *cond);

    int handleLVal(Node *lVal, Value**LValInstucrion);

    int handlePrimaryExp(Node *primaryExp, Value **primaryInstruction);

    void handleNumber(Node *number);

    int handleUnaryExp(Node *unaryExp, Value **unaryInstruction);

    int handleUnaryOp(Node *unaryOp);

    void handleFuncRParams(Node *funcRParams);

    int handleMulExp(Node *mulExp, Value **mulInstruction);

    int handleAddExp(Node *addExp, Value **addInstruction);

    void handleRelExp(Node *relExp);

    void handleEqExp(Node *eqExp);

    void handleLAndExp(Node *lAndExp);

    void handleLOrExp(Node *lOrExp);

    int handleConstExp(Node *constExp, Value **constExpInstruction);
};

#endif // SYSY_COMPILER_VISITOR_H
