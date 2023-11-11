//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_DECL_H
#define SYSY_COMPILER_DECL_H
#include "Node.h"

class Decl : public Node {
public:
    int a = 0;
    Decl(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_DECL_H
