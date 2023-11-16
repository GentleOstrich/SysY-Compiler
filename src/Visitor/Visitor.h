//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_VISITOR_H
#define SYSY_COMPILER_VISITOR_H

#include <iostream>
#include <fstream>
#include "../NonterminalCharacter/Nonterminals.h"
#include "../SymbolManager/SymbolTable.h"
extern CompUnit* compUnit;
class Visitor {
public:
    void handleCompUnit(Node* compUnit);  
    void handleVarDef(Node* varDef, bool isGlobal);
    void handleConstDef(Node* constDef, bool isGlobal);
    void handleFuncDef(Node* funcDef);
    int handleFuncFParam(Node* funcFParam, string* code); // 返回参数类型
    void handleDecl(Node* funcFParam, bool isGlobal);
    void handleMainFuncDef(Node* mainFuncFParam);
    void handleConstDecl(Node* constDecl, bool isGlobal);
    void handleVarDecl(Node* varDecl, bool isGlobal);
    void handleBType(Node* BType);
    int handleConstInitVal(Node* constInitVal, bool isGlobal);
    
    int handleInitVal(Node *initVal, bool isGlobal, int* c);
    
    int handleFuncFParams(Node* funcFParams, vector<int>* paramTypeList); // 返回参数个数
    int handleFuncType(Node* funcType);
    void handleBlock(Node* block, int isNoRet, bool isLoop);
    void handleBlockItem(Node* blockItem, int isNoRet, bool isLoop);
    void handleStmt(Node* stmt, int isNoRet, bool isLoop);
    
    void handleForStmt(Node* forStmt);
    int handleExp(Node *exp, int *c, int* val, bool isGlobal);
    void handleCond(Node* cond);
    int handleLVal(Node* lVal, int* initVal, int *c, bool isGlobal);
    int handlePrimaryExp(Node* primaryExp, int* c, int pos, int* initVal, bool isGlobal);
    int handleNumber(Node* number, int* c, int pos, int* initVal, bool isGlobal);
    int handleUnaryExp(Node* unaryExp, int* c, int pos, int* initVal, bool isGlobal);
    int handleUnaryOp(Node* unaryOp);
    void handleFuncRParams(Node* funcRParams, Symbol* funcSymbole, string* code);
    int handleMulExp(Node* mulExp, int* c, int* initVal, bool isGlobal);
    int handleAddExp(Node* addExp, int* c, int* initVal, bool isGlobal);
    void handleRelExp(Node* relExp);
    void handleEqExp(Node* eqExp);
    void handleLAndExp(Node* lAndExp);
    void handleLOrExp(Node* lOrExp);
    int handleConstExp(Node* constExp, bool isGlobal, int *c);
};


#endif //SYSY_COMPILER_VISITOR_H
