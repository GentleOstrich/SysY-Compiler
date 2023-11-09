//
// Created by lyh on 11/9/2023.
//

#ifndef SYSY_COMPILER_NODETYPE_H
#define SYSY_COMPILER_NODETYPE_H


enum class NodeType {
    AddExp,
    Block,
    BlockItem,
    BType,
    CompUnit,
    Cond,
    ConstDecl,
    ConstDef,
    ConstExp,
    ConstInitVal,
    Decl,
    EqExp,
    Exp,
    ForStmt,
    FuncDef,
    FuncFParam,
    FuncFParams,
    FuncRParams,
    FuncType,
    InitVal,
    LAndExp,
    LOrExp,
    LVal,
    MainFuncDef,
    MulExp,
    Node,
    Number,
    PrimaryExp,
    RelExp,
    Stmt,
    UnaryExp,
    UnaryOp,
    VarDecl,
    VarDef
};


#endif //SYSY_COMPILER_NODETYPE_H
