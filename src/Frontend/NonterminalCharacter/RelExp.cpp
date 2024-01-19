//
// Created by lyh on 11/3/2023.
//

#include "RelExp.h"

RelExp::RelExp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int RelExp::getOp() {
    return op;
}