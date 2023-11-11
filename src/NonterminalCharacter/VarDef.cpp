//
// Created by lyh on 2023/11/1.
//

#include "VarDef.h"

#include <utility>

VarDef::VarDef(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void VarDef::setWord(const string& word) {
    this->word = word;
}

string VarDef::getWord() {
    return this->word;
}

bool VarDef::hasEqual() {
    return this->Equal;
}

short VarDef::getType() {
    return this->type;
}


