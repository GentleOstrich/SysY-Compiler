//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_ADDEXP_H
#define SYSY_COMPILER_ADDEXP_H
#include "Node.h"
#include <vector>

class AddExp : public Node
{
public:
    int op = -1; // 0-+ 1--
    AddExp(NodeType nodeType, int lineNum);
    int getOp() override;
};

#endif // SYSY_COMPILER_ADDEXP_H
