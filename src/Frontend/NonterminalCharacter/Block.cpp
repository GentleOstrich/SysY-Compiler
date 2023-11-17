//
// Created by lyh on 2023/11/2.
//

#include "Block.h"

Block::Block(NodeType nodeType, int lineNum) : Node(nodeType, lineNum) {}

int Block::getLastLine()
{
    return this->lastLine;
}