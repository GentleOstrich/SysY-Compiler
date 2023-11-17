//
// Created by lyh on 2023/11/1.
//

#include "FuncDef.h"

FuncDef::FuncDef(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

// void FuncDef::setWord(const std::string& word) {
//     this->word = word;
// }

std::string FuncDef::getWord() {
    return this->word;
}

