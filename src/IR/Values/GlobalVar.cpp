//
// Created by lyh on 11/20/2023.
//

#include "GlobalVar.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

void GlobalVar::translate() {
    if (this->isConst) {
        c_ofs << this->getName() << " = dso_local constant " << "i" << std::to_string(this->ty)  << " " << std::to_string(this->val) << std::endl;
    } else {
        c_ofs << this->getName()<< " = dso_local global " << "i" << std::to_string(this->ty) <<  " " << std::to_string(this->val) << std::endl;
    }
}


std::string GlobalVar::getName() {
    return "@" + this->name;
}

GlobalVar::GlobalVar(const std::string &name, ValueType valueType, Module *module, bool isConst, int val) : User(name,
                                                                                                                 valueType),
                                                                                                            module(module),
                                                                                                            isConst(isConst),
                                                                                                            val(val) {}


