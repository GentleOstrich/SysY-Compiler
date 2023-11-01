//
// Created by lyh on 2023/11/1.
//

#include "ConstDecl.h"

ConstDecl::ConstDecl() {
    this->Btype = nullptr;
}

int ConstDecl::setBtype(Nonterminal *Btype) {
    this->Btype = Btype;
    return 0;
}

int ConstDecl::addConstDef(Nonterminal *ConstDef) {
    this->ConstDefs.push_back(ConstDef);
    return 0;
}
