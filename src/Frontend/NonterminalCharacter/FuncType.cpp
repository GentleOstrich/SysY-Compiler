//
// Created by lyh on 2023/11/1.
//

#include "FuncType.h"

FuncType::FuncType(NodeType nodeType, int lineNum) : Node(nodeType, lineNum){}

int FuncType::getType() {
    return this->type;
}
