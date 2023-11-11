//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_VISITOR_H
#define SYSY_COMPILER_VISITOR_H

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
    void handleMainFuncDef(Node* funcFParam);
    void handleConstDecl(Node* constDecl);
    void handleVarDecl(Node* varDecl);
    void handleBType(Node* BType);
    void handleConstInitVal(Node* constInitVal);
    
    void handleInitVal(Node* initVal);
    
    int handleFuncFParams(Node* funcFParams, vector<int> paramTypeList); // 返回参数个数
    void handleFuncType(Node* funcType);
    void handleBlock(Node* block);
    void handleBlockItem(Node* blockItem);
    void handleStmt(Node* stmt);
    
    void handleForStmt(Node* forStmt);
    void handleExp(Node* exp);
    void handleCond(Node* cond);
    void handleLVal(Node* lVal);
    void handlePrimaryExp(Node* primaryExp);
    void handleNumber(Node* number);
    void handleUnaryExp(Node* unaryExp);
    void handleUnaryOp(Node* unaryOp);
    void handleFuncRParams(Node* funcRParams);
    void handleMulExp(Node* mulExp);
    void handleAddExp(Node* addExp);
    void handleRelExp(Node* relExp);
    void handleEqExp(Node* eqExp);
    void handleLAndExp(Node* lAndExp);
    void handleLOrExp(Node* lOrExp);
    void handleConstExp(Node* constExp);
};


#endif //SYSY_COMPILER_VISITOR_H
