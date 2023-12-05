//
// Created by lyh on 11/20/2023.
//

#ifndef SYSY_COMPILER_GLOBALVAR_H
#define SYSY_COMPILER_GLOBALVAR_H


#include "../User.h"
class Module;

class GlobalVar : public User {
public:
    Module* module;

    bool isConst;

    std::vector<int> dims;

    GlobalVar(const std::string &name, ValueType valueType, Module *module, bool isConst);

    void translate() override;

    std::string getName() override ;

    void addDim(int dim);

    std::string getType() override;

    std::string getInit() override;

    std::string getContent() override ;

};


#endif //SYSY_COMPILER_GLOBALVAR_H
