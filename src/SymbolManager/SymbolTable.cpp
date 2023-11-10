//
// Created by lyh on 11/9/2023.
//

#include "SymbolTable.h"
void SymbolTable::createSymbolTable() {
    table.push(this->symbolId);
}

void SymbolTable::addSymbol(Symbol* symbol) {
    if (!findSymbol(symbol->word, symbol->type == -1, false)) {
        symbols.push_back(symbol);
    } else {
        return;
    }
}

bool SymbolTable::findSymbol(const string& word, bool isFunc, bool all) {
    int end = (all) ? 0 : table.top();
    for (int i = this->symbolId - 1; i >= end; --i) {
        if (symbols[i]->word == word && ((isFunc && symbols[i]->type == -1) || (!isFunc && symbols[i]->type != -1))) {
            return true;
        }
    }
    return false;
}

void SymbolTable::deleteSymbolTable() {
    symbolId = table.top();
    table.pop();
}

SymbolTable::SymbolTable() {
    this->table.push(0);
}
