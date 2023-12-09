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
    if (instructionType == InstructionType::Alloca || instructionType == InstructionType::GEP) {
        this->isPtr = true;
    }
}

void Instruction::translate() {
    std::string code = "    ";
    if (instructionType == InstructionType::Ret) {
        code += "ret ";
        if (operands.empty()) {
            code += "void";
        } else {
            for (auto *child: operands) {
                Value *value = child->value;
                code += "i" + std::to_string(value->ty) + " " + value->getName() + " "; // 只能返回i32所以无需考虑返回的类型
            }
        }
    } else if (instructionType == InstructionType::Add) {
        code += this->getName() + " = add " + "i" + std::to_string(this->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Sub) {
        code += this->getName() + " = sub " + "i" + std::to_string(this->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Mul) {
        code += this->getName() + " = mul " + "i" + std::to_string(this->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Div) {
        code += this->getName() + " = sdiv " + "i" + std::to_string(this->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } // mod 生成三个指令 先除 再乘 再减
    else if (instructionType == InstructionType::Eq) {
        code += this->getName() + " = icmp eq " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Ne) {
        code += this->getName() + " = icmp ne " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Lt) {
        code += this->getName() + " = icmp slt " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Le) {
        code += this->getName() + " = icmp sle " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Gt) {
        code += this->getName() + " = icmp sgt " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Ge) {
        code += this->getName() + " = icmp sge " + "i" + std::to_string(this->operands[0]->value->ty) + " ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    } else if (instructionType == InstructionType::Alloca) {
        code += this->getName() + " = alloca " + getContent(); // 每个alloca实际上都是指针，这里输出装的是什么
    } else if (instructionType == InstructionType::Store) {
        code += "store ";
        code += operands[0]->value->getType() + " " + operands[0]->value->getName() + ", ";
        code += operands[1]->value->getType() + " " + this->operands[1]->value->getName();
    } else if (instructionType == InstructionType::Load) {
        code += this->getName() + " = load ";
        for (auto *child: operands) {
            Value *value = child->value;
            code += value->getContent() + ", " + value->getType() + " " +
                    value->getName(); // 只会从指针里load，所以前一个是指针里装的是什么，后一个是指针的类型（装的是什么 + *）
        }
    } else if (instructionType == InstructionType::Call) {
        std::string ret;
        if (((Function *) (this->operands[0]->value))->ret == 0) ret = "void";
        else ret = "i32";
        if ((this->name) == std::to_string(-1)) {
            // 直接 call
            code += "call " + ret + " " + this->operands[0]->value->getName() + "(";
            // 函数的ty要么是 i32 要么是 void
            for (int i = 1; i < this->operands.size(); ++i) {
                code += this->operands[i]->value->getType() + " " + this->operands[i]->value->getName();
                code += ", ";
            }
            if (this->operands.size() > 1) code = code.substr(0, code.size() - 2);
            code += ")";
        } else {
            code += this->getName() + " = " + "call " + ret + " " + this->operands[0]->value->getName() + "(";
            for (int i = 1; i < this->operands.size(); ++i) {
                code += this->operands[i]->value->getType() + " " + this->operands[i]->value->getName();
                code += ", ";
            }
            if (this->operands.size() > 1) { code = code.substr(0, code.size() - 2); }
            code += ")";
        }
    } else if (instructionType == InstructionType::Br) {
        if (this->operands.size() == 1) {
            // 直接跳
            code += "br label " + this->operands[0]->value->getName();
        } else {
            // 条件跳
            std::string label1 = (this->operands[1]->pos == 1) ? this->operands[1]->value->getName()
                                                               : this->operands[2]->value->getName();
            std::string label2 = (this->operands[2]->pos == 2) ? this->operands[2]->value->getName()
                                                               : this->operands[1]->value->getName();
            code += "br i" + std::to_string(this->operands[0]->value->ty) + " " +
                    this->operands[0]->value->getName() +
                    ", label " + label1 + ", label " + label2;
        }
    } else if (instructionType == InstructionType::Zext) {
        code += this->getName() + " = zext i1 " + this->operands[0]->value->getName() + " to i32";
    } else if (instructionType == InstructionType::GEP) {
        code += this->getName() + " = getelementptr " +
                this->operands[0]->value->getContent() + ", " +
                this->operands[0]->value->getType() + " " + this->operands[0]->value->getName() + ", ";
        for (int i = 1; i < this->operands.size(); ++i) {
            code += operands[i]->value->getType() + " " + operands[i]->value->getName() + ", ";
        }
        code = code.substr(0, code.size() - 2);
    }
    c_ofs << code << std::endl;
}

std::string Instruction::getName() {
    return "%" + this->name;
}

void Instruction::addDim(int dim) {
    this->dims.push_back(dim);
}

std::string Instruction::getType() {
    std::string code = getContent();
//    for (auto dim: dims) {
//        if (dim > 0)
//            code += "[" + std::to_string(dim) + " x ";
//    }
//    code += "i" + std::to_string(ty);
//    for (int dim: dims) {
//        if (dim > 0)
//            code += "]";
//    }
//    for (auto dim: dims) {
//        if (dim == 0) {
//            code += "*";
//        }
//    }
    if (isPtr) {
        code += "*";
    }
    return code;
}

std::string Instruction::getContent() {
    std::string code;
    if (dims.empty()) {
        code += "i" + std::to_string(ty);
    } else {
        for (auto dim: dims) {
            if (dim > 0)
                code += "[" + std::to_string(dim) + " x ";
        }
        code += "i" + std::to_string(ty);
        for (int dim: dims) {
            if (dim > 0)
                code += "]";
        }
        for (auto dim: dims) {
            if (dim == 0) {
                code += "*";
            }
        }
    }
    return code;
}


