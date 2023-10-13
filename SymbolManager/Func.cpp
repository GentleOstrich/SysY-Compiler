//
// Created by lyh on 10/13/2023.
//
#include "Func.h"
#include "Symbol.h"
Func::Func(int id, int type, const string &word, bool con, int retype, int paramNum, int paraNum) : Symbol::Symbol(type, word, con) {
    this->retype = retype;
    this->paraNum = paramNum;
}