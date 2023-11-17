//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_FUNCFPARAM_H
#define SYSY_COMPILER_FUNCFPARAM_H
#include "Node.h"
#include <vector>

class FuncFParam : public Node
{
public:
    FuncFParam(NodeType nodeType, int lineNum);
    std::string word;
    int type = 0;
    // void setWord(const string& word);
    std::string getWord() override;
    int getType() override;
};

#endif // SYSY_COMPILER_FUNCFPARAM_H
