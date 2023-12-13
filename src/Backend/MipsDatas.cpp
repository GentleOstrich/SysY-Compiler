//
// Created by lyh on 12/11/2023.
//

#include "MipsDatas.h"

std::string MipsDatas::translate() {
    std::string code;
    code += ".data\n";
    for (auto *child:this->mipsDatas) {
        code += child->translate();
    }
    code += "\n";
    return code;
}

MipsDatas::MipsDatas() {}

void MipsDatas::addMipsData(MipsData *mipsData) {
    this->mipsDatas.push_back(mipsData);

}
