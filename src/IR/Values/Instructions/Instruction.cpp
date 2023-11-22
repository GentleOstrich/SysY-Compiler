//
// Created by lyh on 11/19/2023.
//

#include "Instruction.h"
#include "../Const.h"
#include "../Function.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

Instruction::Instruction(const std::string &name, ValueType valueType, BasicBlock *basicBlock,
                         InstructionType instructionType) : User(name, valueType), basicBlock(basicBlock),
                                                            instructionType(instructionType) {
    if (instructionType == InstructionType::Le || instructionType == InstructionType::Lt ||
        instructionType == InstructionType::Ge | instructionType == InstructionType::Ne ||
        instructionType == InstructionType::Gt || instructionType == InstructionType::Eq) {
        this->ty = 1;
    }
}

void Instruction::translate() {
    std::string code = "    ";
    if (instructionType == InstructionType::Ret) {
        code += "ret ";
        if (operands.empty()) {
            code += "void";
        } else {
            for (auto *child : operands) {
                Value *value = child->value;
                code += value->getName() + " ";
            }
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Add) {
        code += this->getName() + " = add " + "i" + std::to_string(this->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Sub) {
        code += this->getName() + " = sub " + "i" + std::to_string(this->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Mul) {
        code += this->getName() + " = mul " + "i" + std::to_string(this->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Div) {
        code += this->getName() + " = div " + "i" + std::to_string(this->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } // 还缺一个mod
    else if (instructionType == InstructionType::Eq) {
        code += this->getName() + " = icmp eq " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Ne) {
        code += this->getName() + " = icmp ne " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Lt) {
        code += this->getName() + " = icmp slt " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Le) {
        code += this->getName() + " = icmp sle " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Gt) {
        code += this->getName() + " = icmp sgt " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Ge) {
        code += this->getName() + " = icmp sge " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        c_ofs << code.substr(0, code.size() - 2) << std::endl;
    } else if (instructionType == InstructionType::Alloca) {
        code += this->getName() + " = alloc " + "i" + std::to_string(this->ty);
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Store) {
        code += "store i" + std::to_string(this->ty) + " ";
        code += this->operands[0]->value->getName() + ", ";
        code += std::to_string(this->ty) + "* " + this->operands[1]->value->getName();
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Load) {
        code += this->getName() + " = load " + "i" + std::to_string(this->ty) + ", ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += "i" + std::to_string(this->ty) + "* " + value->getName();
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Call) {
        std::string ret;
        if (((Function *) (this->operands[0]->value))->ret == 0) ret = "void";
        else ret = "i32";
        if ((this->name) == std::to_string(-1)) {
            // 直接 call
            code += "call " + ret + " " + this->operands[0]->value->getName() + "(";
            // 函数的ty要么是 i32 要么是 void
            for (int i = 1; i < this->operands.size(); ++i) {
                code += "i" + std::to_string(this->operands[i]->value->ty) + " " + this->operands[i]->value->getName();
                code += ", ";
            }
            if (this->operands.size() > 1) { code = code.substr(0, code.size() - 2); }
            code += ")";
        } else {
            code += this->getName() + " = " + "call " + ret + " " + this->operands[0]->value->getName() + "(";
            for (int i = 1; i < this->operands.size(); ++i) {
                code += "i" + std::to_string(this->operands[i]->value->ty) + " " + this->operands[i]->value->getName();
                code += ", ";
            }
            if (this->operands.size() > 1) { code = code.substr(0, code.size() - 2); }
            code += ")";
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Br) {
        // 待施工
        if (this->operands.size() == 1) {
            code += "br label " + this->operands[0]->value->getName();
        } else {
            std::string label1 = (this->operands[1]->pos == 1) ? this->operands[1]->value->getName()
                                                               : this->operands[2]->value->getName();
            std::string label2 = (this->operands[2]->pos == 2) ? this->operands[2]->value->getName()
                                                               : this->operands[1]->value->getName();

            code += "br i" + std::to_string(this->operands[0]->value->ty) + " " +
                    this->operands[0]->value->getName() +
                    " label " + label1 + " label " + label2;
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Zext) {
        code += this->getName() + " = zext i1 " + this->operands[0]->value->getName() + " to i32";
        c_ofs << code << std::endl;
    }
}

std::string Instruction::getName() {
    return "%" + this->name;
}
