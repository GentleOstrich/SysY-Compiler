//
// Created by lyh on 11/3/2023.
//

#include "EqExp.h"

void EqExp::addOp(int op) {
    this->op.push_back(op);
}

EqExp::EqExp(NodeType nodeType1) : Node(nodeType1) {}

