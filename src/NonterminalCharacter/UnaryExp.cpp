//
// Created by lyh on 11/3/2023.
//

#include "UnaryExp.h"

UnaryExp::UnaryExp() {
    this->Ident = nullptr;
    this->PrimaryExp = nullptr;

}

void UnaryExp::setPrimaryExp(Nonterminal *primaryExp) {
    PrimaryExp = primaryExp;
}

void UnaryExp::setIdent(Nonterminal *ident) {
    Ident = ident;
}

void UnaryExp::addFuncRParams(Nonterminal *FuncRParams) {
    this->FuncRParamss.push_back(FuncRParams);
}

void UnaryExp::setUnaryOp(Nonterminal *unaryOp) {
    UnaryOp = unaryOp;
}

void UnaryExp::setUnaryExp1(Nonterminal *unaryExp1) {
    UnaryExp1 = unaryExp1;
}
