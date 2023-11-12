//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_RELEXP_H
#define SYSY_COMPILER_RELEXP_H
#include "Node.h"
#include <vector>
class RelExp : public Node {
public:
    vector<int> op; // 0-GRE 1-GEQ 2-LSS 3-LEQ
    void addOp(int op);

    RelExp(NodeType nodeType1, int lineNum);

};


#endif //SYSY_COMPILER_RELEXP_H
