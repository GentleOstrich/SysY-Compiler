//
// Created by lyh on 11/20/2023.
//

#ifndef SYSY_COMPILER_GLOBALVAR_H
#define SYSY_COMPILER_GLOBALVAR_H


#include "../Value.h"
class Module;

class GlobalVar : public Value {
public:
    Module* module;

    bool isConst;

    int val;

    GlobalVar(const std::string &name, ValueType valueType, Module *module, bool isConst, int val);

    void translate() override;

    std::string getName() override ;

};


#endif //SYSY_COMPILER_GLOBALVAR_H
