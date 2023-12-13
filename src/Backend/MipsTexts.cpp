//
// Created by lyh on 12/11/2023.
//

#include "MipsTexts.h"

std::string MipsTexts::translate() {
    std::string code;
    code += ".text\n\n";
    code += this->mipTexts[this->mipTexts.size() - 1]->translate();
    code += "\n";
    for (int i = 0; i < this->mipTexts.size() - 1; ++i) {
        code += this->mipTexts[i]->translate();
        code += "\n";
    }
    return code;
}

MipsTexts::MipsTexts() {}

void MipsTexts::addMipsText(MipsText *mipsText) {
    this->mipTexts.push_back(mipsText);
}
