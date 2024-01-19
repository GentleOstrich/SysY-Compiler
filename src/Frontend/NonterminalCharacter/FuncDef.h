//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCDEF_H
#define SYSY_COMPILER_FUNCDEF_H
#include "Node.h"
#include <vector>

class FuncDef : public Node
{
public:
    FuncDef(NodeType nodeType, int lineNum);
    std::string word;
    // void setWord(const std::string& word);
    std::string getWord() override;
};

#endif // SYSY_COMPILER_FUNCDEF_H
