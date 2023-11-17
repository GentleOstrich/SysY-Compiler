//
// Created by lyh on 11/3/2023.
//

#include "EqExp.h"

EqExp::EqExp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int EqExp::getOp() {
    return op;
}