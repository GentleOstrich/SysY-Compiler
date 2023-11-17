//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_MULEXP_H
#define SYSY_COMPILER_MULEXP_H
#include "Node.h"
#include <vector>

class MulExp : public Node {
public:
    int op = -1; // 0-* 1-/ 2-%

    MulExp(NodeType nodeType, int lineNum);
    
    int getOp() override;

};


#endif //SYSY_COMPILER_MULEXP_H
