//
// Created by lyh on 2023/11/1.
//

#include "FuncFParams.h"

FuncFParams::FuncFParams() {

}

void FuncFParams::addFuncFParam(FuncFParam *funcFParam) {
    this->funcFParams.push_back(funcFParam);
}
