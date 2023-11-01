//
// Created by lyh on 2023/11/1.
//

#include "VarDef.h"

VarDef::VarDef() {
    this->Ident = nullptr;
}

int VarDef::setIdent(Nonterminal *Ident) {
    this->Ident = Ident;
    return 0;
}

int VarDef::addConstExp(Nonterminal *ConstExp) {
    this->ConstExps.push_back(ConstExp);
    return 0;
}
