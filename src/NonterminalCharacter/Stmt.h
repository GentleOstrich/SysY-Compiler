//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_STMT_H
#define SYSY_COMPILER_STMT_H

#include "LVal.h"
#include "EqExp.h"
#include "Exp.h"
#include "Block.h"
#include "Cond.h"


#include <vector>
#include <string>
class Block;
class Stmt  {
public:
    LVal *lVal1;
    EqExp *eqExp;
    Exp *exp;
    Block *block;
    Cond *ifCond;
    Stmt *ifStmt;
    Stmt *elseStmt;
    Stmt *ForStmt1;
    Cond *forCond;
    Stmt *ForStmt2;
    bool isBreak;
    bool isContinue;
    Exp *returnExp;
    bool isReturn;
    LVal *lVal2;
    bool isGetint;
    std::string formatString;
    std::vector<Exp *> exps;
    bool isPrintf;

    void setLVal1(LVal *lVal1);

    void setEquExp(EqExp *eqExp);

    void setExp(Exp *exp);

    void setBlock(Block *block);

    void setIfCond(Cond *ifCond);

    void setIfStmt(Stmt *ifStmt);

    void setElseStmt(Stmt *elseStmt);

    void setForStmt1(Stmt *forStmt1);

    void setForCond(Cond *forCond);

    void setForStmt2(Stmt *forStmt2);

    void setIsBreak(bool isBreak);

    void setIsContinue(bool isContinue);

    void setReturnExp(Exp *returnExp);

    void setIsReturn(bool isReturn);

    void setLVal2(LVal *lVal2);

    void setIsGetint(bool isGetint);

    void setFormatString(const std::string &formatString);

    void addExps(Exp *exp);

    void setIsPrintf(bool isPrintf);

};


#endif //SYSY_COMPILER_STMT_H
