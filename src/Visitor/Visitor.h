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
    void handleConstExp(Node* constExp);
    void handleInitVal(Node* initVal);
    void handleExp(Node* exp);
    int handleFuncFParams(Node* funcFParams, vector<int> paramTypeList); // 返回参数个数
    void handleFuncType(Node* funcType);
    void handleBlock(Node* block);
    void handleBlockItem(Node* blockItem);
    void handleStmt(Node* stmt);
};


#endif //SYSY_COMPILER_VISITOR_H
