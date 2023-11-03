//
// Created by lyh on 11/3/2023.
//

#include "AddExp.h"

void AddExp::setMulExp(MulExp *mulExp) {
    mulExp = mulExp;
}

void AddExp::setAddExp1(AddExp *addExp1) {
    addExp1 = addExp1;
}

void AddExp::setMulExp1(MulExp *mulExp1) {
    mulExp1 = mulExp1;
}

AddExp::AddExp() {
    this->mulExp = nullptr;
    this->addExp1 = nullptr;
    this->mulExp1 = nullptr;
}
