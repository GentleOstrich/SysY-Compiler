//
// Created by lyh on 2023/11/1.
//

#include "InitVal.h"

InitVal::InitVal() {
    this->Exp = nullptr;
}

int InitVal::setExp(Nonterminal *Exp) {
    this->Exp = Exp;
    return 0;
}

int InitVal::addInitVal(Nonterminal *InitVal) {
    this->InitVals.push_back(InitVal);
    return 0;
}
