//
// Created by lyh on 11/3/2023.
//

#include "LOrExp.h"

void LOrExp::setLAndExp(LAndExp *lAndExp) {
    this->lAndExp = lAndExp;
}

void LOrExp::setLOrExp1(LOrExp *lOrExp1) {
    this->lOrExp1 = lOrExp1;
}

void LOrExp::setLAndExp1(LAndExp *lAndExp1) {
    this->lAndExp1 = lAndExp1;
}

LOrExp::LOrExp() {
    this->lAndExp1 = nullptr;
    this->lAndExp = nullptr;
    this->lOrExp1 = nullptr;

}
