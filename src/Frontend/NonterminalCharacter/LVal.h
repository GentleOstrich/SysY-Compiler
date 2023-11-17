//
// Created by lyh on 2023/11/2.
//

#ifndef SYSY_COMPILER_LVAL_H
#define SYSY_COMPILER_LVAL_H
#include "Node.h"
#include <vector>

class LVal : public Node {
public:
    LVal(NodeType nodeType, int lineNum);
    std::string word;
    int type = 0;
    std::string getWord() override ;
    int getType() override ;

};


#endif //SYSY_COMPILER_LVAL_H
