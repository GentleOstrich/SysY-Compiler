//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_MIPSDATAS_H
#define SYSY_COMPILER_MIPSDATAS_H


#include <vector>
#include "MipsData.h"

class MipsDatas {
public:
    std::vector<MipsData *> mipsDatas;

    std::string translate();

    MipsDatas();

    void addMipsData(MipsData* mipsData);
};


#endif //SYSY_COMPILER_MIPSDATAS_H
