//
// Created by lyh on 11/17/2023.
//

#include "User.h"

User::User(const std::string &name, ValueType valueType) :
        Value(name, valueType) {}

void User::addOperand(Use *use) {
    this->operands.push_back(use);
}
