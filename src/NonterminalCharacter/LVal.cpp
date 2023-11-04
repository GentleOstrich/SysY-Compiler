//
// Created by lyh on 2023/11/2.
//

#include "LVal.h"

LVal::LVal() {
    this->ident = nullptr;
}

void LVal::setIdent(Ident *ident) {
    this->ident = ident;
}

void LVal::addExp(Exp *exp) {
    this->exps.push_back(exp);
}
