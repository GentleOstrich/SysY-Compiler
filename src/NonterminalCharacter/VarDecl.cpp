//
// Created by lyh on 2023/11/1.
//

#include "VarDecl.h"

VarDecl::VarDecl() {
    this->BType = nullptr;
}

int VarDecl::setBType(Nonterminal *BType) {
    this->BType = BType;
    return 0;
}

int VarDecl::addVarDef(Nonterminal *VarDef) {
    this->VarDefs.push_back(VarDef);
    return 0;
}
