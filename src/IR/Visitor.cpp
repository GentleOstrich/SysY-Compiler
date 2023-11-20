#include "Visitor.h"

void Visitor::handleCompUnit(Node *compUnit) {
    for (auto *child:compUnit->children) {
        if (child->nodeType == NodeType::Decl) {
            handleDecl(child, true);
        } else if (child->nodeType == NodeType::FuncDef) {
            handleFuncDef(child);
        } else if (child->nodeType == NodeType::MainFuncDef) {
            handleMainFuncDef(child);
        }
    }
    Module *module = buildFactory->genIRModule();
    module->output();

}

void Visitor::handleVarDef(Node *varDef, bool isGlobal) {
    if (isGlobal) {
        auto *globalVar = buildFactory->genGlobalVar(varDef, 0, false);
        auto *symbol = new Symbol(varDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        for (auto *child:varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                //返回具体数字
                globalVar->val = handleInitVal(child, nullptr);
            }
        }
    } else {
        auto *allocInstruction = buildFactory->genInstruction(varDef, InstructionType::Alloca, true);
        auto *symbol = new Symbol(varDef->getWord(), allocInstruction);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        symbolTable->symbolId--;
        for (auto *child:varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                Value *initValInstuction = nullptr;
                handleInitVal(child, &initValInstuction);

                auto *storeInstruction = buildFactory->genInstruction(varDef, InstructionType::Store, false);

                Use *use0 = new Use(initValInstuction, storeInstruction, 0);
                initValInstuction->addUse(use0);
                storeInstruction->addOperand(use0);

                Use *use1 = new Use(allocInstruction, storeInstruction, 1);
                initValInstuction->addUse(use1);
                storeInstruction->addOperand(use1);

            }
        }
        symbolTable->symbolId++;

    }
    // 对于变量的定义，要生成一个alloc类指令 varDef里是包含变量名字的
}

void Visitor::handleConstDef(Node *constDef, bool isGlobal) {
    // 需要加符号表了
    if (isGlobal) {
        auto *globalVar = buildFactory->genGlobalVar(constDef, 0, true);
        auto *symbol = new Symbol(constDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        for (auto *child:constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                //返回具体数字
                globalVar->val = handleConstInitVal(child, nullptr);
            }
        }
    } else {
        auto *allocInstruction = buildFactory->genInstruction(constDef, InstructionType::Alloca, true);
        auto *symbol = new Symbol(constDef->getWord(), allocInstruction);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        symbolTable->symbolId--;
        for (auto *child:constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                //返回具体数字
                Value *initValInstuction = nullptr;
                handleConstInitVal(child, &initValInstuction);

                auto *storeInstruction = buildFactory->genInstruction(constDef, InstructionType::Store, false);

                Use *use0 = new Use(initValInstuction, storeInstruction, 0);
                initValInstuction->addUse(use0);
                storeInstruction->addOperand(use0);

                Use *use1 = new Use(allocInstruction, storeInstruction, 1);
                initValInstuction->addUse(use1);
                storeInstruction->addOperand(use1);


            }
        }
        symbolTable->symbolId++;
    }


}

void Visitor::handleFuncDef(Node *funcDef) {
    // funcDef 里也有 func的 名字
    auto *function = buildFactory->genFunction(funcDef);
    // 生成函数指令
    auto *symbol = new Symbol(funcDef->getWord(), function);
    symbolTable->addSymbol(symbol, funcDef->getLineNum());
    for (auto *child : funcDef->children) {
        if (child->nodeType == NodeType::FuncType) {
            handleFuncType(child);
        } else if (child->nodeType == NodeType::FuncFParams) {
            symbolTable->createSymbolTable();
            function->cnt = handleFuncFParams(child);
            // 将function的参数个数交给function中
        } else if (child->nodeType == NodeType::Block) {
            handleBlock(child);
        }
    }
}

void Visitor::handleFuncFParam(Node *funcFParam) {

}

void Visitor::handleDecl(Node *Decl, bool isGlobal) {
    for (auto *child : Decl->children) {
        if (child->nodeType == NodeType::ConstDecl) {
            handleConstDecl(child, isGlobal);
        } else if (child->nodeType == NodeType::VarDecl) {
            handleVarDecl(child, isGlobal);
        }
    }
}

void Visitor::handleMainFuncDef(Node *mainFuncFParam) {
    buildFactory->genFunction(mainFuncFParam);
    for (auto *child : mainFuncFParam->children) {
        symbolTable->createSymbolTable();
        handleBlock(child);
    }
}

void Visitor::handleConstDecl(Node *constDecl, bool isGlobal) {
    for (auto *child : constDecl->children) {
        if (child->nodeType == NodeType::BType) {
            handleBType(child);
        } else if (child->nodeType == NodeType::ConstDef) {
            handleConstDef(child, isGlobal);
        }
    }
}

void Visitor::handleVarDecl(Node *varDecl, bool isGlobal) {
    for (auto *child : varDecl->children) {
        if (child->nodeType == NodeType::BType) {
            handleBType(child);
        } else if (child->nodeType == NodeType::VarDef) {
            handleVarDef(child, isGlobal);
        }
    }
}

void Visitor::handleBType(Node *BType) {

}

int Visitor::handleConstInitVal(Node *constInitVal, Value **constInitInstruction) {
    for (auto *child:constInitVal->children) {
        if (child->nodeType == NodeType::ConstInitVal) {
            return handleConstInitVal(child, constInitInstruction);
        } else if (child->nodeType == NodeType::ConstExp) {
            return handleConstExp(child, constInitInstruction);
            // 返回具体数字
        }
    }
    return -114514;
}

int Visitor::handleInitVal(Node *initVal, Value **iniValInstruction) {
    for (auto *child:initVal->children) {
        if (child->nodeType == NodeType::InitVal) {
            return handleInitVal(child, iniValInstruction);
        } else if (child->nodeType == NodeType::Exp) {
            return handleExp(child, iniValInstruction);
            // 返回具体数字 nullptr 要具体数字 否则 要指令
        }
    }
    return -114514;
}

int Visitor::handleFuncFParams(Node *funcFParams) {
    // 返回形参个数
    int ret = 0;
    for (auto *child : funcFParams->children) {
        if (child->nodeType == NodeType::FuncFParam) {
            handleFuncFParam(child);
            ret++;
        }
    }
    return ret;
}

void Visitor::handleFuncType(Node *funcType) {

}

void Visitor::handleBlock(Node *block) {
    for (auto *child : block->children) {
        handleBlockItem(child);
    }
    symbolTable->deleteSymbolTable();
}

void Visitor::handleBlockItem(Node *blockItem) {
    for (auto *child : blockItem->children) {
        if (child->nodeType == NodeType::Decl) {
            handleDecl(child, false);
        } else {
            handleStmt(child);
        }
    }

}

void Visitor::handleStmt(Node *stmt) {
    if (stmt->getType() == 5) {
        // 是return语句
        Value *expInstruction = nullptr;
        for (auto *child : stmt->children) {
            // 只可能是exp
            handleExp(child, &expInstruction);
            // 需要得到装着返回值的寄存器号 那是一个 Instruction
        }
        Instruction *instruction = buildFactory->genInstruction(stmt, InstructionType::Ret, false);
        auto *use = new Use(expInstruction, instruction, 0);
        if (expInstruction != nullptr) {
            expInstruction->addUse(use); // 被使用者
            instruction->addOperand(use); // 使用者
        }
        // ret 语句中只会用到一个其他的寄存器号
        // ret 语句不需要加入符号表
        // 返回一个值 或 void 这个值来自于 handleExp
    } else if (stmt->getType() == 0) {
        if (stmt->children[0]->getNodeType() == NodeType::Block) {
            symbolTable->createSymbolTable();
            handleBlock(stmt->children[0]);
        }
    }
}

void Visitor::handleForStmt(Node *forStmt) {

}

int Visitor::handleExp(Node *exp, Value **expInstruction) {
    // 待施工 无需产生指令
    if (expInstruction == nullptr) {
        return handleAddExp(exp->children[0], nullptr);
    }
    Value *addInstruction = nullptr;
    for (auto *child:exp->children) {
        if (child->nodeType == NodeType::AddExp) {
            handleAddExp(child, &addInstruction);
        }
    }
    *expInstruction = addInstruction;
    return -114514;
}

void Visitor::handleCond(Node *cond) {

}

int Visitor::handleLVal(Node *lVal, Value **lValInstucrion) {
    string word = lVal->getWord();
    Symbol *symbol = symbolTable->getSymbol(word, false, true); // 找这个数先不用考虑函数
    if (symbol->value->valueType == ValueType::Global) {
        if (lValInstucrion) {
            Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
            Use *use = new Use(symbol->value, loadInstruction, 0);
            symbol->value->addUse(use);
            loadInstruction->addOperand(use);
            *lValInstucrion = loadInstruction;
        }
        return ((GlobalVar *) symbol->value)->val;
    } else if (symbol->value->valueType == ValueType::Instruction) {
        Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
        Use *use = new Use(symbol->value, loadInstruction, 0);
        symbol->value->addUse(use);
        loadInstruction->addOperand(use);
        *lValInstucrion = loadInstruction;
        // 找到专门的alloc指令
        // 等一下还要向其他的一样传入Value的形参
    }
    return -114514;
}

int Visitor::handlePrimaryExp(Node *primaryExp, Value **primaryInstruction) {
    // 要生成指令了
    if (primaryInstruction == nullptr) { // 就想要这个数
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            return handleExp(primaryExp->children[0], nullptr);
        } else if (primaryExp->children[0]->nodeType == NodeType::LVal) {
            return handleLVal(primaryExp->children[0], nullptr); // 寻找值的倒数第二个终结点
        } else if (primaryExp->children[0]->nodeType == NodeType::Number) {
            // 例如 return 0 应该直接返回0这个值
            return primaryExp->children[0]->getVal(); // 寻找值的终结点
        }
    } else {
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            Value *expInstruction = nullptr;
            handleExp(primaryExp->children[0], &expInstruction);
            *primaryInstruction = expInstruction;
        } else if (primaryExp->children[0]->nodeType == NodeType::LVal) {
            Value *lValInstruction = nullptr;
            handleLVal(primaryExp->children[0], &lValInstruction);
            *primaryInstruction = lValInstruction;
        } else if (primaryExp->children[0]->nodeType == NodeType::Number) {
            // 例如 return 0 应该直接返回0这个值
            int a = primaryExp->children[0]->getVal();
            *primaryInstruction = buildFactory->genConst(primaryExp, a);
        }
    }
    return -114514;
}

void Visitor::handleNumber(Node *number) {

}

int Visitor::handleUnaryExp(Node *unaryExp, Value **unaryInstruction) {
    // 无需产生指令
    if (unaryInstruction == nullptr) { // 就想要这个数
        if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
            return handlePrimaryExp(unaryExp->children[0], nullptr);
        } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
            int sign = 1;
            if (handleUnaryOp(unaryExp->children[0])) {
                sign *= -1;
            }
            return sign * handleUnaryExp(unaryExp->children[1], nullptr);

        }
    }

    if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
        Value *primaryInstruction = nullptr;
        handlePrimaryExp(unaryExp->children[0], &primaryInstruction);
        *unaryInstruction = primaryInstruction;
    } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
        if (handleUnaryOp(unaryExp->children[0])) {
            auto *c = new Const("", ValueType::Const, 0);

            Value *right;
            handleUnaryExp(unaryExp->children[1], &right);

            Instruction *subInstruction = buildFactory->genInstruction(unaryExp, InstructionType::Sub, true);

            Use *use0 = new Use(c, subInstruction, 0);
            subInstruction->addOperand(use0);
            c->addUse(use0);

            Use *use1 = new Use(right, subInstruction, 1);
            subInstruction->addOperand(use1);
            right->addUse(use1);

            *unaryInstruction = subInstruction;
        } else {
            handleUnaryExp(unaryExp->children[1], unaryInstruction);
        }
    } else {
        // Ident ()  调用函数
    }
    return -114514;
}


int Visitor::handleUnaryOp(Node *unaryOp) {
    return unaryOp->getType();
}

void Visitor::handleFuncRParams(Node *funcRParams) {

}

int Visitor::handleMulExp(Node *mulExp, Value **mulInstruction) {
    if (mulInstruction == nullptr) {
        int a1, a2;
        if (mulExp->children.size() == 1) {
            a1 = handleUnaryExp(mulExp->children[0], nullptr);
            a2 = 1;
            return a1;
        } else {
            a1 = handleMulExp(mulExp->children[0], nullptr);
            a2 = handleUnaryExp(mulExp->children[1], nullptr);
            return (mulExp->getOp() == 0) ? a1 * a2 :
                   (mulExp->getOp() == 1) ? a1 / a2 : a1 % a2;
        }
    }
    if (mulExp->children.size() == 1) {
        Value *unaryInstruction = nullptr;
        //先不产生mul指令
        handleUnaryExp(mulExp->children[0], &unaryInstruction);
        *mulInstruction = unaryInstruction;
    } else if (mulExp->children.size() > 1) {
        //要产生mul指令了
        Value *leftMulInstruction = nullptr;
        Value *rightUnaryInstruction = nullptr;
        handleMulExp(mulExp->children[0], &leftMulInstruction);
        handleUnaryExp(mulExp->children[1], &rightUnaryInstruction);

        InstructionType instructionType = (mulExp->getOp() == 0) ? InstructionType::Mul :
                                          (mulExp->getOp() == 1) ? InstructionType::Div :
                                          InstructionType::Mod;

        *mulInstruction = buildFactory->genInstruction(mulExp, instructionType, true);
        auto *use0 = new Use(leftMulInstruction, (User *) *mulInstruction, 0);//第一个数
        auto *use1 = new Use(rightUnaryInstruction, (User *) *mulInstruction, 1);

        leftMulInstruction->addUse(use0);
        ((Instruction *) (*mulInstruction))->addOperand(use0);
        rightUnaryInstruction->addUse(use1);
        ((Instruction *) (*mulInstruction))->addOperand(use1);

    }
    return -114514;
}

int Visitor::handleAddExp(Node *addExp, Value **addInstruction) {
    if (addInstruction == nullptr) {
        int a1, a2;
        if (addExp->children.size() == 1) {
            a1 = handleMulExp(addExp->children[0], nullptr);
            a2 = 0;
            return a1;
        } else {
            a1 = handleAddExp(addExp->children[0], nullptr);
            a2 = handleMulExp(addExp->children[1], nullptr);
            return (addExp->getOp() == 1) ? (a1 - a2) : (a1 + a2);
        }
    }
    if (addExp->children.size() == 1) {
        Value *mulInstruction = nullptr;
        //先不产生add指令
        handleMulExp(addExp->children[0], &mulInstruction);
        *addInstruction = mulInstruction;
    } else if (addExp->children.size() > 1) {
        //要产生add指令了
        Value *leftAddInstruction = nullptr;
        Value *rightMulInstruction = nullptr;
        handleAddExp(addExp->children[0], &leftAddInstruction);
        handleMulExp(addExp->children[1], &rightMulInstruction);

        InstructionType instructionType = (addExp->getOp() == 0) ? InstructionType::Add : InstructionType::Sub;

        *addInstruction = buildFactory->genInstruction(addExp, instructionType, true);
        auto *use0 = new Use(leftAddInstruction, (User *) addInstruction, 0);//第一个数
        auto *use1 = new Use(rightMulInstruction, (User *) addInstruction, 1);

        leftAddInstruction->addUse(use0);
        ((Instruction *) (*addInstruction))->addOperand(use0);

        rightMulInstruction->addUse(use1);
        ((Instruction *) (*addInstruction))->addOperand(use1);
    }
    return -114514;
}

void Visitor::handleRelExp(Node *relExp) {

}

void Visitor::handleEqExp(Node *eqExp) {

}

void Visitor::handleLAndExp(Node *lAndExp) {

}

void Visitor::handleLOrExp(Node *lOrExp) {

}

int Visitor::handleConstExp(Node *constExp, Value **constExpInstruction) {
    for (auto *child:constExp->children) {
        return handleAddExp(child, constExpInstruction);
        //就是想要这个数 是传入空指针
    }
    return -114514;
}

Visitor::Visitor() {
    this->buildFactory = new BuildFactory();
    this->symbolTable = new SymbolTable();
}


