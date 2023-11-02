//
// Created by lyh on 2023/11/2.
//

#include "Exp.h"

void Exp::setAddExp(Nonterminal *addExp) {
    AddExp = addExp;
}

Exp::Exp() {
    this->AddExp = nullptr;
}
