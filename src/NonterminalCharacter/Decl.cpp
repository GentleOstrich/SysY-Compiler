//
// Created by lyh on 2023/11/1.
//

#include "Decl.h"

Decl::Decl() {
    this->constDecl = nullptr;
    this->varDecl = nullptr;
}

void Decl::setConstDecl(ConstDecl *constDecl) {
    this->constDecl = constDecl;
}

void Decl::setVarDecl(VarDecl *varDecl) {
    this->varDecl = varDecl;
}
