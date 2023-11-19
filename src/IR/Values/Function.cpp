//
// Created by lyh on 11/17/2023.
//

#include "Function.h"

Function::Function(const std::string &name, ValueType valueType, Module *module, int cnt) : Value(name, valueType),
                                                                                            module(module), cnt(cnt) {}
