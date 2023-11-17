//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_USE_H
#define SYSY_COMPILER_USE_H
#include <memory>
class User;
class Value;

class Use {
public:
    Value* value;
    User* user;
    int pos;

    Use(Value* value, User* user, int pos);
};


#endif //SYSY_COMPILER_USE_H
