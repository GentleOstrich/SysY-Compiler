//
// Created by lyh on 2023/11/2.
//

#include "BlockItem.h"

BlockItem::BlockItem() {
    this->stmt = nullptr;
    this->decl = nullptr;
}

void BlockItem::setDecl(Decl *decl) {
    this->decl = decl;
}

void BlockItem::setStmt(Stmt *stmt) {
    this->stmt = stmt;
}
