//
// Created by lyh on 2023/11/2.
//

#include "ForStmt.h"

void ForStmt::setLVal(Nonterminal *lVal) {
    LVal = lVal;
}

void ForStmt::setExp(Nonterminal *exp) {
    Exp = exp;
}
