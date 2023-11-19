//
// Created by lyh on 11/17/2023.
//

#ifndef SYSY_COMPILER_VALUETYPE_H
#define SYSY_COMPILER_VALUETYPE_H

enum class ValueType {
    Function,
    Integer,
    Label,
    None,
    Pointer,
    Void,
    Array,
    Instruction,
    BasicBlock
};
#endif //SYSY_COMPILER_VALUETYPE_H
