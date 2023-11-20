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
    int pos; // value's pos in user --- add i32 %a, %b --- a is 0, b is 1
    Use(Value* value, User* user, int pos);
};


#endif //SYSY_COMPILER_USE_H
