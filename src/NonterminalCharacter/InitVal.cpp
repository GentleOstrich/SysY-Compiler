//
// Created by lyh on 2023/11/1.
//

#include "InitVal.h"

InitVal::InitVal() {
    this->exp = nullptr;
}

void InitVal::setExp(Exp *exp) {
    this->exp = exp;
}

void InitVal::addInitVal(InitVal *initVal) {
    this->initVals.push_back(initVal);
}
