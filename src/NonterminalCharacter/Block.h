//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_BLOCK_H
#define SYSY_COMPILER_BLOCK_H

#include "BlockItem.h"
#include <vector>

class Block : public Node {
public:
    bool isValid = false;
    void setValid();
};


#endif //SYSY_COMPILER_BLOCK_H
