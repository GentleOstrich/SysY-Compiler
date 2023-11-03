//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_COMPUNIT_H
#define SYSY_COMPILER_COMPUNIT_H

#include <vector>
#include "Decl.h"
#include "FuncDef.h"
#include "MainFuncDef.h"

class CompUnit {
public:
    std::vector<Decl*> decls;
    std::vector<FuncDef*> funcDefs;
    MainFuncDef *mainFuncDef;
    CompUnit();

    void addDecl(Decl *decl);

    void addFuncDef(FuncDef *funcDef);

    void setMainFuncDef(MainFuncDef *mainFuncDef);
};


#endif //SYSY_COMPILER_COMPUNIT_H
