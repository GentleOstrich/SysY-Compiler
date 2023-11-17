////
//// Created by lyh on 11/9/2023.
////
//
//#ifndef SYSY_COMPILER_VISITOR_H
//#define SYSY_COMPILER_VISITOR_H
//
//#include <iostream>
//#include <fstream>
//#include "../Frontend/NonterminalCharacter/Nonterminals.h"
//#include "SymbolManager/SymbolTable.h"
//using namespace std;
//extern std::unique_ptr<CompUnit> compUnit;
//class Visitor
//{
//public:
//    void handleCompUnit(std::unique_ptr<Node> compUnit);
//    void handleVarDef(std::unique_ptr<Node> varDef, bool isGlobal);
//    void handleConstDef(std::unique_ptr<Node> constDef, bool isGlobal);
//    void handleFuncDef(std::unique_ptr<Node> funcDef);
//    int handleFuncFParam(std::unique_ptr<Node> funcFParam, string *code); // 返回参数类型
//    void handleDecl(std::unique_ptr<Node> funcFParam, bool isGlobal);
//    void handleMainFuncDef(std::unique_ptr<Node> mainFuncFParam);
//    void handleConstDecl(std::unique_ptr<Node> constDecl, bool isGlobal);
//    void handleVarDecl(std::unique_ptr<Node> varDecl, bool isGlobal);
//    void handleBType(std::unique_ptr<Node> BType);
//    int handleConstInitVal(std::unique_ptr<Node> constInitVal, bool isGlobal);
//    int handleInitVal(std::unique_ptr<Node> initVal, bool isGlobal, int *c);
//    int handleFuncFParams(std::unique_ptr<Node> funcFParams, vector<int> *paramTypeList); // 返回参数个数
//    int handleFuncType(std::unique_ptr<Node> funcType);
//    void handleBlock(std::unique_ptr<Node> block, int isNoRet, bool isLoop);
//    void handleBlockItem(std::unique_ptr<Node> blockItem, int isNoRet, bool isLoop);
//    void handleStmt(std::unique_ptr<Node> stmt, int isNoRet, bool isLoop);
//    void handleForStmt(std::unique_ptr<Node> forStmt);
//    int handleExp(std::unique_ptr<Node> exp, int *c, int *val, bool isGlobal);
//    void handleCond(std::unique_ptr<Node> cond);
//    int handleLVal(std::unique_ptr<Node> lVal, int *initVal, int *c, bool isGlobal);
//    int handlePrimaryExp(std::unique_ptr<Node> primaryExp, int *c, int pos, int *initVal, bool isGlobal);
//    int handleNumber(std::unique_ptr<Node> number, int *c, int pos, int *initVal, bool isGlobal);
//    int handleUnaryExp(std::unique_ptr<Node> unaryExp, int *c, int pos, int *initVal, bool isGlobal);
//    int handleUnaryOp(std::unique_ptr<Node> unaryOp);
//    void handleFuncRParams(std::unique_ptr<Node> funcRParams, Symbol *funcSymbole, string *code);
//    int handleMulExp(std::unique_ptr<Node> mulExp, int *c, int *initVal, bool isGlobal);
//    int handleAddExp(std::unique_ptr<Node> addExp, int *c, int *initVal, bool isGlobal);
//    void handleRelExp(std::unique_ptr<Node> relExp);
//    void handleEqExp(std::unique_ptr<Node> eqExp);
//    void handleLAndExp(std::unique_ptr<Node> lAndExp);
//    void handleLOrExp(std::unique_ptr<Node> lOrExp);
//    int handleConstExp(std::unique_ptr<Node> constExp, bool isGlobal, int *c);
//};
//
//#endif // SYSY_COMPILER_VISITOR_H
