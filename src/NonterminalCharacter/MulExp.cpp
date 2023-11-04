//
// Created by lyh on 11/3/2023.
//

#include "MulExp.h"

void MulExp::setUnaryExp(UnaryExp *unaryExp) {
    this->unaryExp = unaryExp;
}

void MulExp::setMulExp1(MulExp *mulExp1) {
    this->mulExp1 = mulExp1;
}

void MulExp::setUnaryExp1(UnaryExp *unaryExp1) {
    this->unaryExp1 = unaryExp1;
}

MulExp::MulExp() {
    this->mulExp1 = nullptr;
    this->unaryExp1 = nullptr;
    this->unaryExp = nullptr;
}
