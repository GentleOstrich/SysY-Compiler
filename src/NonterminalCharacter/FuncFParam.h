//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FUNCFPARAM_H
#define SYSY_COMPILER_FUNCFPARAM_H
#include "Node.h"
#include <vector>

class FuncFParam : public Node {
public:
    FuncFParam(NodeType nodeType1);
    string word;
    short type = 0;
    void setWord(const string& word);
    string getWord() override ;
    short getType() override ;

};


#endif //SYSY_COMPILER_FUNCFPARAM_H
