//
// Created by lyh on 2023/11/1.
//

#include "ConstDecl.h"

ConstDecl::ConstDecl() {
    this->btype = nullptr;
}

void ConstDecl::setBtype(Btype *btype) {
    this->btype = btype;
}

void ConstDecl::addConstDef(ConstDef *constDef) {
    this->constDefs.push_back(constDef);
}
