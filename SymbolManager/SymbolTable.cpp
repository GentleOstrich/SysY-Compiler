//
// Created by yh on 2023/10/11.
//

#include "SymbolTable.h"
SymbolTable::SymbolTable(int cnt, int id, SymbolTable* father) {
    this->cnt = cnt;
    this->id = id;
    this->father = father;
}

void SymbolTable::addSon(SymbolTable *son) {
    this->sons.push_back(son);
}

bool SymbolTable::exist(string word) {
    return !(this->directory.find(word) == nullptr);
}

void SymbolTable::addSymbol(Symbol symbol) {
    this->directory.insert(make_pair(symbol.word, symbol));
}