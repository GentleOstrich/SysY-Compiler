//
// Created by lyh on 2023/11/1.
//

#include "ConstInitVal.h"

ConstInitVal::ConstInitVal() {
    this->ConstExp = nullptr;
}

int ConstInitVal::setConstExp(Nonterminal *ConstExp) {
    this->ConstExp = ConstExp;
    return 0;
}

int ConstInitVal::addConstInitVal(Nonterminal *ConstInitVal) {
    this->ConstInitVals.push_back(ConstInitVal);
    return 0;
}
