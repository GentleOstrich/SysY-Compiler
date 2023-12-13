//
// Created by lyh on 12/11/2023.
//

#include <iostream>
#include "MipsModule.h"
#include <fstream>

extern std::ofstream m_ofs;

void MipsModule::translate() {
    std::string code;
    code += this->mipsDatas->translate();
    code += this->mipsTexts->translate();
    m_ofs << code << std::endl;
}

MipsModule::MipsModule() {
    this->mipsDatas = new MipsDatas();
    this->mipsTexts = new MipsTexts();
    this->curMipsText = nullptr;
    this->curMipsBasicBlock = nullptr;
}

void MipsModule::addMipsData(MipsData *mipsData) {
    this->mipsDatas->addMipsData(mipsData);
}

void MipsModule::addMipsText(MipsText *mipsText) {
    this->curMipsText = mipsText;
    this->mipsTexts->addMipsText(mipsText);
}
