//
// Created by lyh on 2023/11/2.
//

#include "Cond.h"

void Cond::setLOrExp(LOrExp *lOrExp) {
    this->lOrExp = lOrExp;
}

Cond::Cond() {
    this->lOrExp = nullptr;
}
