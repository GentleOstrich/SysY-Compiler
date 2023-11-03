//
// Created by lyh on 2023/11/2.
//

#include "FuncFParam.h"

FuncFParam::FuncFParam() {
    this->btype = nullptr;
    this->ident = nullptr;
}

void FuncFParam::setBtype(Btype *btype) {
    this->btype = btype;
}

void FuncFParam::setIdent(Ident *ident) {
    this->ident = ident;
}

void FuncFParam::addConstExp(ConstExp *constExp) {
    this->constExps.push_back(constExp);
}
