//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDECL_H
#define SYSY_COMPILER_VARDECL_H
#include "Btype.h"
#include "VarDef.h"
#include <vector>
class VarDecl {
public:
    Btype *btype;
    std::vector<VarDef*> varDefs;
    VarDecl();
    void setBType(Btype *btype);
    void  addVarDef(VarDef *varDef);

};


#endif //SYSY_COMPILER_VARDECL_H
