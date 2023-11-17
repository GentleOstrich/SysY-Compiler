//
// Created by lyh on 11/3/2023.
//

#include "UnaryExp.h"

UnaryExp::UnaryExp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

// void UnaryExp::setWord(const string& word) {
//     this->word = word;
// }

std::string UnaryExp::getWord()
{
    return this->word;
}
