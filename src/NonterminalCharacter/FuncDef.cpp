//
// Created by lyh on 2023/11/1.
//

#include "FuncDef.h"

FuncDef::FuncDef(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void FuncDef::setWord(const string& word) {
    this->word = word;
}

string FuncDef::getWord() {
    return this->word;
}

