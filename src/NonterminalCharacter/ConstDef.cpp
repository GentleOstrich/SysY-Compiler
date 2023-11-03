//
// Created by lyh on 2023/11/1.
//

#include "ConstDef.h"

ConstDef::ConstDef() {
    this->ident = nullptr;
    this->constInitVal = nullptr;
}

void ConstDef::setIdent(Ident *ident) {
    this->ident = ident;
}

void ConstDef::addConstExps(ConstExp *constExp) {
    this->constExps.push_back(constExp);
}

void ConstDef::setConstInitVal(ConstInitVal *constInitVal) {
    this->constInitVal = constInitVal;
}
