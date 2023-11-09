//
// Created by yh on 2023/10/11.
//

#include "Symbol.h"
#include <stack>
#include <vector>
using namespace std;

Symbol::Symbol(short type, const string &word, bool con, Func* func) {
    this->type = type;
    this->word = word;
    this->con = con;
    this->func = func;
}
