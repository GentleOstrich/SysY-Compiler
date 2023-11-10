//
// Created by lyh on 2023/11/1.
//

#include "ConstDef.h"

ConstDef::ConstDef(NodeType nodeType1) : Node(nodeType1) {}

void ConstDef::setWord(const string &word) {
    this->word = word;
}

string ConstDef::getWord() {
    return this->word;
}

short ConstDef::getType() {
    return this->type;
}

