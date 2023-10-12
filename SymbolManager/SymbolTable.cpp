//
// Created by yh on 2023/10/11.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable(int cnt, int id, int fatherId) {
    this->cnt = cnt;
    this->id = id;
    this->fatherId = fatherId;
}

bool SymbolTable::exist(string word) {
    return !(this->directory.find(word) == this->directory.end());
}

void SymbolTable::addSymbol(Symbol symbol) {
    this->directory.insert(make_pair(symbol.word, symbol));
}