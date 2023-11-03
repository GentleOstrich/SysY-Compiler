//
// Created by lyh on 11/3/2023.
//

#include "CompUnit.h"

void CompUnit::addDecl(Decl *decl) {
    this->decls.push_back(decl);
}

void CompUnit::addFuncDef(FuncDef *funcDef) {
    this->funcDefs.push_back(funcDef);
}

void CompUnit::setMainFuncDef(MainFuncDef *mainFuncDef) {
    this->mainFuncDef = mainFuncDef;
}

CompUnit::CompUnit() {
    this->mainFuncDef = nullptr;
}
