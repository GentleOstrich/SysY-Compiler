//
// Created by lyh on 11/3/2023.
//

#include "MulExp.h"

void MulExp::setUnaryExp(Nonterminal *unaryExp) {
    UnaryExp = unaryExp;
}

void MulExp::setMulExp1(Nonterminal *mulExp1) {
    MulExp1 = mulExp1;
}

void MulExp::setUnaryExp1(Nonterminal *unaryExp1) {
    UnaryExp1 = unaryExp1;
}

MulExp::MulExp() {

}
