//
// Created by lyh on 2023/11/2.
//

#include "Stmt.h"

void Stmt::setLVal1(Nonterminal *lVal1) {
    LVal1 = lVal1;
}

void Stmt::setEquExp(Nonterminal *equExp) {
    Stmt::equExp = equExp;
}

void Stmt::setExp(Nonterminal *exp) {
    Exp = exp;
}

void Stmt::setBlock(Nonterminal *block) {
    Block = block;
}

void Stmt::setIfCond(Nonterminal *ifCond) {
    Stmt::ifCond = ifCond;
}

void Stmt::setIfStmt(Nonterminal *ifStmt) {
    Stmt::ifStmt = ifStmt;
}

void Stmt::setElseStmt(Nonterminal *elseStmt) {
    Stmt::elseStmt = elseStmt;
}

void Stmt::setForStmt1(Nonterminal *forStmt1) {
    ForStmt1 = forStmt1;
}

void Stmt::setForCond(Nonterminal *forCond) {
    Stmt::forCond = forCond;
}

void Stmt::setForStmt2(Nonterminal *forStmt2) {
    ForStmt2 = forStmt2;
}

void Stmt::setIsBreak(bool isBreak) {
    Stmt::isBreak = isBreak;
}

void Stmt::setIsContinue(bool isContinue) {
    Stmt::isContinue = isContinue;
}

void Stmt::setReturnExp(Nonterminal *returnExp) {
    Stmt::returnExp = returnExp;
}

void Stmt::setIsReturn(bool isReturn) {
    Stmt::isReturn = isReturn;
}

void Stmt::setLVal2(Nonterminal *lVal2) {
    LVal2 = lVal2;
}

void Stmt::setIsGetint(bool isGetint) {
    Stmt::isGetint = isGetint;
}

void Stmt::setFormatString(const std::string &formatString) {
    FormatString = formatString;
}

void Stmt::addExps(Nonterminal *exp) {
    this->Exps.push_back(exp);
}

void Stmt::setIsPrintf(bool isPrintf) {
    Stmt::isPrintf = isPrintf;
}
