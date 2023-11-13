//
// Created by lyh on 11/3/2023.
//

#include "AddExp.h"

AddExp::AddExp(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

int AddExp::getOp() {
    return op;
}
