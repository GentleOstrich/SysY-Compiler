//
// Created by lyh on 12/11/2023.
//

#include <iostream>
#include "Handler.h"
#include "MipsData.h"
#include "../IR/Values/BasicBlock.h"
#include "../IR/Values/Function.h"
#include "../IR/Values/Param.h"
#include "MipsInstructions/Li.h"
#include "../IR/Values/Const.h"
#include "MipsInstructions/Sw.h"
#include "MipsInstructions/Add.h"
#include "MipsInstructions/Lw.h"
#include "MipsInstructions/Div.h"
#include "MipsInstructions/Sub.h"
#include "MipsInstructions/Mult.h"
#include "MipsInstructions/Mflo.h"
#include "MipsInstructions/Mfhi.h"
#include "MipsInstructions/J.h"
#include "MipsInstructions/Beq.h"
#include "MipsInstructions/Seq.h"
#include "MipsInstructions/Sne.h"
#include "MipsInstructions/Sle.h"
#include "MipsInstructions/Sge.h"
#include "MipsInstructions/Sgt.h"
#include "MipsInstructions/Slt.h"
#include "MipsInstructions/Move.h"
#include "MipsInstructions/Jal.h"
#include "MipsInstructions/Jr.h"
#include "MipsInstructions/Addiu.h"
#include "MipsInstructions/Annotation.h"
#include "MipsInstructions/Syscall.h"
#include "MipsInstructions/La.h"

int Handler::findReg(Value *value) {
    for (auto &it:value2reg) {
        if (value->getName() == it.first->getName()) {
            return it.second;
        }
    }
    return -1;
}

// 分配t寄存器 value2reg 存的是键值对 key是value reg是寄存器 这个value存在哪个寄存器里
int Handler::allocaReg(Value *value, bool *isAllocated) {
    if (value->valueType == ValueType::Instruction) {
        auto *ins = (Instruction *) value;
        for (auto &it : value2reg) {
            // 防止load多次
            if (ins->instructionType == InstructionType::Load && it.first->valueType == ValueType::Instruction) {
                auto *ins1 = ((Instruction *) it.first);
                if (ins1->instructionType == InstructionType::Load) {
                    if (ins1->operands[0]->value->getName() == ins->operands[0]->value->getName()) {
                        this->value2reg[value] = it.second;
                        *isAllocated = true;
                        return it.second;
                    }
                }
            }
        }
    }
    // 要不然就给第一个为空的寄存器
    for (int i = 8; i <= 15; ++i) {
        if (regs[i] == 0) {
            this->value2reg[value] = i;
            regs[i] = 1;
            return i;
        }
    }
    std::cout << "t寄存器不够用啦" << std::endl;
    return -1;
}

// 找value在内存中的偏移量
int Handler::findOffset(Value *value, std::string *glob) {
    if (value2offset.find(value) == value2offset.end()) {
        if (value->valueType == ValueType::Global) {
            *glob = value->getName();
        }
    } else {
        return value2offset[value];
    }
}

void Handler::handleModule(Module *module) {
    for (auto *globalVar : module->globalVars) {
        handleGlobalVar(globalVar);
    }
//    J* j = new J("main");
//    this->mipsBuilder->genInstruction(j);
    for (auto *function : module->functions) {
        this->curOffSet = 0;
        handleFunction(function);
    }
    this->mipsBuilder->translate();
}

void Handler::handleAlloca(Instruction *child) {
    this->value2offset[child] = this->curOffSet;
    int x = 1;
    for (auto dim : child->dims) {
        x *= dim;
    }
    for (int i = 0; i < x; ++i) {
        this->curOffSet -= 4;
    }
}

void Handler::handleGlobalVar(GlobalVar *globalVar) {
    std::string code;
    std::string name = globalVar->name;
    int type = 0;
    std::string val;
    for (auto *child : globalVar->operands) {
        val += child->value->getName();
        val += ", ";
    }
    if (val.empty()) {
        val += "0";
    } else {
        val = val.substr(0, val.size() - 2);
    }
    this->mipsBuilder->genMipsData(name, type, val);
}

void Handler::handleFunction(Function *function) {
    std::cout << function->getName() << std::endl;
    if (function->getName() == "@getint" || function->getName() == "@putint" || function->getName() == "@putch" ||
        function->getName() == "@putstr") {
        return;
    }
    mipsBuilder->genMipsText(function->getName().substr(1, function->getName().size() - 1));
    for (auto *param : function->params) {
        this->value2offset[param] = this->curOffSet;
        this->curOffSet -= 4;
    }
    for (auto *child : function->basicBlocks) {
        handleBasicBlock(child);
    }
    for (int &reg : regs) {
        reg = 0;
    }
    value2reg.clear();
    value2offset.clear();
    curOffSet = 0;
}

Handler::Handler() {
    this->mipsBuilder = new MipsBuilder();
}

int modReg = -1;
int oldSp = 0;

bool saved = false;

void Handler::handleBasicBlock(BasicBlock *basicBlock) {
    mipsBuilder->genMipsBasicBlock(basicBlock->getName());
    for (auto *child : basicBlock->instructions) {
        if (child->useless) {
            continue;
        }
        if (!child->uses.empty() && child->uses[0]->user->valueType == ValueType::Instruction) {
            auto *ins = (Instruction *) child->uses[0]->user;
            if (ins->instructionType == InstructionType::Call && !saved &&
                ins->operands[0]->value->getName() != "@putint" && ins->operands[0]->value->getName() != "@putchar") {
                save();
            }
        }
        if (child->instructionType == InstructionType::Alloca) {
            handleAlloca(child);
        } else if (child->instructionType == InstructionType::Add) {
            handleAdd(child);
        } else if (child->instructionType == InstructionType::Sub) {
            handleSub(child, modReg);
        } else if (child->instructionType == InstructionType::Mul) {
            handleMul(child);
        } else if (child->instructionType == InstructionType::Div) {
            handleDiv(child, &modReg);
        } else if (child->instructionType == InstructionType::Store) {
            handleStore(child);
        } else if (child->instructionType == InstructionType::Load) {
            handleLoad(child);
        } else if (child->instructionType == InstructionType::Br) {
            handleBr(child);
        } else if (child->instructionType == InstructionType::Ne) {
            handleNe(child);
        } else if (child->instructionType == InstructionType::Eq) {
            handleEq(child);
        } else if (child->instructionType == InstructionType::Gt) {
            handleGt(child);
        } else if (child->instructionType == InstructionType::Ge) {
            handleGe(child);
        } else if (child->instructionType == InstructionType::Lt) {
            handleLt(child);
        } else if (child->instructionType == InstructionType::Le) {
            handleLe(child);
        } else if (child->instructionType == InstructionType::Zext) {
            handleZext(child);
        } else if (child->instructionType == InstructionType::Ret) {
            handleRet(child);
        } else if (child->instructionType == InstructionType::Call) {
            handleCall(child);
        } else if (child->instructionType == InstructionType::GEP) {
            handleGEP(child);
        }
        if (!child->uses.empty() && child->uses[0]->user->valueType == ValueType::Instruction) {
            auto *ins = (Instruction *) child->uses[0]->user;
            if (ins->instructionType == InstructionType::Call && ins->operands[0]->value->getName() != "@putint"
                && ins->operands[0]->value->getName() != "@putch" && ins->operands[0]->value->getName() != "@getint") {
                this->mipsBuilder->genInstruction(new Annotation("# 把参数放入内存中"));
                this->value2offset[child] = this->curOffSet;
                Sw *sw = new Sw(findReg(child), this->curOffSet, 29);
                this->mipsBuilder->genInstruction(sw);
                removeReg(child);
                this->curOffSet -= 4;
                this->mipsBuilder->genInstruction(new Annotation("# ------\n"));
            }
        }
    }
}


void Handler::handleLoad(Instruction *child) {
    std::string glob;
    int offset = findOffset(child->operands[0]->value, &glob);
    if (offset <= 0) {
        bool isAllocated = false;
        int reg = allocaReg(child, &isAllocated);
        if (!isAllocated) {
            Lw *lw = new Lw(reg, offset, 29);
            if (!glob.empty()) {
                lw->glob = glob;
            }
            this->mipsBuilder->genInstruction(lw);
        } else {
            this->value2reg[child] = reg;
        }
    } else {
        // 不在内存中
        int reg = findReg(child->operands[0]->value);
        bool foo;
        Lw *lw = new Lw(allocaReg(child, &foo), 0, reg);
        removeReg(child->operands[0]->value);
        this->mipsBuilder->genInstruction(lw);
    }

}

void Handler::handleStore(Instruction *child) {
    Value *op0 = child->operands[0]->value;
    Value *op1 = child->operands[1]->value;
    int reg = -1;
    if (op0->valueType == ValueType::Instruction) {
        // 找这个寄存器
        reg = findReg(op0);
    } else if (op0->valueType == ValueType::Const) {
        // 生成li
        bool foo;
        reg = allocaReg(op0, &foo);
        Li *li = new Li(reg, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else if (op0->valueType == ValueType::Param) {
        // 针对于函数的参数 和常数的比较类似
        std::string glob;
        int offset = findOffset(op0, &glob);
        if (offset > 0) {
            std::cout << "形参没存到内存中" << std::endl;
        }
        bool foo;
        reg = allocaReg(op0, &foo);
        Lw *lw = new Lw(reg, offset, 29);
        this->mipsBuilder->genInstruction(lw);
    }
    std::string glob;
    int offset = findOffset(op1, &glob);
    if (offset <= 0) {
        // 已在内存中
        Sw *sw = new Sw(reg, offset, 29);
        if (!glob.empty()) {
            sw->glob = glob;
        }
        this->mipsBuilder->genInstruction(sw);
    } else {
        // 不在内存中
        int reg1 = findReg(op1);

        Sw *sw = new Sw(reg, 0, reg1);
        removeReg(op1);
        this->mipsBuilder->genInstruction(sw);

    }
    removeReg(op0);
}


void Handler::handleAdd(Instruction *child) {
    Value *op1 = child->operands[0]->value;
    Value *op2 = child->operands[1]->value;
    int reg1 = -1;
    int reg2 = -1;
    if (op1->valueType == ValueType::Instruction) {
        reg1 = findReg(op1);
    } else if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    }
    if (op2->valueType == ValueType::Instruction) {
        reg2 = findReg(op2);
    } else if (op2->valueType == ValueType::Const) {
        bool foo;
        reg2 = allocaReg(op2, &foo);
        Li *li = new Li(reg2, ((Const *) op2)->val);
        this->mipsBuilder->genInstruction(li);
    }

    removeReg(op1);
    removeReg(op2);

    bool foo;
    allocaReg(child, &foo);
    int reg0 = findReg(child);
    this->value2reg[child] = reg0;

    Add *add = new Add(reg0, reg1, reg2);

    this->mipsBuilder->genInstruction(add);
}

void Handler::handleSub(Instruction *child, int reg) {
    if (child->isMod) {
        this->value2reg[child] = reg;
        return;
    }
    Value *op1 = child->operands[0]->value;
    Value *op2 = child->operands[1]->value;
    int reg1 = -1;
    int reg2 = -1;
    if (op1->valueType == ValueType::Instruction) {
        reg1 = findReg(op1);
    } else if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    }
    if (op2->valueType == ValueType::Instruction) {
        reg2 = findReg(op2);
    } else if (op2->valueType == ValueType::Const) {
        bool foo;
        reg2 = allocaReg(op2, &foo);
        Li *li = new Li(reg2, ((Const *) op2)->val);
        this->mipsBuilder->genInstruction(li);
    }

    removeReg(op1);
    removeReg(op2);

    bool foo;
    allocaReg(child, &foo);
    int reg0 = findReg(child);
    this->value2reg[child] = reg0;

    Sub *sub = new Sub(reg0, reg1, reg2);

    this->mipsBuilder->genInstruction(sub);
}

void Handler::handleMul(Instruction *child) {
    if (child->isMod) {
        return;
    }
    Value *op1 = child->operands[0]->value;
    Value *op2 = child->operands[1]->value;
    int reg1 = -1;
    int reg2 = -1;
    if (op1->valueType == ValueType::Instruction) {
        reg1 = findReg(op1);
    } else if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    }
    if (op2->valueType == ValueType::Instruction) {
        reg2 = findReg(op2);
    } else if (op2->valueType == ValueType::Const) {
        bool foo;
        reg2 = allocaReg(op2, &foo);
        Li *li = new Li(reg2, ((Const *) op2)->val);
        this->mipsBuilder->genInstruction(li);
    }

    removeReg(op1);
    removeReg(op2);

    bool foo;
    allocaReg(child, &foo);
    int reg0 = findReg(child);
    this->value2reg[child] = reg0;

    Mult *mult = new Mult(reg1, reg2);

    this->mipsBuilder->genInstruction(mult);

    Mflo *mflo = new Mflo(reg0);

    this->mipsBuilder->genInstruction(mflo);

}

void Handler::handleDiv(Instruction *child, int *reg) {

    Value *op1 = child->operands[0]->value;
    Value *op2 = child->operands[1]->value;
    int reg1 = -1;
    int reg2 = -1;
    if (op1->valueType == ValueType::Instruction) {
        reg1 = findReg(op1);
    } else if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    }
    if (op2->valueType == ValueType::Instruction) {
        reg2 = findReg(op2);
    } else if (op2->valueType == ValueType::Const) {
        bool foo;
        reg2 = allocaReg(op2, &foo);
        Li *li = new Li(reg2, ((Const *) op2)->val);
        this->mipsBuilder->genInstruction(li);
    }

    removeReg(op1);
    removeReg(op2);

    bool foo;
    allocaReg(child, &foo);
    int reg0 = findReg(child);

    if (child->isMod) {
        *reg = reg0;
        Div *div = new Div(-1, reg1, reg2);
        this->mipsBuilder->genInstruction(div);
        Mfhi *mfhi = new Mfhi(reg0);
        this->mipsBuilder->genInstruction(mfhi);
    } else {
        this->value2reg[child] = reg0;
        Div *div = new Div(reg0, reg1, reg2);
        this->mipsBuilder->genInstruction(div);
    }


}

void Handler::removeReg(Value *value) {
    int reg = -1;
    for (auto &it:this->value2reg) {
        if (it.first->getName() == value->getName()) {
            reg = it.second;
            this->value2reg.erase(it.first);
            break;
        }
    }
    bool flag = false;
    for (auto &it1:this->value2reg) {
        if (it1.second == reg) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        this->regs[reg] = 0;
    }
}

void Handler::handleBr(Instruction *child) {
    if (child->operands.size() == 1) {
        J *j = new J(child->operands[0]->value->getName());
        this->mipsBuilder->genInstruction(j);
    } else if (child->operands.size() == 3) {
        auto *cond = child->operands[0]->value;

        auto *label1 = (child->operands[1]->pos == 1) ? child->operands[1]->value
                                                      : child->operands[2]->value;
        auto *label2 = (child->operands[2]->pos == 2) ? child->operands[2]->value
                                                      : child->operands[1]->value;

        Beq *beq = new Beq(findReg(cond), label2->getName());
        this->mipsBuilder->genInstruction(beq);
        J *j = new J(label1->getName());
        this->mipsBuilder->genInstruction(j);

        removeReg(cond);
    } else {
        std::cout << "跳转指令的参数有问题" << std::endl;
    }
}

void Handler::handleNe(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Sne *sne = new Sne(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(sne);
}

void Handler::handleLe(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Sle *sle = new Sle(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(sle);
}

void Handler::handleGe(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Sge *sge = new Sge(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(sge);
}

void Handler::handleGt(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Sgt *sgt = new Sgt(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(sgt);
}

void Handler::handleEq(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Seq *seq = new Seq(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(seq);
}

void Handler::handleLt(Instruction *child) {
    auto *op0 = child->operands[0]->value;
    auto *op1 = child->operands[1]->value;
    int reg0, reg1;
    if (op0->valueType == ValueType::Const) {
        bool foo;
        reg0 = allocaReg(op0, &foo);
        Li *li = new Li(reg0, ((Const *) op0)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg0 = findReg(op0);
    }
    if (op1->valueType == ValueType::Const) {
        bool foo;
        reg1 = allocaReg(op1, &foo);
        Li *li = new Li(reg1, ((Const *) op1)->val);
        this->mipsBuilder->genInstruction(li);
    } else {
        reg1 = findReg(op1);
    }

    removeReg(op0);
    removeReg(op1);

    bool foo;
    int reg = allocaReg(child, &foo);
    Slt *slt = new Slt(reg, reg0, reg1);

    this->mipsBuilder->genInstruction(slt);
}

void Handler::handleZext(Instruction *child) {
    int reg = findReg(child->operands[0]->value);
    removeReg(child->operands[0]->value);
    value2reg[child] = reg;
    this->regs[reg] = 1;
}

void Handler::handleRet(Instruction *child) {
    if (mipsBuilder->mipsModule->curMipsText->name == "main") {
        Li *li = new Li(2, 10);
        this->mipsBuilder->genInstruction(li);
        this->mipsBuilder->genInstruction(new Syscall());
        return;
    }
    if (!child->operands.empty()) {
        if (child->operands[0]->value->valueType == ValueType::Instruction) {
            Move *move = new Move(2, findReg(child->operands[0]->value));
            removeReg(child->operands[0]->value);
            this->mipsBuilder->genInstruction(move);
        } else if (child->operands[0]->value->valueType == ValueType::Const) {
            Li *li = new Li(2, atoi(child->operands[0]->value->getName().c_str()));
            this->mipsBuilder->genInstruction(li);
        }

    }
    Jr *jr = new Jr(31);
    this->mipsBuilder->genInstruction(jr);

}


void Handler::save() {
    saved = true;
    this->mipsBuilder->genInstruction(new Annotation("# 保存现场"));
    // 将寄存器里现在的值统统装入内存中
    oldSp = curOffSet;
    for (auto &it:value2reg) {
        this->value2offset[it.first] = this->curOffSet;
        Sw *sw = new Sw(it.second, this->curOffSet, 29);
        this->mipsBuilder->genInstruction(sw);
        this->curOffSet -= 4;
        std::cout << it.first->getName() << std::endl;
    }
//    value2reg.clear();
//    for (int i = 0; i < 32; ++i) {
//        regs[i] = 0;
//    }


    this->mipsBuilder->genInstruction(new Annotation("# 保存ra"));

    this->value2offset[nullptr] = curOffSet;
    Sw *sw = new Sw(31, curOffSet, 29);
    this->mipsBuilder->genInstruction(sw);
    this->curOffSet -= 4;

    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));


    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));

}

void Handler::handleCall(Instruction *child) {

    if (child->operands[0]->value->getName() == "@putint") {

        int reg = findReg(child->operands[1]->value);

        Move *move = new Move(4, reg);
        this->mipsBuilder->genInstruction(move);
        Li *li = new Li(2, 1);
        this->mipsBuilder->genInstruction(li);
        this->mipsBuilder->genInstruction(new Syscall());

        return;
    } else if (child->operands[0]->value->getName() == "@putch") {
        Li *li0 = new Li(4, atoi(child->operands[1]->value->getName().c_str()));
        this->mipsBuilder->genInstruction(li0);
        Li *li1 = new Li(2, 11);
        this->mipsBuilder->genInstruction(li1);
        this->mipsBuilder->genInstruction(new Syscall());

        return;

    } else if (child->operands[0]->value->getName() == "@getint") {


        Li *li = new Li(2, 5);
        this->mipsBuilder->genInstruction(li);
        this->mipsBuilder->genInstruction(new Syscall());
        bool foo;
        int reg = allocaReg(child, &foo);
        Move *move = new Move(reg, 2);
        this->mipsBuilder->genInstruction(move);
        return;
    }

    for (auto *use : child->operands) {
        auto *value = use->value;
        if (value->valueType == ValueType::Const) {
            this->mipsBuilder->genInstruction(new Annotation("# 把数字参数放入内存中"));

            bool foo;
            int reg = allocaReg(value, &foo);
            Li *li = new Li(reg, atoi(value->getName().c_str()));
            this->mipsBuilder->genInstruction(li);

            Sw *sw = new Sw(reg, this->curOffSet, 29);
            this->value2offset[value] = this->curOffSet;
            this->mipsBuilder->genInstruction(sw);

            removeReg(value);

            this->curOffSet -= 4;
            this->mipsBuilder->genInstruction(new Annotation("# ------\n"));
        }
    }

    this->mipsBuilder->genInstruction(new Annotation("# 移动sp"));
    Addiu *addiu = new Addiu(29, 29, curOffSet + 4);
    this->mipsBuilder->genInstruction(addiu);
    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));

    value2reg.clear();
    for (int i = 0; i < 32; ++i) {
        regs[i] = 0;
    }

    this->mipsBuilder->genInstruction(new Annotation("# 跳转到函数"));
    Jal *jal = new Jal(child->operands[0]->value->getName().substr(1, child->operands[0]->value->getName().size() - 1));
    this->mipsBuilder->genInstruction(jal);

    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));

    if (((Function *) child->operands[0]->value)->ret == 1) {
        //int
        this->mipsBuilder->genInstruction(new Annotation("# 得到函数的返回值"));

        bool foo;
        int reg = allocaReg(child, &foo);
        Move *move = new Move(reg, 2);
        mipsBuilder->genInstruction(move);
        this->mipsBuilder->genInstruction(new Annotation("# -----\n"));
    } else {
        //void
    }


    this->mipsBuilder->genInstruction(new Annotation("# 移回sp"));
    addiu = new Addiu(29, 29, -curOffSet - 4);
    std::cout << oldSp << std::endl;
    this->mipsBuilder->genInstruction(addiu);
    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));


    this->mipsBuilder->genInstruction(new Annotation("# 恢复现场"));
    for (auto &it:value2offset) {
        if (it.second <= oldSp && it.second > curOffSet + 4) {
            if (it.first == nullptr) {
                this->mipsBuilder->genInstruction(new Annotation("# 恢复ra"));
                int reg = 31;
                Lw *lw = new Lw(reg, it.second, 29);
                this->mipsBuilder->genInstruction(lw);
                this->mipsBuilder->genInstruction(new Annotation("# ------\n"));
            } else {
                bool foo;
                int reg = allocaReg(it.first, &foo);
                Lw *lw = new Lw(reg, it.second, 29);
                this->mipsBuilder->genInstruction(lw);
            }
            value2offset.erase(it.first);
        }
    }
    this->mipsBuilder->genInstruction(new Annotation("# ------\n"));

    saved = false;


}

void Handler::handleGEP(Instruction *child) {
    int temp = 0;
    for (int i = 1; i < child->operands.size(); ++i) {
        if (child->operands[i]->value->valueType == ValueType::Const) {
            if (((Instruction *) child->operands[0]->value)->dims.size() >= i) {
                temp += (atoi(child->operands[i]->value->getName().c_str()) << 2) *
                        ((Instruction *) child->operands[0]->value)->dims[i - 1];
            } else {
                temp += (atoi(child->operands[i]->value->getName().c_str()) << 2);
            }
        } else {

        }
    }
    if (((Instruction *) child->operands[0]->value)->instructionType == InstructionType::Alloca) {
        std::string name;
        int offset = findOffset(child->operands[0]->value, &name);
        if (offset <= 0) {
            // 在内存中
            temp = 0 - temp + offset;
        }
        bool foo;
        auto *value_foo = new Value("", ValueType::Const);
        int reg0 = allocaReg(value_foo, &foo);
        Li *li = new Li(reg0, temp);
        this->mipsBuilder->genInstruction(li);

        int reg1 = allocaReg(child, &foo);
        auto *add = new Add(reg1, reg0, 29);
        this->mipsBuilder->genInstruction(add);
        removeReg(value_foo);

    } else if (((Instruction *) child->operands[0]->value)->instructionType == InstructionType::Load) {
        // 在寄存器中

        int reg0 = findReg(child->operands[0]->value);
        bool foo;
        auto *value_foo = new Value("", ValueType::Const);
        // 寄存器里的偏移量减去temp
        int reg1 = allocaReg(value_foo, &foo);
        auto *addiu = new Addiu(reg1, reg0, -temp);
        this->mipsBuilder->genInstruction(addiu);
        removeReg(child->operands[0]->value);
        if (((Instruction *) child->operands[0]->value)->isPtr) {
            int reg2 = allocaReg(child, &foo);
            auto *move = new Move(reg2, reg1);
            this->mipsBuilder->genInstruction(move);
            removeReg(value_foo);
        } else {
            int reg2 = allocaReg(child, &foo);
            auto *add = new Add(reg2, reg1, 29);
            this->mipsBuilder->genInstruction(add);
            removeReg(value_foo);
        }
    } else if (child->operands[0]->value->valueType == ValueType::Global) {
        std::cout << "gep的操作对象为全局" << std::endl;
        auto *value_foo = new Value("", ValueType::Const);
        bool foo;
        int reg = allocaReg(value_foo, &foo);
        La *la = new La(reg, child->operands[0]->value->getName().substr(1,
                                                                         child->operands[0]->value->getName().size() -
                                                                         1));
        this->mipsBuilder->genInstruction(la);

        int reg2 = allocaReg(child, &foo);
        auto *addiu = new Addiu(reg2, reg, temp);
        this->mipsBuilder->genInstruction(addiu);
        removeReg(value_foo);

    }
    std::cout << "gep的偏移量是[" << temp << "]" << std::endl;
}






