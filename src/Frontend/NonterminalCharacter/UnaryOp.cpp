//
// Created by lyh on 11/3/2023.
//

#include "UnaryOp.h"

UnaryOp::UnaryOp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int UnaryOp::getType() {
    return this->type;
}

