//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_EQEXP_H
#define SYSY_COMPILER_EQEXP_H
#include "Node.h"
#include <vector>
class EqExp : public Node{
public:
    vector<int> op; // 0-EQL 1-NEQ
    void addOp(int op);

    EqExp(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_EQEXP_H
