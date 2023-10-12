//
// Created by yh on 2023/10/11.
//

#include "Symbol.h"
#include <stack>
#include <vector>
using namespace std;
int symbolId;
vector<Symbol> symbols;
stack<int> symbolTable;

Symbol::Symbol(int id, const string &word, bool con, int retype, int paramNum) {
    this->id = id; this->word = word; this->con = con; this->retype = retype; this->paramNum = paramNum;
}


