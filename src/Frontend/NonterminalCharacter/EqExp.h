//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_EQEXP_H
#define SYSY_COMPILER_EQEXP_H
#include "Node.h"
#include <vector>
class EqExp : public Node{
public:
    int op = -1;

    EqExp(NodeType nodeType, int lineNum);

    int getOp() override;
};


#endif //SYSY_COMPILER_EQEXP_H
