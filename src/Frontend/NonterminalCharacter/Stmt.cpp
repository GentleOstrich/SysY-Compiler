//
// Created by lyh on 2023/11/2.
//

#include "Stmt.h"

Stmt::Stmt(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int Stmt::getType() {
    return type;
}

// void Stmt::setStr(std::string str) {
//     this->str = str;
// }

std::string Stmt::getStr() {
    return str;
}

