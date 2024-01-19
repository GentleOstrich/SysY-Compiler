//
// Created by lyh on 11/17/2023.
//

#include "Module.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

void Module::translate() {
    c_ofs << "declare i32 @getint()\n" <<
          "declare void @putint(i32)\n" <<
          "declare void @putch(i32)\n" <<
          "declare void @putstr(i8*)" << std::endl;

    for (auto *child: globalVars) {
        child->translate();
    }

    for (int i = 0; i < functions.size() - 1; ++i) {
        functions[i]->translate();
    }

    if (!globalVars.empty()) {
        c_ofs << std::endl;
    }

    functions[functions.size() - 1]->translate();
}

void Module::addGlobalVar(GlobalVar *globalVar) {
    this->globalVars.push_back(globalVar);
}

void Module::addFunction(Function *function) {
    this->functions.push_back(function);
}

Module::Module() {

}
