//
// Created by lyh on 12/11/2023.
//

#ifndef SYSY_COMPILER_HANDLER_H
#define SYSY_COMPILER_HANDLER_H

#include <unordered_map>
#include "../IR/Module.h"
#include "MipsBuilder.h"

class Handler {
public:
    MipsBuilder *mipsBuilder;

    int regs[32]{};

    std::unordered_map<Value *, int> value2reg;

    std::unordered_map<Value *, int> value2offset;

    int curOffSet = 0;

    void handleModule(Module *module);

    void handleGlobalVar(GlobalVar *globalVar);

    void handleFunction(Function *function);

    void handleBasicBlock(BasicBlock *basicBlock);

    int findReg(Value *value);

    int allocaReg(Value *value, bool *isAllocated);

    void removeReg(Value *value);

    int findOffset(Value *value, std::string *glob);

    void handleAdd(Instruction *child);

    void handleSub(Instruction *child, int reg);

    void handleMul(Instruction *child);

    void handleDiv(Instruction *child, int *reg);

    void handleMod();

    void handleLt(Instruction *child);

    void handleLe(Instruction *child);

    void handleGe(Instruction *child);

    void handleGt(Instruction *child);

    void handleEq(Instruction *child);

    void handleNe(Instruction *child);

    void handleBr(Instruction *child);

    void handleCall(Instruction *child);

    void handleRet(Instruction *child);

    void handleAlloca(Instruction *child);

    void handleLoad(Instruction *child);

    void handleStore(Instruction *child);

    void handleGEP();

    void handleZext(Instruction *child);

    Handler();

    void save(); // 保存现场：将寄存器里的值都存进内存中，调整$sp的位置


};


#endif //SYSY_COMPILER_HANDLER_H
