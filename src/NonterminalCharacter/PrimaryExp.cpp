//
// Created by lyh on 2023/11/2.
//

#include "PrimaryExp.h"

PrimaryExp::PrimaryExp() {
    Exp = nullptr;
    LVal = nullptr;
    Number = nullptr;
}

void PrimaryExp::setExp(Nonterminal *exp) {
    Exp = exp;
}

void PrimaryExp::setLVal(Nonterminal *lVal) {
    LVal = lVal;
}

void PrimaryExp::setNumber(Nonterminal *number) {
    Number = number;
}
