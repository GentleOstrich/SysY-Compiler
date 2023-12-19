//
// Created by lyh on 11/9/2023.
//

#include "SymbolTable.h"
#include "../Values/Instructions/Instruction.h"

#define ERROR_CHECK

#ifdef ERROR_CHECK

struct Error {
    int line;
    char c;
};
extern Error errors[1000];
extern int e;

#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}

#endif

void SymbolTable::createSymbolTable() {
    if (working) {
        table.push(this->symbolId);
    }
}

void SymbolTable::addSymbol(Symbol *symbol, int lineNum) {
    auto *sym = getSymbol(symbol->word, symbol->value->valueType == ValueType::Function, false);
    if (sym->word != "int") {
#ifdef ERROR_CHECK
        printError(lineNum, "b");
#endif
    } else {
        if (working) {
            symbols.insert(symbols.begin() + symbolId, symbol);
            symbolId++;
        }
    }
}


void SymbolTable::deleteSymbolTable() {
    symbolId = table.top();
    table.pop();
}

SymbolTable::SymbolTable() {
    symbolId = 0;
    working = true;
}

Symbol *SymbolTable::getSymbol(const std::string &word, bool isFunc, bool all) {
    int end = (all) ? 0 : table.top();
    for (int i = this->symbolId - 1; i >= end; --i) {
        if (symbols[i]->word == word && ((isFunc && symbols[i]->value->valueType == ValueType::Function) ||
                                         (!isFunc && symbols[i]->value->valueType != ValueType::Function))) {
            return symbols[i];
        }
    }
    auto *fooValue = new Instruction("int", ValueType::Instruction, nullptr, InstructionType::Zext);
    auto *fooSymbol = new Symbol("int", fooValue);
    return fooSymbol;
}
