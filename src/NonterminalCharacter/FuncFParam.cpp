//
// Created by lyh on 2023/11/2.
//

#include "FuncFParam.h"

FuncFParam::FuncFParam() {
    this->Btype = nullptr;
    this->Ident = nullptr;
}

int FuncFParam::setBtype(Nonterminal *Btype) {
    this->Btype = Btype;
    return 0;
}

int FuncFParam::setIdent(Nonterminal *Ident) {
    this->Ident = Ident;
    return 0;
}

int FuncFParam::addConstExp(Nonterminal *ConstExp) {
    this->ConstExps.push_back(ConstExp);
    return 0;
}
