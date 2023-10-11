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
    int tableId;
    string word;
    int type; //0->a,1->a[],2->a[][],-1->func
    int con; //1->const,0->var
};


#endif //SYSY_COMPILER_SYMBOL_H
