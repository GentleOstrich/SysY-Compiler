//
// Created by lyh on 2023/11/2.
//

#include "LVal.h"

LVal::LVal(NodeType nodeType1) : Node(nodeType1) {}

void LVal::setWord(const string &word) {
    this->word = word;
}

string LVal::getWord() {
    return this->word;
}
