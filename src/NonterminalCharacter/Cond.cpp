//
// Created by lyh on 2023/11/2.
//

#include "Cond.h"

void Cond::setLOrExp(Nonterminal *lOrExp) {
    LOrExp = lOrExp;
}

Cond::Cond() {
    this->LOrExp = nullptr;
}
