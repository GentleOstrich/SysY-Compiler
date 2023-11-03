//
// Created by lyh on 11/3/2023.
//

#include "LOrExp.h"

void LOrExp::setLAndExp(Nonterminal *lAndExp) {
    LAndExp = lAndExp;
}

void LOrExp::setLOrExp1(Nonterminal *lOrExp1) {
    LOrExp1 = lOrExp1;
}

void LOrExp::setLAndExp1(Nonterminal *lAndExp1) {
    LAndExp1 = lAndExp1;
}

LOrExp::LOrExp() {
    this->LAndExp1 = nullptr;
    this->LAndExp = nullptr;
    this->LOrExp1 = nullptr;

}
