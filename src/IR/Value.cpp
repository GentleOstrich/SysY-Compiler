//
// Created by lyh on 11/17/2023.
//

#include "Value.h"

#include <utility>

Value::Value(std::string name, ValueType valueType) :
        name(std::move(name)), valueType(valueType) {}

void Value::addUse(Use *use) {
    this->uses.push_back(use);

}

void Value::translate() {

}

std::string Value::getName() {
    return "";
}
