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

BuildFactory* buildFactory;

using namespace std;
extern CompUnit *compUnit;

class Visitor {
public:
    void handleCompUnit(Node *compUnit);

    void handleVarDef(Node *varDef);

    void handleConstDef(Node *constDef);

    void handleFuncDef(Node *funcDef);

    void handleFuncFParam(Node *funcFParam);

    void handleDecl(Node *funcFParam);

    void handleMainFuncDef(Node *mainFuncFParam);

    void handleConstDecl(Node *constDecl);

    void handleVarDecl(Node *varDecl);

    void handleBType(Node *BType);

    void handleConstInitVal(Node *constInitVal);

    void handleInitVal(Node *initVal);

    void handleFuncFParams(Node *funcFParams);

    void handleFuncType(Node *funcType);

    void handleBlock(Node *block);

    void handleBlockItem(Node *blockItem);

    void handleStmt(Node *stmt);

    void handleForStmt(Node *forStmt);

    void handleExp(Node *exp);

    void handleCond(Node *cond);

    void handleLVal(Node *lVal);

    void handlePrimaryExp(Node *primaryExp);

    void handleNumber(Node *number);

    void handleUnaryExp(Node *unaryExp);

    void handleUnaryOp(Node *unaryOp);

    void handleFuncRParams(Node *funcRParams);

    void handleMulExp(Node *mulExp);

    void handleAddExp(Node *addExp);

    void handleRelExp(Node *relExp);

    void handleEqExp(Node *eqExp);

    void handleLAndExp(Node *lAndExp);

    void handleLOrExp(Node *lOrExp);

    void handleConstExp(Node *constExp);
};

#endif // SYSY_COMPILER_VISITOR_H
