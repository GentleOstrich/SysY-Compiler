//
// Created by lyh on 2023/11/2.
//

#include "LVal.h"

LVal::LVal(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

std::string LVal::getWord() {
    return this->word;
}

int LVal::getType() {
    return this->type;
}