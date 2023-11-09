//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_FUNCRPARAMS_H
#define SYSY_COMPILER_FUNCRPARAMS_H
#include "Node.h"
#include <vector>

class FuncRParams : public Node {
public:
    FuncRParams(NodeType nodeType1);

    virtual ~FuncRParams();
};


#endif //SYSY_COMPILER_FUNCRPARAMS_H
