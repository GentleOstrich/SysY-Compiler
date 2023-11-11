//
// Created by lyh on 2023/11/1.
//

#include "FuncType.h"

FuncType::FuncType(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum){}

short FuncType::getType() {
    return this->type;
}
