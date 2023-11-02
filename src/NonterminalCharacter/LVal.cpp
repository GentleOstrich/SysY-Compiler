//
// Created by lyh on 2023/11/2.
//

#include "LVal.h"

LVal::LVal() {
    this->Ident = nullptr;
}

int LVal::setIdent(Nonterminal *Ident) {
    this->Ident = Ident;
    return 0;
}

int LVal::addExp(Nonterminal *Exp) {
    this->Exps.push_back(Exp);
    return 0;
}
