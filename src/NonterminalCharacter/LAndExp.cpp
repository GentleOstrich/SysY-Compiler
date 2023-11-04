//
// Created by lyh on 11/3/2023.
//

#include "LAndExp.h"

void LAndExp::setEqExp(EqExp *eqExp) {
    this->eqExp = eqExp;
}

void LAndExp::setLAndExp1(LAndExp *lAndExp1) {
    this->lAndExp1 = lAndExp1;
}

void LAndExp::setEqExp1(EqExp *eqExp1) {
    this->eqExp1 = eqExp1;
}

LAndExp::LAndExp() {
    this->eqExp1 = nullptr;
    this->eqExp = nullptr;
    this->lAndExp1 = nullptr;
}
