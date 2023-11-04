//
// Created by lyh on 2023/11/1.
//

#include "VarDecl.h"

VarDecl::VarDecl() {
    this->btype = nullptr;
}

void VarDecl::setBType(Btype *btype) {
    this->btype = btype;
}

void VarDecl::addVarDef(VarDef *varDef) {
    this->varDefs.push_back(varDef);
}
