//
// Created by lyh on 11/3/2023.
//

#include "MulExp.h"

MulExp::MulExp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int MulExp::getOp() {
    return op;
}

