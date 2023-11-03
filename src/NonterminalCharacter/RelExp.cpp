//
// Created by lyh on 11/3/2023.
//

#include "RelExp.h"

void RelExp::setAddExp(Nonterminal *addExp) {
    AddExp = addExp;
}

void RelExp::setRelExp1(Nonterminal *relExp1) {
    RelExp1 = relExp1;
}

void RelExp::setAddExp1(Nonterminal *addExp1) {
    AddExp1 = addExp1;
}

RelExp::RelExp() {
    this->AddExp1 = nullptr;
    this->AddExp = nullptr;
    this->RelExp1 = nullptr;
}
