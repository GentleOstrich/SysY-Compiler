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
    std::vector<Value*> values;
    int symbolId;
    SymbolTable();

    void createSymbolTable();

    void addSymbol(Value* symbol, int lineNum);

    bool findSymbol(const std::string& word, bool isFunc, bool all);

    void deleteSymbolTable();

    Value* getSymbol(const std::string& word, bool isFunc, bool all);

};


#endif //SYSY_COMPILER_SYMBOLTABLE_H
