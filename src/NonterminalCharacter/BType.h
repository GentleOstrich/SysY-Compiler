//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_BTYPE_H
#define SYSY_COMPILER_BTYPE_H
#include "Node.h"
#include <string>

class BType : public Node {
public:
    int type; // 0 is int
    BType(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_BTYPE_H
