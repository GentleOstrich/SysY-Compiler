#include "Visitor.h"

#define use(a, b, pos)      \
  use = new Use(a, b, pos); \
  a->addUse(use);           \
  b->addOperand(use)

#define ERROR_CHECK

#ifdef ERROR_CHECK

struct Error {
    int line;
    char c;
};
extern Error errors[1000];
extern int e;

#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}

#endif

Use *use = nullptr;

void Visitor::visitCompUnit(Node *compUnit) {
    for (auto *child : compUnit->children) {
        if (child->nodeType == NodeType::Decl) {
            visitDecl(child, true);
        } else if (child->nodeType == NodeType::FuncDef) {
            visitFuncDef(child);
        } else if (child->nodeType == NodeType::MainFuncDef) {
            visitMainFuncDef(child);
        }
    }
    Module *module = buildFactory->genIRModule();
    module->translate();
}

void Visitor::visitVarDef(Node *varDef, bool isGlobal) {
    if (isGlobal) {
        // 全局变量 数 数组
        auto *globalVar = buildFactory->genGlobalVar(varDef, false);  // 不是const
        auto *symbol = new Symbol(varDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        for (auto *child : varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                std::vector<Value *> initVals;
                // 返回具体数字 isGlobal?
                visitInitVal(child, &initVals,
                             isGlobal);  // TODO 全局变量的初始值一定能算出来---数
                for (int i = 0; i < initVals.size(); ++i) {
                    use(initVals[i], globalVar, i);
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 数组:各维的长度
                Value *Const = nullptr;
                visitConstExp(child, &Const, isGlobal);  // TODO 一定是个数字
                globalVar->addDim(atoi(Const->getName().c_str()));
            }
        }
    } else {
        auto *allocIns =
                buildFactory->genInstruction(InstructionType::Alloca, true);
        auto *symbol = new Symbol(varDef->getWord(), allocIns);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        symbolTable->symbolId--;
        for (auto *child : varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                std::vector<Value *> initVals;
                visitInitVal(child, &initVals,
                             isGlobal);  // TODO 这里的初始值可能不是直接的数
                int i = 0;
                for (auto initVal : initVals) {
                    if (allocIns->dims.empty()) {
                        // 不是数组 不需要GEP
                        auto *storeIns =
                                buildFactory->genInstruction(InstructionType::Store, false);
                        use(initVal, storeIns, 0);
                        use(allocIns, storeIns, 1);
                    } else {
                        // 是数组 需要GEP
                        auto *GEPIns =
                                buildFactory->genInstruction(InstructionType::GEP, true);

                        use(allocIns, GEPIns, 0);
                        auto *Const = buildFactory->genConst(0);
                        use(Const, GEPIns, 1);  // 此处第一个移动数都是0 （整体不移动）

                        // 初始值一个一个放入数组中
                        if (allocIns->dims.size() == 1) {
                            // 一维数组两个偏移
                            Const = buildFactory->genConst(i);
                            use(Const, GEPIns, 2);
                        } else if (allocIns->dims.size() == 2) {
                            // 二维数组三个偏移
                            Const = buildFactory->genConst(i / allocIns->dims[1]);
                            use(Const, GEPIns, 2);
                            Const = buildFactory->genConst(i % allocIns->dims[1]);
                            use(Const, GEPIns, 3);
                        }
                        auto *storeIns =
                                buildFactory->genInstruction(InstructionType::Store, false);
                        use(initVal, storeIns, 0);
                        use(GEPIns, storeIns, 1);
                    }
                    i++;
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 数组:各维的长度
                Value *Const = nullptr;
                visitConstExp(child, &Const, true);  // TODO  一定是个数字吗？
                // 设定alloca的维度
                allocIns->addDim(atoi(Const->getName().c_str()));
            }
        }
        symbolTable->symbolId++;
    }
    // 对于变量的定义，要生成一个alloc类指令 varDef里是包含变量名字的
}

void Visitor::visitConstDef(Node *constDef, bool isGlobal) {
    // TODO
    //  数组相关
    //  需要加符号表了
    if (isGlobal) {
        auto *globalVar = buildFactory->genGlobalVar(constDef, true);  // 是const
        auto *symbol = new Symbol(constDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        for (auto *child : constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                std::vector<Value *> initVals;
                visitConstInitVal(child, &initVals,
                                  isGlobal);  // TODO 全局变量的初始值一定能算出来---数
                for (int i = 0; i < initVals.size(); ++i) {
                    use(initVals[i], globalVar, i);
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 数组:各维的长度
                Value *Const = nullptr;
                visitConstExp(child, &Const, isGlobal);  // TODO 一定是个数字
                globalVar->addDim(atoi(Const->getName().c_str()));
            }
        }
    } else {
        auto *allocIns =
                buildFactory->genInstruction(InstructionType::Alloca, true);
        auto *symbol = new Symbol(constDef->getWord(), allocIns);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        symbolTable->symbolId--;

        for (auto *child : constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                std::vector<Value *> initVals;
                visitConstInitVal(child, &initVals,
                                  isGlobal);  // TODO 这里的初始值可能不是直接的数
                int i = 0;
                for (auto initVal : initVals) {
                    if (allocIns->dims.size() < 1) {
                        // 不是数组 不需要GEP
                        auto *storeInstruction =
                                buildFactory->genInstruction(InstructionType::Store, false);
                        use(initVal, storeInstruction, 0);
                        use(allocIns, storeInstruction, 1);
                    } else {
                        // 是数组 需要GEP
                        auto *GEPIns =
                                buildFactory->genInstruction(InstructionType::GEP, true);

                        use(allocIns, GEPIns, 0);
                        auto *Const = buildFactory->genConst(0);
                        use(Const, GEPIns, 1);  // 此处第一个移动数都是0 （整体不移动）

                        if (allocIns->dims.size() == 1) {
                            Const = buildFactory->genConst(i);
                            use(Const, GEPIns, 2);
                        } else if (allocIns->dims.size() == 2) {
                            Const = buildFactory->genConst(i / allocIns->dims[1]);
                            use(Const, GEPIns, 2);
                            Const = buildFactory->genConst(i % allocIns->dims[1]);
                            use(Const, GEPIns, 3);
                        }
                        auto *storeIns =
                                buildFactory->genInstruction(InstructionType::Store, false);
                        use(initVal, storeIns, 0);
                        use(GEPIns, storeIns, 1);
                    }
                    i++;
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 各维的长度
                Value *Const = nullptr;
                visitConstExp(child, &Const, true);  // TODO  一定是个数字吗？
                // 设定alloca的维度
                allocIns->addDim(atoi(Const->getName().c_str()));
            }
        }
        symbolTable->symbolId++;
    }
}

void Visitor::visitFuncDef(Node *funcDef) {
    // funcDef里有func的名字
    auto *function = buildFactory->genFunction(funcDef);
    // 生成函数指令
    auto *symbol = new Symbol(funcDef->getWord(), function);
    symbolTable->addSymbol(symbol, funcDef->getLineNum());

    function->ret = visitFuncType(funcDef->children[0]);
    symbolTable->createSymbolTable();

    for (int i = 1; i < funcDef->children.size(); ++i) {
        if (funcDef->children[i]->getNodeType() == NodeType::FuncFParams) {
            function->cnt = visitFuncFParams(funcDef->children[i]);
        } else if (funcDef->children[i]->getNodeType() == NodeType::Block) {
            // 没有参数时，此时的基本块就是nullptr
            if (buildFactory->curBasicBlock == nullptr) {
                buildFactory->genBasicBlock();
            }
            visitBlock(funcDef->children[i]);
        }
    }
}

int Visitor::visitFuncFParams(Node *funcFParams) {
    // 返回形参个数
    int ret = 0;
    vector<Value *> params;
    for (auto *child : funcFParams->children) {
        if (child->nodeType == NodeType::FuncFParam) {
            // 这里是形参，要添加形参转换实参的alloca和store
            Value *param = nullptr;
            visitFuncFParam(child, &param);
            params.push_back(param);
            ret++;
        }
    }
    buildFactory->genBasicBlock();
    vector<Value *> allocas;

    // 把参数都先存起来
    // 分配 alloca
    for (int i = 0; i < params.size(); ++i) {
        Instruction *allocaIns =
                buildFactory->genInstruction(InstructionType::Alloca, true);
        auto *symbol = new Symbol(funcFParams->children[i]->getWord(), allocaIns);
        symbolTable->addSymbol(symbol, funcFParams->getLineNum());
        allocas.push_back(allocaIns);
    }
    // 存储 store
    for (int i = 0; i < params.size(); ++i) {
        Instruction *storeIns =
                buildFactory->genInstruction(InstructionType::Store, false);
        use(params[i], storeIns, 0);
        use(allocas[i], storeIns, 1);
        // TODO 设定alloc的维度 指针
        for (auto dim : ((Param *) params[i])->dims) {
            ((Instruction *) allocas[i])->addDim(dim);
        }
    }
    return ret;
}

void Visitor::visitFuncFParam(Node *funcFParam, Value **param) {
    auto *param1 = buildFactory->genParam();
    if (funcFParam->getType() > 0) {
        param1->addDim(0);
    }
    for (auto *child : funcFParam->children) {
        if (child->getNodeType() == NodeType::BType) {
            visitBType(child);
        } else if (child->getNodeType() == NodeType::ConstExp) {
            Value *Const = nullptr;
            visitConstExp(child, &Const, true);  // TODO 一定能算出来的具体数

            param1->addDim(atoi(Const->getName().c_str()));
        }
    }
    *param = param1;
}

void Visitor::visitDecl(Node *funcFParam, bool isGlobal) {
    for (auto *child : funcFParam->children) {
        if (child->nodeType == NodeType::ConstDecl) {
            visitConstDecl(child, isGlobal);
        } else if (child->nodeType == NodeType::VarDecl) {
            visitVarDecl(child, isGlobal);
        }
    }
}

void Visitor::visitMainFuncDef(Node *mainFuncFParam) {
    auto *f = buildFactory->genFunction(mainFuncFParam);
    f->ret = 1;
    for (auto *child : mainFuncFParam->children) {
        symbolTable->createSymbolTable();
        buildFactory->genBasicBlock();
        visitBlock(child);
    }
}

void Visitor::visitConstDecl(Node *constDecl, bool isGlobal) {
    for (auto *child : constDecl->children) {
        if (child->nodeType == NodeType::BType) {
            visitBType(child);
        } else if (child->nodeType == NodeType::ConstDef) {
            visitConstDef(child, isGlobal);
        }
    }
}

void Visitor::visitVarDecl(Node *varDecl, bool isGlobal) {
    for (auto *child : varDecl->children) {
        if (child->nodeType == NodeType::BType) {
            visitBType(child);
        } else if (child->nodeType == NodeType::VarDef) {
            visitVarDef(child, isGlobal);
        }
    }
}

void Visitor::visitBType(Node *BType) {}

int Visitor::visitConstInitVal(Node *constInitVal,
                               std::vector<Value *> *constInitVals,
                               bool needNum) {
    for (auto *child : constInitVal->children) {
        if (child->nodeType == NodeType::ConstInitVal) {
            visitConstInitVal(child, constInitVals,
                              needNum);  // TODO isGlobal决定是否是具体数字了
        } else if (child->nodeType == NodeType::ConstExp) {
            Value *constInitValue = nullptr;
            visitConstExp(child, &constInitValue, needNum);
            (*constInitVals)
                    .push_back(constInitValue);  // TODO isGlobal决定是否是具体数字了
        }
    }
    return 114514;
}

int Visitor::visitInitVal(Node *initVal, std::vector<Value *> *initVals,
                          bool needNum) {
    for (auto *child : initVal->children) {
        if (child->nodeType == NodeType::InitVal) {
            visitInitVal(child, initVals,
                         needNum);  // TODO isGlobal决定是否是具体数字了
        } else if (child->nodeType == NodeType::Exp) {
            Value *initValValue = nullptr;
            visitExp(child, &initValValue,
                     needNum);  // TODO isGlobal决定是否是具体数字了

            (*initVals).push_back(initValValue);
        }
    }
    return 114514;
}

int Visitor::visitFuncType(Node *funcType) {
    // funcType->getType() 0-int 1-void
    if (funcType->getType() == 0) {
        return 1;
    } else {
        return 0;
    }
}

void Visitor::visitBlock(Node *block) {
    for (auto *child : block->children) {
        if (visitBlockItem(child) == 1) {  // TODO ?
            break;
        }
    }
    symbolTable->deleteSymbolTable();
}

int Visitor::visitBlockItem(Node *blockItem) {
    for (auto *child : blockItem->children) {
        if (child->nodeType == NodeType::Decl) {
            visitDecl(child, false);
        } else {
            visitStmt(child);
            if (child->getType() == 3 || child->getType() == 4) {
                return 1;  // TODO ?
            }
        }
    }
    return 0;
}

void Visitor::visitForStmt(Node *forStmt) {
    // LVal = Exp
    Value *lValIns = nullptr;
    visitLVal(forStmt->children[0], &lValIns);

    // 得到的其实是一个 load 指令 他的operand才是alloc
    // 生成一个store指令
    if (lValIns != nullptr && lValIns->valueType == ValueType::Instruction) {
        //        ((Instruction *) lValIns)->useless = true;
        buildFactory->removeIns();
        Value *allocaIns = ((Instruction *) lValIns)->operands[0]->value;

        Value *expIns = nullptr;
        visitExp(forStmt->children[1], &expIns, false);

        Instruction *storeIns =
                buildFactory->genInstruction(InstructionType::Store, false);
        // 添加use
        use(expIns, storeIns, 0);
        use(allocaIns, storeIns, 1);
    }
}

int Visitor::visitExp(Node *exp, Value **expIns, bool needNum) {
    // 待施工 无需产生指令
    if (needNum) {
        // expIns将会是一个const
        return visitAddExp(exp->children[0], expIns,
                           needNum);  // TODO isGlobal决定是否具体数字？
    }

    Value *addIns = nullptr;
    for (auto *child : exp->children) {
        if (child->nodeType == NodeType::AddExp) {
            visitAddExp(child, &addIns, false);
        }
    }
    *expIns = addIns;
    return 114514;
}

int Visitor::visitLVal(Node *lVal, Value **lValInstruction) {
    string word = lVal->getWord();
    Symbol *symbol = symbolTable->getSymbol(
            word, false, true);  // 找这个数先不用考虑函数（不会是函数？）
#ifdef ERROR_CHECK
    if (symbol->word == "int") {
        printError(lVal->getLineNum(), "c");
    }
#endif
    if (buildFactory->curFunction == nullptr) {  // 全局状态
        auto *value = symbol->value;
        if (((GlobalVar *) value)->dims.empty()) {
            *lValInstruction = ((GlobalVar *) value)->operands[0]->value;
        } else {
            if (lVal->children.empty()) {
            } else if (lVal->children.size() == 1) {
                Value *expIns = nullptr;
                visitExp(lVal->children[0], &expIns,
                         true);  // TODO isGlobal决定是否具体数字
                *lValInstruction = ((GlobalVar *) value)
                        ->operands[atoi(expIns->getName().c_str())]
                        ->value;
            } else if (lVal->children.size() == 2) {
                Value *expIns1 = nullptr;
                Value *expIns2 = nullptr;
                visitExp(lVal->children[0], &expIns1,
                         true);  // TODO isGlobal决定是否具体数字
                visitExp(lVal->children[1], &expIns2,
                         true);  // TODO isGlobal决定是否具体数字
                *lValInstruction = ((GlobalVar *) value)
                        ->operands[atoi(expIns1->getName().c_str()) *
                                   ((GlobalVar *) value)->dims[1] +
                                   atoi(expIns2->getName().c_str())]
                        ->value;
            } else {
            }
        }
    } else {
        if (symbol->value->valueType == ValueType::Global) {  // 全局变量
            if (((Instruction *) (symbol->value))->dims.empty()) {
                Instruction *loadIns =
                        buildFactory->genInstruction(InstructionType::Load, true);
                use(symbol->value, loadIns, 0);
                *lValInstruction = loadIns;
            } else {
                auto *valueIns = symbol->value;
                Instruction *userIns = nullptr;
                int i = 0;
                while (i < lVal->children.size()) {
                    auto *Const = buildFactory->genConst(0);
                    Value *expIns = nullptr;
                    visitExp(lVal->children[i], &expIns,
                             false);  // TODO isGlobal决定是否具体数字

                    userIns = buildFactory->genInstruction(InstructionType::GEP, true);
                    use(valueIns, userIns, 0);
                    for (auto dim : ((Instruction *) valueIns)->dims) {
                        userIns->dims.push_back(dim);
                    }

                    use(Const, userIns, 1);
                    use(expIns, userIns, 2);
                    userIns->dims.erase(userIns->dims.begin());
                    valueIns = userIns;
                    i++;
                }
                if (i >= ((Instruction *) (symbol->value))->dims.size()) {
                    Instruction *loadIns =
                            buildFactory->genInstruction(InstructionType::Load, true);
                    use(userIns, loadIns, 0);
                    *lValInstruction = loadIns;
                } else {
                    userIns = buildFactory->genInstruction(InstructionType::GEP, true);
                    use(valueIns, userIns, 0);
                    for (auto dim : ((Instruction *) valueIns)->dims) {
                        userIns->dims.push_back(dim);
                    }
                    auto *Const = buildFactory->genConst(0);
                    use(Const, userIns, 1);
                    Value *expIns = buildFactory->genConst(0);
                    use(expIns, userIns, 2);
                    userIns->dims.erase(userIns->dims.begin());
                    *lValInstruction = userIns;
                }
            }
        } else if (symbol->value->valueType ==
                   ValueType::Instruction) {  // 不是全局变量
            if (((Instruction *) (symbol->value))->dims.empty()) {
                // 不是数组
                Instruction *loadIns =
                        buildFactory->genInstruction(InstructionType::Load, true);
                use(symbol->value, loadIns, 0);
                *lValInstruction = loadIns;
            } else {
                auto *valueIns = symbol->value;
                if (((Instruction *) (valueIns))->dims[0] == 0) {
                    // 函数中的处理
                    auto *loadIns =
                            buildFactory->genInstruction(InstructionType::Load, true);
                    use(valueIns, loadIns, 0);
                    loadIns->isPtr = true;
                    for (auto dim : ((Instruction *) (valueIns))->dims) {
                        loadIns->addDim(dim);
                    }
                    loadIns->dims.erase(loadIns->dims.begin());  // load里装的就不是指针了
                    if (!lVal->children.empty()) {
                        valueIns = loadIns;
                        if (lVal->children.size() == 1) {
                            if (((Instruction *) valueIns)->dims.empty()) {
                                Value *expIns = nullptr;
                                visitExp(lVal->children[0], &expIns,
                                         false);  // TODO isGlobal决定是否具体数字
                                Instruction *userIns =
                                        buildFactory->genInstruction(InstructionType::GEP, true);

                                use(valueIns, userIns, 0);
                                use(expIns, userIns, 1);
                                valueIns = userIns;
                                userIns = nullptr;
                            } else {
                                Value *expIns = nullptr;
                                visitExp(lVal->children[0], &expIns,
                                         false);  // TODO isGlobal决定是否具体数字
                                Instruction *userIns =
                                        buildFactory->genInstruction(InstructionType::GEP, true);
                                for (auto dim : ((Instruction *) valueIns)->dims) {
                                    userIns->addDim(dim);
                                }
                                use(valueIns, userIns, 0);
                                use(expIns, userIns, 1);

                                valueIns = userIns;
                                userIns =
                                        buildFactory->genInstruction(InstructionType::GEP, true);
                                use(valueIns, userIns, 0);
                                for (auto dim : ((Instruction *) valueIns)->dims) {
                                    userIns->addDim(dim);
                                }
                                userIns->dims.erase(userIns->dims.begin());
                                auto *Const = buildFactory->genConst(0);
                                use(Const, userIns, 1);
                                use(Const, userIns, 2);
                                valueIns = userIns;
                                userIns = nullptr;
                            }
                        } else if (lVal->children.size() == 2) {
                            Value *expIns = nullptr;
                            visitExp(lVal->children[0], &expIns,
                                     false);  // TODO isGlobal决定是否具体数字
                            Instruction *userIns =
                                    buildFactory->genInstruction(InstructionType::GEP, true);
                            for (auto dim : ((Instruction *) valueIns)->dims) {
                                userIns->addDim(dim);
                            }
                            use(valueIns, userIns, 0);
                            use(expIns, userIns, 1);
                            valueIns = userIns;
                            visitExp(lVal->children[1], &expIns,
                                     false);  // TODO isGlobal决定是否具体数字
                            userIns =
                                    buildFactory->genInstruction(InstructionType::GEP, true);
                            for (auto dim : ((Instruction *) valueIns)->dims) {
                                userIns->addDim(dim);
                            }
                            userIns->dims.erase(userIns->dims.begin());
                            use(valueIns, userIns, 0);
                            auto *Const = buildFactory->genConst(0);
                            use(Const, userIns, 1);
                            use(expIns, userIns, 2);
                            valueIns = userIns;
                            userIns = nullptr;
                        }
                        if (((Instruction *) (symbol->value))->dims.size() ==
                            lVal->children.size()) {
                            loadIns =
                                    buildFactory->genInstruction(InstructionType::Load, true);
                            use(valueIns, loadIns, 0);
                            for (auto dim : ((Instruction *) valueIns)->dims) {
                                loadIns->addDim(dim);
                            }
                            *lValInstruction = loadIns;
                        } else {
                            *lValInstruction = valueIns;
                        }
                    } else {
                        *lValInstruction = loadIns;
                    }
                } else {
                    // 不是在函数中参数（存的不是指针）
                    Instruction *userIns = nullptr;
                    int i = 0;
                    while (i < lVal->children.size()) {
                        Value *expIns = nullptr;
                        visitExp(lVal->children[i], &expIns,
                                 false);  // TODO isGlobal决定是否具体数字
                        userIns = buildFactory->genInstruction(InstructionType::GEP, true);
                        use(valueIns, userIns, 0);
                        for (auto dim : ((Instruction *) valueIns)->dims) {
                            userIns->dims.push_back(dim);
                        }
                        auto *Const = buildFactory->genConst(0);
                        use(Const, userIns, 1);
                        use(expIns, userIns, 2);
                        userIns->dims.erase(userIns->dims.begin());
                        valueIns = userIns;
                        i++;
                    }
                    if (i >= ((Instruction *) (symbol->value))->dims.size()) {
                        Instruction *loadInstruction =
                                buildFactory->genInstruction(InstructionType::Load, true);
                        use(userIns, loadInstruction, 0);
                        *lValInstruction = loadInstruction;
                    } else {
                        userIns = buildFactory->genInstruction(InstructionType::GEP, true);
                        use(valueIns, userIns, 0);
                        for (auto dim : ((Instruction *) valueIns)->dims) {
                            userIns->dims.push_back(dim);
                        }

                        auto *Const = buildFactory->genConst(0);
                        Value *expIns = buildFactory->genConst(0);

                        use(Const, userIns, 1);
                        use(expIns, userIns, 2);
                        userIns->dims.erase(userIns->dims.begin());
                        *lValInstruction = userIns;
                    }
                }
            }
        }
    }
    return 114514;
}

int Visitor::visitPrimaryExp(Node *primaryExp, Value **primaryInstruction,
                             bool needNum) {  // TODO isGlobal决定是否具体数字
    // 要生成指令了
    if (needNum) {  // 就想要这个数 产生那个const
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            return visitExp(primaryExp->children[0], primaryInstruction,
                            needNum);  // TODO isGlobal决定是否具体数字
        } else if (primaryExp->children[0]->nodeType == NodeType::LVal) {
            return visitLVal(primaryExp->children[0],
                             primaryInstruction);  // 寻找值的倒数第二个终结点
        } else if (primaryExp->children[0]->nodeType == NodeType::Number) {
            // 例如 return 0 应该直接返回0这个值
            *primaryInstruction = buildFactory->genConst(
                    primaryExp->children[0]->getVal());  // 寻找值的终结点
        }
    } else {
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            Value *expInstruction = nullptr;
            visitExp(primaryExp->children[0], &expInstruction,
                     needNum);  // TODO isGlobal决定是否具体数字
            *primaryInstruction = expInstruction;
        } else if (primaryExp->children[0]->nodeType == NodeType::LVal) {
            Value *lValInstruction = nullptr;
            visitLVal(primaryExp->children[0], &lValInstruction);
            *primaryInstruction = lValInstruction;
        } else if (primaryExp->children[0]->nodeType == NodeType::Number) {
            // 例如 return 0 应该直接返回0这个值
            int a = primaryExp->children[0]->getVal();
            *primaryInstruction = buildFactory->genConst(a);
        }
    }
    return 114514;
}

void Visitor::handleNumber(Node *number) {}

int NOT = -1;

int Visitor::visitUnaryExp(Node *unaryExp, Value **unaryInstruction,
                           bool needNum) {  // TODO isGlobal决定是否具体数字
    if (needNum) {
        if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
            // unaryIns是一个Const
            return visitPrimaryExp(unaryExp->children[0], unaryInstruction,
                                   needNum);  // TODO isGlobal决定是否具体数字
        } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
            int sign = 1;
            int op = visitUnaryOp(unaryExp->children[0]);
            if (op == 1) {  // -1
                sign *= -1;
            } else if (op == 2) {  // !
                NOT *= -1;
            }
            visitUnaryExp(unaryExp->children[1], unaryInstruction,
                          needNum);  // TODO isGlobal决定是否具体数字
            if ((*unaryInstruction)->valueType == ValueType::Const) {
                // 一定是
                ((Const *) (*unaryInstruction))->val *= sign;
            }
        }
    } else {
        if (unaryExp->children.empty()) {
            // 无参数的调用
            Symbol *sym = symbolTable->getSymbol(unaryExp->getWord(), true, true);
#ifdef ERROR_CHECK
            if (sym->word == "int") {
                printError(unaryExp->getLineNum(), "c");
            } else {
                if (!((Function *) sym->value)->params.empty()) {
                    printError(unaryExp->getLineNum(), "d");
                }
            }
#endif
            Value *function = sym->value;

            Instruction *call = buildFactory->genInstruction(
                    InstructionType::Call, ((Function *) function)->ret == 1);
            use(function, call, 0);
            *unaryInstruction = call;
            // 函数调用
        } else {
            if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
                Value *primaryIns = nullptr;
                visitPrimaryExp(unaryExp->children[0], &primaryIns,
                                needNum);  // TODO isGlobal决定是否具体数字
                *unaryInstruction = primaryIns;
            } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
                int op = visitUnaryOp(unaryExp->children[0]);
                if (op == 1) {
                    // -用0减
                    auto *c = new Const("", ValueType::Const, 0);
                    Value *right = nullptr;
                    visitUnaryExp(unaryExp->children[1], &right,
                                  needNum);  // TODO isGlobal决定是否具体数字
                    Instruction *subInstruction =
                            buildFactory->genInstruction(InstructionType::Sub, true);
                    use(c, subInstruction, 0);
                    use(right, subInstruction, 1);
                    *unaryInstruction = subInstruction;
                } else {
                    // !
                    if (op == 2) NOT *= -1;
                    visitUnaryExp(unaryExp->children[1], unaryInstruction,
                                  needNum);  // TODO isGlobal决定是否具体数字
                }
            } else {
                // 有参数的调用
                // Ident ()  调用函数
                vector<Value *> exps;
                for (auto *child : unaryExp->children) {
                    for (auto *child_ : child->children) {
                        Value *exp = nullptr;
                        visitExp(child_, &exp, needNum);
                        exps.push_back(exp);
                    }
                }
                Symbol *sym = symbolTable->getSymbol(unaryExp->getWord(), true, true);
#ifdef ERROR_CHECK
                if (sym->word == "int") {
                    printError(unaryExp->getLineNum(), "c");
                } else {
                    if (exps.size() != ((Function *) sym->value)->params.size()) {
                        printError(unaryExp->getLineNum(), "d");
                    }
                }
#endif
                Value *function = sym->value;
                Value *call = buildFactory->genInstruction(
                        InstructionType::Call, ((Function *) function)->ret == 1);
                use(function, ((Instruction *) call), 0);
                int x = 0;
                for (auto *child : exps) {
#ifdef ERROR_CHECK
                    if (child->valueType == ValueType::Instruction) {
                        auto *insChild = (Instruction *) child;
                        if (insChild->isPtr) {
                            if (!((insChild->dims.empty() &&
                                   ((Function *) function)->params[x++]->dims.size() == 1) ||
                                  (insChild->dims.size() == 1 &&
                                   ((Function *) function)->params[x++]->dims.size() == 2))) {
                                printError(unaryExp->getLineNum(), "e");
                            }
                        } else {
                            if (!((Function *) function)->params[x++]->dims.empty()) {
                                printError(unaryExp->getLineNum(), "e");
                            }
                        }
                    }

#endif
                    use(child, ((Instruction *) call), 0);
                }
                *unaryInstruction = call;
            }
        }
    }
    return 114514;
}

void Visitor::handleFuncRParams(Node *funcRParams, Value **call) {
    // 不用这个了
}

int Visitor::visitUnaryOp(Node *unaryOp) { return unaryOp->getType(); }

int Visitor::visitMulExp(Node *mulExp, Value **mulInstruction,
                         bool needNum) {  // TODO isGlobal决定是否具体数字
    if (needNum) {
        // mulIns将会是一个Const
        if (mulExp->children.size() == 1) {
            visitUnaryExp(mulExp->children[0], mulInstruction, needNum);
        } else {
            Value *mul1 = nullptr, *mul2 = nullptr;
            visitMulExp(mulExp->children[0], &mul1, needNum);
            visitUnaryExp(mulExp->children[1], &mul2, needNum);
            int m1 = atoi(mul1->getName().c_str());
            int m2 = atoi(mul2->getName().c_str());
            int val = (mulExp->getOp() == 0) ? m1 * m2
                                             : (mulExp->getOp() == 1) ? m1 / m2
                                                                      : m1 % m2;
            *mulInstruction = buildFactory->genConst(val);
        }
    } else {
        if (mulExp->children.size() == 1) {
            Value *unaryInstruction = nullptr;
            // 先不产生mul指令
            visitUnaryExp(mulExp->children[0], &unaryInstruction, needNum);
            *mulInstruction = unaryInstruction;
        } else if (mulExp->children.size() > 1) {
            // 要产生mul指令了
            Value *leftMulInstruction = nullptr;
            Value *rightUnaryInstruction = nullptr;
            visitMulExp(mulExp->children[0], &leftMulInstruction, needNum);
            visitUnaryExp(mulExp->children[1], &rightUnaryInstruction, needNum);

            InstructionType instructionType =
                    (mulExp->getOp() == 0) ? InstructionType::Mul
                                           : (mulExp->getOp() == 1) ? InstructionType::Div
                                                                    : InstructionType::Mod;

            if (instructionType == InstructionType::Mod) {
                // 先除再乘再减
                auto *instruction1 =
                        buildFactory->genInstruction(InstructionType::Div, true);
                instruction1->isMod = true;
                use(leftMulInstruction, instruction1, 0);
                use(rightUnaryInstruction, instruction1, 1);

                auto *instruction2 =
                        buildFactory->genInstruction(InstructionType::Mul, true);
                instruction2->isMod = true;
                use(rightUnaryInstruction, instruction2, 0);
                use(instruction1, instruction2, 1);

                auto *instruction3 =
                        buildFactory->genInstruction(InstructionType::Sub, true);
                instruction3->isMod = true;
                use(leftMulInstruction, instruction3, 0);
                use(instruction2, instruction3, 1);

                *mulInstruction = instruction3;
            } else {
                *mulInstruction = buildFactory->genInstruction(instructionType, true);
                use(leftMulInstruction, ((Instruction *) (*mulInstruction)), 0);
                use(rightUnaryInstruction, ((Instruction *) (*mulInstruction)), 1);
            }
        }
    }
    return 114514;
}

std::vector<Instruction *> brs;
std::vector<Instruction *> brs_;
std::vector<Instruction *> break_brs;
std::vector<BasicBlock *> beforeConds;
std::vector<Instruction *> continues;
int inFor = 0;

void Visitor::visitStmt(Node *stmt) {
    if (stmt->getType() == 5) {
        // 是return语句
        Value *expIns = nullptr;
        for (auto *child : stmt->children) {
            // 只可能是exp
            visitExp(child, &expIns, false);
            // 需要得到装着返回值的寄存器号 那是一个 Instruction
        }
        Instruction *retIns =
                buildFactory->genInstruction(InstructionType::Ret, false);
        if (!stmt->children.empty()) {
            use(expIns, retIns, 0);
        }
        // ret 语句中只会用到一个其他的寄存器号
        // ret 语句不需要加入符号表
        // 返回一个值 或 void 这个值来自于 visitExp
    } else if (stmt->getType() == 6) {
        //        // getint
        //        // 第一次先定义getint这个库函数
        //        static int gt = 0;
        //        if (gt != 1) {
        //            buildFactory->genFunction("getint", 0);
        //            gt = 1;
        //        }
        // 先处理printf中的exp，利用load获取他们的值
        Value *lVal = nullptr;
        visitLVal(stmt->children[0], &lVal);
        if (lVal != nullptr) {
            buildFactory->removeIns();
            Value *alloca = ((User *) lVal)->operands[0]->value;
            auto *call = buildFactory->genInstruction(InstructionType::Call, true);
            auto *getint = symbolTable->getSymbol("getint", true, true)->value;
            use(getint, call, 0);

            auto *store = buildFactory->genInstruction(InstructionType::Store, false);
            use(call, store, 0);
            use(alloca, store, 1);
        }
    } else if (stmt->getType() == 7) {
        // printf
        int j = 0;
        std::string str = stmt->getStr();
        vector<Value *> values;
        for (auto *child : stmt->children) {
            Value *value = nullptr;
            visitExp(child, &value, false);
            values.push_back(value);
        }
        for (int i = 1; i < str.size() - 1; ++i) {
            if (str[i] == '%' && str[i + 1] == 'd') {
                auto *call = buildFactory->genInstruction(InstructionType::Call, false);
                auto *putint = symbolTable->getSymbol("putint", true, true)->value;
                use(putint, call, 0);
                use(values[j], ((Instruction *) call), 0);
                j++;
                i++;
            } else if (str[i] == '\\' &&
                       str[i + 1] == 'n') {  // TODO 只有\n一种情况？
                auto *Const = buildFactory->genConst((int) '\n');
                auto *call = buildFactory->genInstruction(InstructionType::Call, false);
                auto *putch = symbolTable->getSymbol("putch", true, true)->value;
                use(putch, call, 0);
                use(Const, ((Instruction *) call), 0);
                i++;
            } else {
                auto *Const = buildFactory->genConst((int) str[i]);
                auto *call = buildFactory->genInstruction(InstructionType::Call, false);
                auto *putch = symbolTable->getSymbol("putch", true, true)->value;
                use(putch, call, 0);
                use(Const, ((Instruction *) call), 0);
            }
        }
    } else if (stmt->getType() == 0) {
        if (!stmt->children.empty()) {
            if (stmt->children[0]->getNodeType() == NodeType::Block) {  // 是 block
                symbolTable->createSymbolTable();
                visitBlock(stmt->children[0]);
            } else if (stmt->children[0]->getNodeType() == NodeType::LVal) {
                // LVal = Exp
                Value *lValIns = nullptr;
                visitLVal(stmt->children[0], &lValIns);
                // 得到的其实是一个 load 指令 他的operand才是alloc
                // 生成一个store指令
                if (lValIns != nullptr &&
                    lValIns->valueType == ValueType::Instruction) {
                    //                    ((Instruction *) lValIns)->useless = true;
                    buildFactory->removeIns();
                    Value *allocaIns = ((Instruction *) lValIns)->operands[0]->value;

                    Value *expIns = nullptr;
                    visitExp(stmt->children[1], &expIns,
                             false);  // TODO isGlobal决定是否具体数字 这里不是具体数字

                    Instruction *storeIns =
                            buildFactory->genInstruction(InstructionType::Store, false);
                    // 添加use
                    use(expIns, storeIns, 0);
                    use(allocaIns, storeIns, 1);
                }
            } else {
                if (!stmt->children.empty()) {
                    Value *value;
                    visitExp(stmt->children[0], &value,
                             false);  // TODO isGlobal决定是否具体数字 这里不是具体数字
                }
            }
        }
    } else if (stmt->getType() == 1) {
        // if
        int t = brs.size();

        auto *br0 = buildFactory->genInstruction(
                InstructionType::Br, false);  // 跳入第一个基本块（条件判断）
        buildFactory->genBasicBlock();
        use(buildFactory->curBasicBlock, br0, 0);

        Value *cond = nullptr;
        auto *br = visitCond(stmt->children[0], &cond);  // 产生两条指令 icmp 和 br

        visitStmt(stmt->children[1]);  // if语句块内的内容

        auto *br1 = buildFactory->genInstruction(InstructionType::Br,
                                                 false);  // 跳出if语句块

        buildFactory->genBasicBlock();

        // 条件语句不成立，不执行if语句的label2

        for (int i = brs.size() - 1; i >= t; --i) {
            use(buildFactory->curBasicBlock, brs[i], 2);
            brs.pop_back();
        }

        if (stmt->children.size() > 2) {  // 有else
            visitStmt(stmt->children[2]);   // else语句块内的内容
            auto *br2 = buildFactory->genInstruction(InstructionType::Br,
                                                     false);  // 跳出else语句

            buildFactory->genBasicBlock();
            use(buildFactory->curBasicBlock, br1, 0);
            use(buildFactory->curBasicBlock, br2, 0);
        } else {
            use(buildFactory->curBasicBlock, br1, 0);
        }
    } else if (stmt->getType() == 2) {
        // for
        inFor++;
        int t = brs.size();
        int c_t = continues.size();
        int b_t = break_brs.size();
        Stmt *forStmt = (Stmt *) stmt;
        if (forStmt->forStmt1 != nullptr) {
            visitForStmt(forStmt->forStmt1);
        }
        auto *br0 = buildFactory->genInstruction(InstructionType::Br, false);

        auto *beforCondLabel = buildFactory->genBasicBlock();
        beforeConds.push_back(beforCondLabel);
        use(buildFactory->curBasicBlock, br0, 0);
        Value *cond = nullptr;
        Instruction *br = nullptr;
        if (forStmt->cond != nullptr) {
            br = visitCond(forStmt->cond, &cond);
        }

        visitStmt(forStmt->children[0]);

        auto *br1 = buildFactory->genInstruction(InstructionType::Br, false);
        buildFactory->genBasicBlock();
        use(buildFactory->curBasicBlock, br1, 0);
        for (int i = continues.size() - 1; i >= c_t; i--) {
            use(buildFactory->curBasicBlock, continues[i], 0);
            continues.pop_back();
        }

        if (forStmt->forStmt2 != nullptr) {
            visitForStmt(forStmt->forStmt2);
        }
        auto *br2 = buildFactory->genInstruction(InstructionType::Br, false);
        use(beforeConds[beforeConds.size() - 1], br2, 0);
        beforeConds.pop_back();

        buildFactory->genBasicBlock();
        // 跳出for循环的位置 break 产生的br跳出的位置

        for (int i = brs.size() - 1; i >= t; --i) {
            use(buildFactory->curBasicBlock, brs[i], 2);
            brs.pop_back();
        }

        if (!break_brs.empty()) {
            // buildFactory->genBasicBlock(nullptr);
            for (int i = break_brs.size() - 1; i >= b_t; --i) {
                use(buildFactory->curBasicBlock, break_brs[i], 0);
                break_brs.pop_back();
            }
        }

        inFor--;
    } else if (stmt->getType() == 4) {
        // continue
        if (inFor) {
            auto *br = buildFactory->genInstruction(InstructionType::Br, false);;
            continues.push_back(br);
        }
    } else if (stmt->getType() == 3) {
        // break
        if (inFor) {
            auto *br = buildFactory->genInstruction(InstructionType::Br, false);
            break_brs.push_back(br);
        }
    }
}

Instruction *Visitor::visitCond(Node *cond, Value **c) {
    brs_.clear();
    Instruction *br = visitLOrExp(cond->children[0]);
    buildFactory->genBasicBlock();
    for (auto *child : brs_) {
        use(buildFactory->curBasicBlock, child, 1);
    }
    brs_.clear();
    return br;
    // 生成一条跳转指令，进入条件的判断
}

Instruction *Visitor::visitLOrExp(Node *lOrExp) {
    int t = brs.size();
    if (lOrExp->children.size() == 1) {
        return visitLAndExp(lOrExp->children[0]);
    } else {
        //        brs.clear();
        visitLOrExp(lOrExp->children[0]);
        buildFactory->genBasicBlock();
        // 现在它们知道label2了
        //        for (auto *child: brs) {
        //            use(buildFactory->curBasicBlock, child, 2);
        //        }
        for (int i = brs.size() - 1; i >= t; --i) {
            use(buildFactory->curBasicBlock, brs[i], 2);
            brs.pop_back();
        }
        //        brs.clear();
        return visitLAndExp(lOrExp->children[1]);
    }
}

Instruction *Visitor::visitLAndExp(Node *lAndExp) {
    // 1 && 2
    Instruction *br = nullptr;
    if (lAndExp->children.size() == 1) {
        Value *v = nullptr;
        // 产生新的基本块
        br = visitEqExp(lAndExp->children[0], &v, true);
        brs_.push_back(br);
    } else {
        Value *br1 = visitLAndExp(lAndExp->children[0]);
        brs_.pop_back();
        // 产生新的基本块
        buildFactory->genBasicBlock();
        // 在handleAnd中知道label1了 但还不知道label2
        use(buildFactory->curBasicBlock, ((Instruction *) br1), 1);

        Value *v = nullptr;
        br = visitEqExp(lAndExp->children[1], &v, true);
        brs_.push_back(br);
    }
    return br;
}

Instruction *Visitor::visitEqExp(Node *eqExp, Value **eq, bool isBr) {
    if (eqExp->children.size() == 1) {
        Value *rel = nullptr;
        // 先不产生add指令
        NOT = -1;
        visitRelExp(eqExp->children[0], &rel);
        if (rel->ty != 32) {
            auto *zext = buildFactory->genInstruction(InstructionType::Zext, true);
            use(rel, zext, 0);
            rel = zext;
        }
        *eq = rel;
        if (NOT == 1 && !isBr) {
            InstructionType instructionType =
                    (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(instructionType, true);
            auto *Const = buildFactory->genConst(0);
            use(Const, ne, 0);
            use((*eq), ne, 1);
            *eq = ne;
        }

        if (isBr) {
            InstructionType instructionType =
                    (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(instructionType, true);
            auto *Const = buildFactory->genConst(0);
            use(Const, ne, 0);
            use((*eq), ne, 1);
            *eq = ne;
        }
    } else if (eqExp->children.size() > 1) {
        Value *leftEq = nullptr;
        Value *rightRel = nullptr;
        visitEqExp(eqExp->children[0], &leftEq, false);

        NOT = -1;
        visitRelExp(eqExp->children[1], &rightRel);
        if (NOT == 1) {
            InstructionType instructionType =
                    (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(instructionType, true);
            auto *Const = buildFactory->genConst(0);
            use(Const, ne, 0);
            use(rightRel, ne, 1);
            rightRel = ne;
        }

        InstructionType instructionType =
                (eqExp->getOp() == 0) ? InstructionType::Eq : InstructionType::Ne;

        if (leftEq->ty == 1) {
            auto *zext = buildFactory->genInstruction(InstructionType::Zext, true);
            use(leftEq, zext, 0);
            leftEq = zext;
        }
        if (rightRel->ty == 1) {
            auto *zext = buildFactory->genInstruction(InstructionType::Zext, true);
            use(rightRel, zext, 0);
            rightRel = zext;
        }

        *eq = buildFactory->genInstruction(instructionType, true);
        use(leftEq, ((Instruction *) (*eq)), 0);
        use(rightRel, ((Instruction *) (*eq)), 0);
    }
    // 这里才是最小的，产生新的br指令,并与使用*eq
    if (isBr) {
        auto *br = buildFactory->genInstruction(InstructionType::Br, false);
        use((*eq), br, 0);
        // 此时的br还不知道自己要跳到哪里，但回到handleAnd中将会知道label1，即成立时要跳到哪里
        brs.push_back(br);
        // 先将它们装进一个向量里，回到handleOr中将会知道label2，即不成立时会跳到哪里
        return br;
    } else {
        return nullptr;
    }
}

void Visitor::visitRelExp(Node *relExp, Value **rel) {
    if (relExp->children.size() == 1) {
        Value *add = nullptr;
        visitAddExp(relExp->children[0], &add, false);
        *rel = add;
    } else if (relExp->children.size() > 1) {
        // 要产生add指令了
        Value *leftRel = nullptr;
        Value *righAdd = nullptr;
        NOT = -1;
        visitRelExp(relExp->children[0], &leftRel);
        if (NOT == 1) {
            InstructionType instructionType =
                    (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(instructionType, true);
            auto *Const = buildFactory->genConst(0);
            use(Const, ne, 0);
            use(leftRel, ne, 1);
            leftRel = ne;
        }
        NOT = -1;
        visitAddExp(relExp->children[1], &righAdd, false);
        if (NOT == 1) {
            InstructionType instructionType =
                    (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(instructionType, true);
            auto *Const = buildFactory->genConst(0);
            use(Const, ne, 0);
            use(righAdd, ne, 1);
            righAdd = ne;
        }

        InstructionType instructionType =
                (relExp->getOp() == 1) ? InstructionType::Ge
                                       : (relExp->getOp() == 0) ? InstructionType::Gt
                                                                : (relExp->getOp() == 2) ? InstructionType::Lt
                                                                                         : InstructionType::Le;

        if (leftRel->ty != righAdd->ty) {
            if (leftRel->ty == 1) {
                auto *zext = buildFactory->genInstruction(InstructionType::Zext, true);
                use(leftRel, zext, 0);
                leftRel = zext;
            } else if (righAdd->ty == 1) {
                auto *zext = buildFactory->genInstruction(InstructionType::Zext, true);
                use(righAdd, zext, 0);
                righAdd = zext;
            }
        }

        *rel = buildFactory->genInstruction(instructionType, true);
        use(leftRel, ((Instruction *) (*rel)), 0);
        use(righAdd, ((Instruction *) (*rel)), 1);
    }
}

int Visitor::visitAddExp(Node *addExp, Value **addInstruction, bool isGlobal) {
    if (isGlobal) {
        // addIns将会是一个Const
        if (addExp->children.size() == 1) {
            visitMulExp(addExp->children[0], addInstruction, isGlobal);
        } else {
            Value *add1 = nullptr, *add2 = nullptr;
            visitAddExp(addExp->children[0], &add1, isGlobal);
            visitMulExp(addExp->children[1], &add2, isGlobal);
            int a1 = atoi(add1->getName().c_str());
            int a2 = atoi(add2->getName().c_str());
            int val = (addExp->getOp() == 1) ? (a1 - a2) : (a1 + a2);
            *addInstruction = buildFactory->genConst(val);
        }
    } else {
        if (addExp->children.size() == 1) {
            Value *mulInstruction = nullptr;
            // 先不产生add指令
            visitMulExp(addExp->children[0], &mulInstruction, isGlobal);
            *addInstruction = mulInstruction;
        } else if (addExp->children.size() > 1) {
            // 要产生add指令了
            Value *leftAddInstruction = nullptr;
            Value *rightMulInstruction = nullptr;
            visitAddExp(addExp->children[0], &leftAddInstruction, isGlobal);
            visitMulExp(addExp->children[1], &rightMulInstruction, isGlobal);

            InstructionType instructionType =
                    (addExp->getOp() == 0) ? InstructionType::Add : InstructionType::Sub;

            *addInstruction = buildFactory->genInstruction(instructionType, true);
            use(leftAddInstruction, ((Instruction *) (*addInstruction)), 0);
            use(rightMulInstruction, ((Instruction *) (*addInstruction)), 1);
        }
    }
    return 114514;
}

int Visitor::visitConstExp(Node *constExp, Value **constExpInstruction,
                           bool isGlobal) {  // TODO isGlobal决定是否具体数字
    if (isGlobal) {
        return visitAddExp(constExp->children[0], constExpInstruction, isGlobal);
    }
    Value *addInstruction = nullptr;
    for (auto *child : constExp->children) {
        if (child->nodeType == NodeType::AddExp) {
            visitAddExp(child, &addInstruction, isGlobal);
        }
    }
    *constExpInstruction = addInstruction;
    return 114514;
}

Visitor::Visitor() {
    this->buildFactory = new BuildFactory();
    this->symbolTable = new SymbolTable();
    symbolTable->createSymbolTable();
    auto *getint = buildFactory->genFunction("getint", 0);
    getint->ret = 1;
    auto *putint = buildFactory->genFunction("putint", 1);
    putint->ret = 0;
    auto *putch = buildFactory->genFunction("putch", 1);
    putch->ret = 0;
    auto *putstr = buildFactory->genFunction("putstr", 1);
    putstr->ret = 0;
    auto *symbol0 = new Symbol("getint", getint);
    auto *symbol1 = new Symbol("putint", putint);
    auto *symbol2 = new Symbol("putch", putch);
    auto *symbol3 = new Symbol("putstr", putstr);
    symbolTable->addSymbol(symbol0, 0);
    symbolTable->addSymbol(symbol1, 0);
    symbolTable->addSymbol(symbol2, 0);
    symbolTable->addSymbol(symbol3, 0);
}

Module *Visitor::getModule() { return this->buildFactory->genIRModule(); }
