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

Symbol::Symbol(int type, const string &word, bool con) {
    this->type = type;
    this->word = word;
    this->con = con;
}
