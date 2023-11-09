//
// Created by lyh on 11/6/2023.
//

#ifndef SYSY_COMPILER_NUMBER_H
#define SYSY_COMPILER_NUMBER_H
#include "Node.h"

class Number : public Node{
public:
    int val;

    Number(NodeType nodeType1);

    virtual ~Number();
};


#endif //SYSY_COMPILER_NUMBER_H
