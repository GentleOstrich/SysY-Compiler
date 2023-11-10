//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_SYMBOLTABLE_H
#define SYSY_COMPILER_SYMBOLTABLE_H

#include <stack>
#include <vector>
#include "Symbol.h"
#include "../NonterminalCharacter/Nonterminals.h"

class SymbolTable {
public:
    std::stack<int> table;
    std::vector<Symbol*> symbols;
    int symbolId;
    SymbolTable();

    void createSymbolTable();

    void addSymbol(Symbol* symbol);

    bool findSymbol(const string& word, bool isFunc, bool all);

    void deleteSymbolTable();

};


#endif //SYSY_COMPILER_SYMBOLTABLE_H
