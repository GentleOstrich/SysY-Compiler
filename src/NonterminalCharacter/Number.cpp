//
// Created by lyh on 11/6/2023.
//

#include "Number.h"

Number::Number(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

int Number::getVal() {
    return this->val;
}
