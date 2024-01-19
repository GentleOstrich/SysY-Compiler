//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_COND_H
#define SYSY_COMPILER_COND_H
#include "Node.h"

class Cond : public Node
{
public:
    Cond(NodeType nodeType, int lineNum);
};

#endif // SYSY_COMPILER_COND_H
