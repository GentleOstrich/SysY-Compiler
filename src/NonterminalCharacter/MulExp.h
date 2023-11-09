//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_MULEXP_H
#define SYSY_COMPILER_MULEXP_H
#include "Node.h"
#include <vector>

class MulExp : public Node {
public:
    vector<short> op; // 0-* 1-/ 2-%
    void addOp(int op);

    MulExp(NodeType nodeType1);

};


#endif //SYSY_COMPILER_MULEXP_H
