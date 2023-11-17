//
// Created by lyh on 11/3/2023.
//

#include "AddExp.h"

AddExp::AddExp(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int AddExp::getOp()
{
    return op;
}
