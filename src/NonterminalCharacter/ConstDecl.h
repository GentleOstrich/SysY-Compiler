//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDECL_H
#define SYSY_COMPILER_CONSTDECL_H
#include "Node.h"
#include <vector>

class ConstDecl : public Node{
public:
    ConstDecl(NodeType nodeType1);

    virtual ~ConstDecl();
};


#endif //SYSY_COMPILER_CONSTDECL_H
