//
// Created by lyh on 2023/11/1.
//

#include "ConstInitVal.h"

ConstInitVal::ConstInitVal() {
    this->constExp = nullptr;
}

void ConstInitVal::setConstExp(ConstExp *constExp) {
    this->constExp = constExp;
}

void ConstInitVal::addConstInitVal(ConstInitVal *ConstInitVal) {
    this->constInitVals.push_back(ConstInitVal);
}
