//
// Created by lyh on 2023/11/1.
//

#include "ConstDef.h"

ConstDef::ConstDef(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void ConstDef::setWord(const string &word) {
    this->word = word;
}

string ConstDef::getWord() {
    return this->word;
}

int ConstDef::getType() {
    return this->type;
}

