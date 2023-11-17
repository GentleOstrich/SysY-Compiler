//
// Created by lyh on 2023/11/1.
//

#include "VarDef.h"

#include <utility>

VarDef::VarDef(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

// void VarDef::setWord(const string& word) {
//     this->word = word;
// }

std::string VarDef::getWord()
{
    return this->word;
}

bool VarDef::hasEqual()
{
    return this->Equal;
}

int VarDef::getType()
{
    return this->type;
}
