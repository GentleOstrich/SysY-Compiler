//
// Created by lyh on 2023/11/1.
//

#include "Decl.h"

Decl::Decl() {
    this->ConstDecl = nullptr;
    this->VarDecl = nullptr;

}

int Decl::setConstDecl(Nonterminal *ConstDecl) {
    this->ConstDecl = ConstDecl;
    return 0;
}

int Decl::setVarDecl(Nonterminal *VarDecl) {
    this->VarDecl = VarDecl;
    return 0;
}
