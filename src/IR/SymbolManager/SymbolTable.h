//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_SYMBOLTABLE_H
#define SYSY_COMPILER_SYMBOLTABLE_H

#include <stack>
#include <vector>
#include "Symbol.h"
#include "../../Frontend/NonterminalCharacter/Nonterminals.h"
#include "../Value.h"

class SymbolTable {
public:
    std::stack<int> table;
    std::vector<Symbol *> symbols;
    int symbolId;
    bool working;

    SymbolTable();

    void createSymbolTable();

    void addSymbol(Symbol *symbol, int lineNum);

    void deleteSymbolTable();

    Symbol *getSymbol(const std::string &word, bool isFunc, bool all);

};


#endif //SYSY_COMPILER_SYMBOLTABLE_H
