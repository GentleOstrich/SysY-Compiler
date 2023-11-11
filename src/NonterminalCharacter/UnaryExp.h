//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_UNARYEXP_H
#define SYSY_COMPILER_UNARYEXP_H

#include "Node.h"
#include <vector>

class UnaryExp : public Node {
public:
    UnaryExp(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_UNARYEXP_H
