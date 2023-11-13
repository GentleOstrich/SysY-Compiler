//
// Created by lyh on 11/3/2023.
//

#include "MulExp.h"

MulExp::MulExp(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

int MulExp::getOp() {
    return op;
}

