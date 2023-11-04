//
// Created by lyh on 11/3/2023.
//

#include "RelExp.h"

void RelExp::setAddExp(AddExp *addExp) {
    this->addExp = addExp;
}

void RelExp::setRelExp1(RelExp *relExp1) {
    this->relExp1 = relExp1;
}

void RelExp::setAddExp1(AddExp *addExp1) {
    this->addExp1 = addExp1;
}

RelExp::RelExp() {
    this->addExp1 = nullptr;
    this->addExp = nullptr;
    this->relExp1 = nullptr;
}
