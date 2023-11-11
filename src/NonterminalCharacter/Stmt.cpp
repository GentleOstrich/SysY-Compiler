//
// Created by lyh on 2023/11/2.
//

#include "Stmt.h"

Stmt::Stmt(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

short Stmt::getType() {
    return type;
}

void Stmt::setStr(string str) {
    this->str = str;
}

string Stmt::getStr() {
    return str;
}