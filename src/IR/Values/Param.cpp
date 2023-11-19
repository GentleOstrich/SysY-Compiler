//
// Created by lyh on 11/19/2023.
//

#include "Param.h"

Param::Param(const std::string &name, ValueType valueType, int pos) : Value(name, valueType), pos(pos) {}
