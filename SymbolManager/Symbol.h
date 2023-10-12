//
// Created by yh on 2023/10/11.
//

#ifndef SYSY_COMPILER_SYMBOL_H
#define SYSY_COMPILER_SYMBOL_H

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class Symbol {
public:
    int id;
    string word;
    int type; //0->a,1->a[],2->a[][],-1->func
    bool con; //1->const,0->var
    int retype; // 0 void 1 int -1 none
    int paramNum;
    Symbol(int id, const string &word, bool con, int retype, int paramNum);
};


#endif //SYSY_COMPILER_SYMBOL_H
