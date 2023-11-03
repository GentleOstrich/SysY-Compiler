//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_BLOCKITEM_H
#define SYSY_COMPILER_BLOCKITEM_H

#include "Decl.h"
#include "Stmt.h"

class BlockItem {
public:
    Decl *decl;
    Stmt *stmt;
    BlockItem();
    void setDecl(Decl *decl);
    void setStmt(Stmt *stmt);
};


#endif //SYSY_COMPILER_BLOCKITEM_H
