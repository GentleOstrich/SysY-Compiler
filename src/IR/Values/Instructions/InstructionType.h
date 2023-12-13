//
// Created by lyh on 11/19/2023.
//

#ifndef SYSY_COMPILER_INSTRUCTIONTYPE_H
#define SYSY_COMPILER_INSTRUCTIONTYPE_H

#endif //SYSY_COMPILER_INSTRUCTIONTYPE_H

enum class InstructionType {
    Add,// +
    Sub,// -
    Mul,// *
    Div,// /
    Mod,// %
    Lt, // <
    Le, // <=
    Ge, // >=
    Gt, // >
    Eq, // ==
    Ne, // !=
    Br,
    Call,
    Ret,
    Alloca,
    Load,
    Store,
    GEP, // Get Element Ptr
    Zext,
};