//
// Created by lyh on 2023/11/1.
//

#include "FuncDef.h"

FuncDef::FuncDef() {
    this->block = nullptr;
    this->ident = nullptr;
    this->funcType = nullptr;
}

void FuncDef::setFuncType(FuncType *funcType) {
    this->funcType = funcType;
}

void FuncDef::setIdent(Ident *ident) {
    this->ident = ident;
}

void FuncDef::addFuncFParam(FuncFParam *funcFParam) {
    this->funcFParams.push_back(funcFParam);
}

void FuncDef::setBlock(Block *block) {
    this->block = block;
}
