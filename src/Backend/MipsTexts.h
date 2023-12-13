//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSTEXTS_H
#define SYSY_COMPILER_MIPSTEXTS_H


#include <vector>
#include "MipsText.h"

class MipsTexts {
public:
    std::vector<MipsText *> mipTexts;

    std::string translate();

    MipsTexts();

    void addMipsText(MipsText* mipsText);
};


#endif //SYSY_COMPILER_MIPSTEXTS_H
