//
// Created by lyh on 2023/11/1.
//

#include "FunDef.h"

FunDef::FunDef() {
    this->Ident = nullptr;
    this->Block = nullptr;
    this->FuncType = nullptr;
}

int FunDef::setFuncType(Nonterminal *FuncType) {
    this->FuncType = FuncType;
    return 0;
}

int FunDef::setIdent(Nonterminal *Ident) {
    this->Ident = Ident;
    return 0;
}

int FunDef::addFuncFParam(Nonterminal *FuncFParam) {
    this->addFuncFParam(FuncFParam);
    return 0;
}

int FunDef::setBlock(Nonterminal *Block) {
    this->Block = Block;
    return 0;
}
