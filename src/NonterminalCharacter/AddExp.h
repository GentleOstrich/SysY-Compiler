//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_ADDEXP_H
#define SYSY_COMPILER_ADDEXP_H
#include "Node.h"
#include <vector>

class AddExp : public Node {
public:
    vector<short> op; // 0-+ 1--
    void addOp(int op);

    AddExp(NodeType nodeType1);

    virtual ~AddExp();

    ~Node() override ;
};


#endif //SYSY_COMPILER_ADDEXP_H
