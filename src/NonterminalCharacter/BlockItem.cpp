//
// Created by lyh on 2023/11/2.
//

#include "BlockItem.h"

BlockItem::BlockItem() {
    this->Stmt = nullptr;
    this->Decl = nullptr;
}

int BlockItem::setDecl(Nonterminal *Decl) {
    this->Decl = Decl;
    return 0;
}

int BlockItem::setStmt(Nonterminal *Stmt) {
    this->Stmt = Stmt;
    return 0;
}
