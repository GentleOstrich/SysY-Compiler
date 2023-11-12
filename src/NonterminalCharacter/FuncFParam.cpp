//
// Created by lyh on 2023/11/2.
//

#include "FuncFParam.h"

FuncFParam::FuncFParam(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void FuncFParam::setWord(const string &word) {
    this->word = word;
}

string FuncFParam::getWord() {
    return this->word;
}

int FuncFParam::getType() {
    return this->type;
}
