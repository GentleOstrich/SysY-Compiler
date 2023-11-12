//
// Created by lyh on 2023/11/2.
//

#include "Block.h"

Block::Block(NodeType nodeType1, int lineNum) : Node(nodeType1, lineNum) {}

int Block::getLastLine() {
    return this->lastLine;
}