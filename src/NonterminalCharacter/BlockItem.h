//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_BLOCKITEM_H
#define SYSY_COMPILER_BLOCKITEM_H
#include "Nonterminal.h"

class BlockItem {
public:
    Nonterminal *Decl;
    Nonterminal *Stmt;
    BlockItem();
    int setDecl(Nonterminal *Decl);
    int setStmt(Nonterminal *Stmt);
};


#endif //SYSY_COMPILER_BLOCKITEM_H
