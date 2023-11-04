//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_MAINFUNCDEF_H
#define SYSY_COMPILER_MAINFUNCDEF_H
#include "Block.h"

class MainFuncDef {
public:
    Block *block;
    MainFuncDef();
    void setBlock(Block *block);
};


#endif //SYSY_COMPILER_MAINFUNCDEF_H
