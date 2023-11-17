//
// Created by lyh on 2023/11/2.
//

#include "FuncFParam.h"

FuncFParam::FuncFParam(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

// void FuncFParam::setWord(const string &word) {
//     this->word = word;
// }

std::string FuncFParam::getWord()
{
    return this->word;
}

int FuncFParam::getType()
{
    return this->type;
}
