//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSMODULE_H
#define SYSY_COMPILER_MIPSMODULE_H


#include "MipsDatas.h"
#include "MipsTexts.h"


class MipsModule {
public:
    MipsDatas *mipsDatas;
    MipsTexts *mipsTexts;
    MipsText *curMipsText;
    MipsBasicBlock *curMipsBasicBlock;;

    void translate();

    void addMipsData(MipsData *mipsData);

    void addMipsText(MipsText *mipsText);

    MipsModule();


};


#endif //SYSY_COMPILER_MIPSMODULE_H
