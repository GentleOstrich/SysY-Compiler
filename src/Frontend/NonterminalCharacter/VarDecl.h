//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDECL_H
#define SYSY_COMPILER_VARDECL_H
#include "Node.h"
#include <vector>
class VarDecl : public Node {
public:
    VarDecl(NodeType nodeType, int lineNum);

};


#endif //SYSY_COMPILER_VARDECL_H
