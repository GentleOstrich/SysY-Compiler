//
// Created by lyh on 12/11/2023.
//

#include "MipsBuilder.h"

void MipsBuilder::translate() {
    this->mipsModule->translate();
}

void MipsBuilder::genMipsData(std::string name, int type, std::string val) {
    auto *mipsData = new MipsData(name, type, val);
    this->mipsModule->addMipsData(mipsData);
}

MipsBuilder::MipsBuilder() {
    this->mipsModule = new MipsModule();
}

void MipsBuilder::genMipsText(std::string name) {
    auto *mipsText = new MipsText(name);
    this->mipsModule->addMipsText(mipsText);
}

void MipsBuilder::genMipsBasicBlock(std::string name) {
    auto *mipsBasicBlock = new MipsBasicBlock(name);
    this->mipsModule->curMipsBasicBlock = mipsBasicBlock;
    this->mipsModule->curMipsText->addMipsBasicBlock(mipsBasicBlock);
}

void MipsBuilder::genInstruction(MipsInstruction *Ins) {
    this->mipsModule->curMipsBasicBlock->addIns(Ins);
}


