//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_VISITOR_H
#define SYSY_COMPILER_VISITOR_H

#include "iostream"
#include "../NonterminalCharacter/Nonterminals.h"
#include "../SymbolManager/SymbolTable.h"
extern CompUnit* compUnit;
class Visitor {
public:
    void handleCompUnit(Node* compUnit);  
    void handleVarDef(Node* varDef);
    void handleConstDef(Node* constDef);
    void handleFuncDef(Node* funcDef);
    int handleFuncFParam(Node* funcFParam); // 返回参数类型
    void handleDecl(Node* funcFParam);
    void handleMainFuncDef(Node* mainFuncFParam);
    void handleConstDecl(Node* constDecl);
    void handleVarDecl(Node* varDecl);
    void handleBType(Node* BType);
    void handleConstInitVal(Node* constInitVal);
    
    void handleInitVal(Node* initVal);
    
    int handleFuncFParams(Node* funcFParams, vector<int>* paramTypeList); // 返回参数个数
    int handleFuncType(Node* funcType);
    void handleBlock(Node* block, int isNoRet, bool isLoop);
    void handleBlockItem(Node* blockItem, int isNoRet, bool isLoop);
    void handleStmt(Node* stmt, int isNoRet, bool isLoop);
    
    void handleForStmt(Node* forStmt);
    int handleExp(Node* exp);
    void handleCond(Node* cond);
    int handleLVal(Node* lVal);
    int handlePrimaryExp(Node* primaryExp);
    int handleNumber(Node* number);
    int handleUnaryExp(Node* unaryExp);
    void handleUnaryOp(Node* unaryOp);
    void handleFuncRParams(Node* funcRParams, Symbol* funcSymbole);
    int handleMulExp(Node* mulExp);
    int handleAddExp(Node* addExp);
    void handleRelExp(Node* relExp);
    void handleEqExp(Node* eqExp);
    void handleLAndExp(Node* lAndExp);
    void handleLOrExp(Node* lOrExp);
    void handleConstExp(Node* constExp);
};


#endif //SYSY_COMPILER_VISITOR_H
