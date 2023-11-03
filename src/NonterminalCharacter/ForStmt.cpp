//
// Created by lyh on 2023/11/2.
//

#include "ForStmt.h"

void ForStmt::setLVal(LVal *lVal) {
    this->lVal = lVal;
}

void ForStmt::setExp(Exp *exp) {
    this->exp = exp;
}
