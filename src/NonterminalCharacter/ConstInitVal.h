//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTINITVAL_H
#define SYSY_COMPILER_CONSTINITVAL_H
#include "Node.h"
#include <vector>

class ConstInitVal : public Node {
public:
    bool isValid = false;
    void setValid();

};


#endif //SYSY_COMPILER_CONSTINITVAL_H
