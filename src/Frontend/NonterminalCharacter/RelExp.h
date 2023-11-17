//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_RELEXP_H
#define SYSY_COMPILER_RELEXP_H
#include "Node.h"
#include <vector>
class RelExp : public Node
{
public:
    int op = -1; // 0-GRE 1-GEQ 2-LSS 3-LEQ
    RelExp(NodeType nodeType, int lineNum);
    int getOp() override;
};

#endif // SYSY_COMPILER_RELEXP_H
