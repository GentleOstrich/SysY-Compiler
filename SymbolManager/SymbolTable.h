//
// Created by yh on 2023/10/11.
//
#ifndef SYSY_COMPILER_SYMBOLTABLE_H
#define SYSY_COMPILER_SYMBOLTABLE_H


#include <string>
#include <vector>
#include "Symbol.h"
using namespace std;



class SymbolTable {
public:
    int cnt;
    int id;
    SymbolTable* father;
    vector<SymbolTable*> sons;
    unordered_map<string, Symbol> directory;

    SymbolTable(int cnt, int id, SymbolTable* father);
    void addSon(SymbolTable* son);
    bool exist(string word);
    void addSymbol(Symbol symbol);

};


#endif //SYSY_COMPILER_SYMBOLTABLE_H
