//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_UNARYOP_H
#define SYSY_COMPILER_UNARYOP_H
#include "Node.h"

class UnaryOp : public Node {
public:
    short type = 0; // 0-+ 1-- 1-!
    UnaryOp(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_UNARYOP_H
