//
// Created by lyh on 2023/11/2.
//

#include "Exp.h"

void Exp::setAddExp(AddExp *addExp) {
    this->addExp = addExp;
}

Exp::Exp() {
    this->addExp = nullptr;
}
