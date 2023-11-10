//
// Created by lyh on 2023/11/1.
//

#include "FuncType.h"

FuncType::FuncType(NodeType nodeType1) : Node(nodeType1){}

short FuncType::getType() {
    return this->type;
}
