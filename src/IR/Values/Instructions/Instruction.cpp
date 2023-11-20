//
// Created by lyh on 11/19/2023.
//

#include "Instruction.h"
#include "../Const.h"
#include <iostream>
#include <fstream>

extern std::ofstream c_ofs;

Instruction::Instruction(const std::string &name, ValueType valueType, BasicBlock *basicBlock,
                         InstructionType instructionType) : User(name, valueType), basicBlock(basicBlock),
                                                            instructionType(instructionType) {}

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
        code += this->getName() + " = add ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + " ";
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Sub) {
        code += this->getName() + " = sub ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + " ";
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Mul) {
        code += this->getName() + " = mul ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + " ";
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Div) {
        code += this->getName() + " = div ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += value->getName() + " ";
        }
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Alloca) {
        code += this->getName() + " = alloc ";
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Store) {
        code += "store <type> ";
        code += this->operands[0]->value->getName() + ", ";
        code += "<type>* " + this->operands[1]->value->getName();
        c_ofs << code << std::endl;
    } else if (instructionType == InstructionType::Load) {
        code += this->getName() + " = load <type>, ";
        for (auto *child : operands) {
            Value *value = child->value;
            code += "<type>* " + value->getName();
        }
        c_ofs << code << std::endl;
    }
}

std::string Instruction::getName() {
    return "%" + this->name;
}
