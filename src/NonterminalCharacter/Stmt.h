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
    bool isBreak = false;
    bool isContinue = false;
    bool isReturn = false;
    bool isPrintf = false;
    bool isGetInt = false;
    void setBreak();
    void  setContinue();
    void setReturn();
    void setPrintf();
    void setGetInt();

};


#endif //SYSY_COMPILER_STMT_H
