//
// Created by lyh on 2023/11/1.
//

#include "ConstDef.h"

ConstDef::ConstDef(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

void ConstDef::setWord(const std::string &word) {
    this->word = word;
}

std::string ConstDef::getWord() {
    return this->word;
}

int ConstDef::getType() {
    return this->type;
}

