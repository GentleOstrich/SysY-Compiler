//
// Created by lyh on 2023/11/2.
//

#include "PrimaryExp.h"

PrimaryExp::PrimaryExp() {
    this->exp = nullptr;
    this->lVal = nullptr;
    this->number = nullptr;
}

void PrimaryExp::setExp(Exp *exp) {
    this->exp = exp;
}

void PrimaryExp::setLVal(LVal *lVal) {
    this->lVal = lVal;
}

void PrimaryExp::setNumber(Number *number) {
    this->number = number;
}
