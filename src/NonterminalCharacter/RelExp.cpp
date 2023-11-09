//
// Created by lyh on 11/3/2023.
//

#include "RelExp.h"

void RelExp::addOp(int op) {
    this->op.push_back(op);
}

RelExp::RelExp(NodeType nodeType1) : Node(nodeType1) {}
