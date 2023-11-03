//
// Created by lyh on 11/3/2023.
//

#include "LAndExp.h"

void LAndExp::setEqExp(Nonterminal *eqExp) {
    EqExp = eqExp;
}

void LAndExp::setLAndExp1(Nonterminal *lAndExp1) {
    LAndExp1 = lAndExp1;
}

void LAndExp::setEqExp1(Nonterminal *eqExp1) {
    EqExp1 = eqExp1;
}

LAndExp::LAndExp() {
    this->EqExp1 = nullptr;
    this->EqExp = nullptr;
    this->LAndExp1 = nullptr;
}
