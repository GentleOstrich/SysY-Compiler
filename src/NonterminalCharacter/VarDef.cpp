//
// Created by lyh on 2023/11/1.
//

#include "VarDef.h"

#include <utility>

VarDef::VarDef(NodeType nodeType1) : Node(nodeType1) {}

void VarDef::setWord(const string& word) {
    this->word = word;
}

string VarDef::getWord() {
    return this->word;
}

VarDef::~VarDef() {

}
