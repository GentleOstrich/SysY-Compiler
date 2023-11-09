//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_VISITOR_H
#define SYSY_COMPILER_VISITOR_H

#include "../NonterminalCharacter/Nonterminals.h"
#include "../SymbolManager/SymbolTable.h"
extern CompUnit* compUnit;
class Visitor {
public:
    void visit(Node* node);
};


#endif //SYSY_COMPILER_VISITOR_H
