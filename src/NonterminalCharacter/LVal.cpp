//
// Created by lyh on 2023/11/2.
//

#include "LVal.h"

LVal::LVal(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void LVal::setWord(const string &word) {
    this->word = word;
}

string LVal::getWord() {
    return this->word;
}
