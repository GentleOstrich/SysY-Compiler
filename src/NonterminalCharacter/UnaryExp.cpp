//
// Created by lyh on 11/3/2023.
//

#include "UnaryExp.h"

UnaryExp::UnaryExp() {
    this->ident = nullptr;
    this->primaryExp = nullptr;

}

void UnaryExp::setPrimaryExp(PrimaryExp *primaryExp) {
    this->primaryExp = primaryExp;
}

void UnaryExp::setIdent(Ident *ident) {
    this->ident = ident;
}

void UnaryExp::addFuncRParams(FuncRParams *funcRParams) {
    this->funcRParamss.push_back(funcRParams);
}

void UnaryExp::setUnaryOp(UnaryOp *unaryOp) {
    this->unaryOp = unaryOp;
}

void UnaryExp::setUnaryExp1(UnaryExp *unaryExp1) {
    this->unaryExp1 = unaryExp1;
}
