//
// Created by lyh on 11/3/2023.
//

#include "UnaryExp.h"

UnaryExp::UnaryExp(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

void UnaryExp::setWord(const string& word) {
    this->word = word;
}

string UnaryExp::getWord() {
    return this->word;
}
