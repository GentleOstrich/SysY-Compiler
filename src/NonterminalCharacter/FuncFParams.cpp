//
// Created by lyh on 2023/11/1.
//

#include "FuncFParams.h"

FuncFParams::FuncFParams() {

}

int FuncFParams::addFuncFParam(Nonterminal *FuncFParam) {
    this->FuncFParam.push_back(FuncFParam);
    return 0;
}
