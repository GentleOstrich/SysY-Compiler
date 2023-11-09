//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_PRIMARYEXP_H
#define SYSY_COMPILER_PRIMARYEXP_H
#include "Node.h"
#include <vector>

class PrimaryExp : public Node {
public:
    PrimaryExp(NodeType nodeType1);

    virtual ~PrimaryExp();
};


#endif //SYSY_COMPILER_PRIMARYEXP_H
