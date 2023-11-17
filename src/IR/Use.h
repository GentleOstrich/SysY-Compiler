//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_USE_H
#define SYSY_COMPILER_USE_H

#include "Values/Value.h"
#include "Values/User.h"

class Use {
public:
    Value value;
    User user;
    int pos;
    Use(const Value &value, const User &user, int pos);
};


#endif //SYSY_COMPILER_USE_H
