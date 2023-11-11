//
// Created by lyh on 11/3/2023.
//

#include "AddExp.h"

void AddExp::addOp(int op) {
    this->op.push_back(op);
}

AddExp::AddExp(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}
