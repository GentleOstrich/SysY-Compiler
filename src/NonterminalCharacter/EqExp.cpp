//
// Created by lyh on 11/3/2023.
//

#include "EqExp.h"

void EqExp::setRelExp(RelExp *relExp) {
    this->relExp = relExp;
}

void EqExp::setEqExp1(EqExp *eqExp1) {
    this->eqExp1 = eqExp1;
}

void EqExp::setRelExp1(RelExp *relExp1) {
    this->relExp1 = relExp1;
}

EqExp::EqExp() {
    this->relExp1 = nullptr;
    this->relExp = nullptr;
    this->eqExp1 = nullptr;
}
