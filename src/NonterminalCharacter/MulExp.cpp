//
// Created by lyh on 11/3/2023.
//

#include "MulExp.h"

void MulExp::addOp(int op) {
    this->op.push_back(op);
}

MulExp::MulExp(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

vector<int>* MulExp::getOp() {
    return &(this->op);
}

