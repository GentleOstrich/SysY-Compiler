//
// Created by lyh on 2023/11/1.
//

#include "VarDef.h"

VarDef::VarDef() {
    this->ident = nullptr;
}

void VarDef::setIdent(Ident *ident) {
    this->ident = ident;
}

void VarDef::addConstExp(ConstExp *constExp) {
    this->constExps.push_back(constExp);
}

void VarDef::setInitVal(InitVal *initVal) {
    this->initVal = initVal;
}