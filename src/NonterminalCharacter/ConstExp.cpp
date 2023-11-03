//
// Created by lyh on 11/3/2023.
//

#include "ConstExp.h"

void ConstExp::setAddExp(AddExp *addExp) {
    this->addExp = addExp;
}

ConstExp::ConstExp() {
    this->addExp = nullptr;
}
