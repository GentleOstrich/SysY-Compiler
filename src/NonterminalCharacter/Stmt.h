//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_STMT_H
#define SYSY_COMPILER_STMT_H
#include "Nonterminal.h"
#include <vector>
#include <string>

class Stmt : Nonterminal {
public:
    Nonterminal *LVal1;
    Nonterminal *equExp;
    Nonterminal *Exp;
    Nonterminal *Block;
    Nonterminal *ifCond;
    Nonterminal *ifStmt;
    Nonterminal *elseStmt;
    Nonterminal *ForStmt1;
    Nonterminal *forCond;
    Nonterminal *ForStmt2;
    bool isBreak;
    bool isContinue;
    Nonterminal *returnExp;
    bool isReturn;
    Nonterminal *LVal2;
    bool isGetint;
    std::string FormatString;
    std::vector<Nonterminal *> Exps;
    bool isPrintf;

    void setLVal1(Nonterminal *lVal1);

    void setEquExp(Nonterminal *equExp);

    void setExp(Nonterminal *exp);

    void setBlock(Nonterminal *block);

    void setIfCond(Nonterminal *ifCond);

    void setIfStmt(Nonterminal *ifStmt);

    void setElseStmt(Nonterminal *elseStmt);

    void setForStmt1(Nonterminal *forStmt1);

    void setForCond(Nonterminal *forCond);

    void setForStmt2(Nonterminal *forStmt2);

    void setIsBreak(bool isBreak);

    void setIsContinue(bool isContinue);

    void setReturnExp(Nonterminal *returnExp);

    void setIsReturn(bool isReturn);

    void setLVal2(Nonterminal *lVal2);

    void setIsGetint(bool isGetint);

    void setFormatString(const std::string &formatString);

    void addExps(Nonterminal *exp);

    void setIsPrintf(bool isPrintf);

};


#endif //SYSY_COMPILER_STMT_H
