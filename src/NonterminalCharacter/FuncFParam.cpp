//
// Created by lyh on 2023/11/2.
//

#include "FuncFParam.h"

FuncFParam::FuncFParam(NodeType nodeType1) : Node(nodeType1) {}

void FuncFParam::setWord(const string &word) {
    this->word = word;
}

string FuncFParam::getWord() {
    return this->word;
}

short FuncFParam::getType() {
    return this->type;
}
