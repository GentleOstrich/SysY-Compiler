//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCTYPE_H
#define SYSY_COMPILER_FUNCTYPE_H
#include "Node.h"
#include <string>
class FuncType : public Node {
public:
    int type; // 0 is int 1 is void
};



#endif //SYSY_COMPILER_FUNCTYPE_H
