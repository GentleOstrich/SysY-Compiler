//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_STMT_H
#define SYSY_COMPILER_STMT_H

#include "Node.h"

#include <vector>
#include <string>

class Stmt : public Node {
public:
    int type = 0; // 0 normal 1-if 2-for 3-break 4-continue 5-return 6-getint 7-printf
    Stmt(NodeType nodeType1);

    virtual ~Stmt();
};


#endif //SYSY_COMPILER_STMT_H
