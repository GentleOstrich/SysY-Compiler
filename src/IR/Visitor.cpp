#include "Visitor.h"

#define use(a, b, pos) use = new Use(a,b,pos); a->addUse(use); b->addOperand(use)
Use *use = nullptr;

void Visitor::handleCompUnit(Node *compUnit) {
    for (auto *child: compUnit->children) {
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
    //TODO
    // 数组相关
    if (isGlobal) {
        auto *globalVar = buildFactory->genGlobalVar(varDef, 0, false);
        auto *symbol = new Symbol(varDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        for (auto *child: varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                //返回具体数字
                std::vector<Value *> initVals;
                handleInitVal(child, &initVals, isGlobal);
                for (int i = 0; i < initVals.size(); ++i) {
                    use(initVals[i], globalVar, i);
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 各维的长度
                Value *Const = nullptr;
                handleConstExp(child, &Const, isGlobal);
                globalVar->addDim(atoi(Const->getName().c_str()));
            }
        }
    } else {
        auto *allocInstruction = buildFactory->genInstruction(varDef, InstructionType::Alloca, true);
        auto *symbol = new Symbol(varDef->getWord(), allocInstruction);
        symbolTable->addSymbol(symbol, varDef->getLineNum());
        symbolTable->symbolId--;
        for (auto *child: varDef->children) {
            if (child->getNodeType() == NodeType::InitVal) {
                std::vector<Value *> initVals;
                handleInitVal(child, &initVals, isGlobal);
                int i = 0;
                for (auto initVal: initVals) {
                    if (allocInstruction->dims.size() < 1) {
                        // 不是数组 不需要GEP
                        auto *storeInstruction = buildFactory->genInstruction(varDef, InstructionType::Store, false);
                        use(initVal, storeInstruction, 0);
                        use(allocInstruction, storeInstruction, 1);
                    } else {
                        // 是数组
                        auto *GEPIns = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
                        for (auto dim:allocInstruction->dims) {
                            GEPIns->addDim(dim);
                        }

                        use(allocInstruction, GEPIns, 0);
                        auto *Const1 = buildFactory->genConst(nullptr, 0);
                        use(Const1, GEPIns, 1); // 此处第一个移动数都是0 （整体不移动）

                        if (allocInstruction->dims.size() == 1) {
                            Const1 = buildFactory->genConst(nullptr, i);
                            use(Const1, GEPIns, 2);
                        } else if (allocInstruction->dims.size() == 2) {
                            Const1 = buildFactory->genConst(nullptr, i / allocInstruction->dims[1]);
                            use(Const1, GEPIns, 2);
                            Const1 = buildFactory->genConst(nullptr, i % allocInstruction->dims[1]);
                            use(Const1, GEPIns, 3);
                        }

                        auto *storeInstruction = buildFactory->genInstruction(varDef, InstructionType::Store, false);
                        use(initVal, storeInstruction, 0);
                        use(GEPIns, storeInstruction, 1);
                    }
                    i++;
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 各维的长度
                Value *Const = nullptr;
                handleConstExp(child, &Const, isGlobal);
                // 设定alloca的维度
                allocInstruction->addDim(atoi(Const->getName().c_str()));
            }
        }
        symbolTable->symbolId++;
    }
    // 对于变量的定义，要生成一个alloc类指令 varDef里是包含变量名字的
}

void Visitor::handleConstDef(Node *constDef, bool isGlobal) {
    //TODO
    // 数组相关
    // 需要加符号表了
    if (isGlobal) {
        auto *globalVar = buildFactory->genGlobalVar(constDef, 0, true);
        auto *symbol = new Symbol(constDef->getWord(), globalVar);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        for (auto *child: constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                //返回具体数字
                //TODO
                std::vector<Value *> initVals;
                handleConstInitVal(child, &initVals, isGlobal);
                for (int i = 0; i < initVals.size(); ++i) {
                    use(initVals[i], globalVar, i);
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 各维的长度
                Value *Const = nullptr;
                handleConstExp(child, &Const, isGlobal);
                globalVar->addDim(atoi(Const->getName().c_str()));
            }
        }
    } else {
        auto *allocInstruction = buildFactory->genInstruction(constDef, InstructionType::Alloca, true);
        auto *symbol = new Symbol(constDef->getWord(), allocInstruction);
        symbolTable->addSymbol(symbol, constDef->getLineNum());
        symbolTable->symbolId--;
        for (auto *child: constDef->children) {
            if (child->getNodeType() == NodeType::ConstInitVal) {
                std::vector<Value *> constInitVals;
                handleConstInitVal(child, &constInitVals, isGlobal);
                for (auto constInitVal: constInitVals) {
                    auto *storeInstruction = buildFactory->genInstruction(constDef, InstructionType::Store, false);
                    use(constInitVal, storeInstruction, 0);
                    use(allocInstruction, storeInstruction, 1);
                }
            } else if (child->getNodeType() == NodeType::ConstExp) {
                // 各维的长度
                Value *Const = nullptr;
                handleConstExp(child, &Const, isGlobal);
                allocInstruction->addDim(atoi(Const->getName().c_str()));
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

    function->ret = handleFuncType(funcDef->children[0]);
    symbolTable->createSymbolTable();

    for (int i = 1; i < funcDef->children.size(); ++i) {
        if (funcDef->children[i]->getNodeType() == NodeType::FuncFParams) {
            function->cnt = handleFuncFParams(funcDef->children[i]);
        } else if (funcDef->children[i]->getNodeType() == NodeType::Block) {
            if (buildFactory->curBasicBlock == nullptr) {
                buildFactory->genBasicBlock(nullptr);
            }
            handleBlock(funcDef->children[i]);
        }
    }
}

int Visitor::handleFuncFParams(Node *funcFParams) {
    // 返回形参个数
    int ret = 0;
    vector<Value *> params;
    for (auto *child: funcFParams->children) {
        if (child->nodeType == NodeType::FuncFParam) {
            // 这里是形参，要添加形参转换实参的alloc和store
            Value *param = nullptr;
            handleFuncFParam(child, &param);
            params.push_back(param);
            ret++;
        }
    }
    buildFactory->genBasicBlock(nullptr); // 这个参数没有用
    vector<Value *> allocas;


    // 把参数都先存起来
    // 分配 alloca
    for (int i = 0; i < params.size(); ++i) {
        Instruction *alloca = buildFactory->genInstruction(funcFParams, InstructionType::Alloca, true);
        auto *symbol = new Symbol(funcFParams->children[i]->getWord(), alloca);
        symbolTable->addSymbol(symbol, funcFParams->getLineNum());
        allocas.push_back(alloca);
    }
    // 存储 store
    for (int i = 0; i < params.size(); ++i) {
        Instruction *store = buildFactory->genInstruction(funcFParams, InstructionType::Store, false);
        use(params[i], store, 0);
        use(allocas[i], store, 1);
        // 设定alloc的维度
        for (auto dim:((Param *) params[i])->dims) {
            ((Instruction *) allocas[i])->addDim(dim);
        }
    }
    return ret;
}

void Visitor::handleFuncFParam(Node *funcFParam, Value **param) {
    //TODO
    // 数组相关
    auto *param1 = buildFactory->genParam(funcFParam);
    if (funcFParam->getType() > 0) {
        param1->addDim(0);
    }
    for (auto *child:funcFParam->children) {
        if (child->getNodeType() == NodeType::BType) {
            handleBType(child);
        } else if (child->getNodeType() == NodeType::ConstExp) {
            Value *Const = nullptr;
            handleConstExp(child, &Const, false);

            param1->addDim(atoi(Const->getName().c_str()));
        }
    }
    *param = param1;

}

void Visitor::handleDecl(Node *Decl, bool isGlobal) {
    for (auto *child: Decl->children) {
        if (child->nodeType == NodeType::ConstDecl) {
            handleConstDecl(child, isGlobal);
        } else if (child->nodeType == NodeType::VarDecl) {
            handleVarDecl(child, isGlobal);
        }
    }
}

void Visitor::handleMainFuncDef(Node *mainFuncFParam) {
    auto *f = buildFactory->genFunction(mainFuncFParam);
    f->ret = 1;
    for (auto *child: mainFuncFParam->children) {
        symbolTable->createSymbolTable();
        buildFactory->genBasicBlock(child);
        handleBlock(child);
    }
}

void Visitor::handleConstDecl(Node *constDecl, bool isGlobal) {
    for (auto *child: constDecl->children) {
        if (child->nodeType == NodeType::BType) {
            handleBType(child);
        } else if (child->nodeType == NodeType::ConstDef) {
            handleConstDef(child, isGlobal);
        }
    }
}

void Visitor::handleVarDecl(Node *varDecl, bool isGlobal) {
    for (auto *child: varDecl->children) {
        if (child->nodeType == NodeType::BType) {
            handleBType(child);
        } else if (child->nodeType == NodeType::VarDef) {
            handleVarDef(child, isGlobal);
        }
    }
}

void Visitor::handleBType(Node *BType) {

}

int Visitor::handleConstInitVal(Node *constInitVal, std::vector<Value *> *constInitVals, bool isGlobal) {

    //TODO
    // 数组相关
    for (auto *child: constInitVal->children) {
        if (child->nodeType == NodeType::ConstInitVal) {
            handleConstInitVal(child, constInitVals, isGlobal);
        } else if (child->nodeType == NodeType::ConstExp) {
            Value *constInitValue = nullptr;
            handleConstExp(child, &constInitValue, isGlobal);
            (*constInitVals).push_back(constInitValue);
            // 返回具体数字
        }
    }
    return -114514;
}

int Visitor::handleInitVal(Node *initVal, std::vector<Value *> *initVals, bool isGlobal) {
    //TODO
    // 数组相关
    // 有多个不能只返回一个值
    for (auto *child: initVal->children) {
        if (child->nodeType == NodeType::InitVal) {
            handleInitVal(child, initVals, isGlobal);
        } else if (child->nodeType == NodeType::Exp) {
            Value *initValValue = nullptr;
            handleExp(child, &initValValue, isGlobal);
            (*initVals).push_back(initValValue);
            // 返回具体数字 nullptr 要具体数字 否则 要指令
        }
    }
    return -114514;
}


int Visitor::handleFuncType(Node *funcType) {
    if (funcType->getType() == 0) {
        return 1;
    } else {
        return 0;
    }
}

void Visitor::handleBlock(Node *block) {
    for (auto *child: block->children) {
        handleBlockItem(child);
    }
    symbolTable->deleteSymbolTable();
}

void Visitor::handleBlockItem(Node *blockItem) {
    for (auto *child: blockItem->children) {
        if (child->nodeType == NodeType::Decl) {
            handleDecl(child, false);
        } else {
            handleStmt(child);
        }
    }
}

void Visitor::handleForStmt(Node *forStmt) {
    // LVal = Exp
    Value *lValInstruction = nullptr;
    handleLVal(forStmt->children[0], &lValInstruction);
    // 得到的其实是一个 load 指令 他的operand才是alloc
    // 生成一个store指令
    if (lValInstruction->valueType == ValueType::Instruction) {
        Value *allocInstruction = ((Instruction *) lValInstruction)->operands[0]->value;

        Value *expInstruction = nullptr;
        handleExp(forStmt->children[1], &expInstruction, false);

        Instruction *storeInstruction = buildFactory->genInstruction(forStmt, InstructionType::Store, false);
        // 添加use
        use(expInstruction, storeInstruction, 0);
        use(allocInstruction, storeInstruction, 1);
    }

}

int Visitor::handleExp(Node *exp, Value **expInstruction, bool isGlobal) {
    // 待施工 无需产生指令
    if (isGlobal) {
        // expIns将会是一个const
        return handleAddExp(exp->children[0], expInstruction, isGlobal);
    }
    Value *addInstruction = nullptr;
    for (auto *child: exp->children) {
        if (child->nodeType == NodeType::AddExp) {
            handleAddExp(child, &addInstruction, false);
        }
    }
    *expInstruction = addInstruction;
    return -114514;
}


int Visitor::handleLVal(Node *lVal, Value **lValInstruction) {
    //TODO
    // 数组相关

    string word = lVal->getWord();
    Symbol *symbol = symbolTable->getSymbol(word, false, true); // 找这个数先不用考虑函数
    if (symbol->value->valueType == ValueType::Global) {
        if (((Instruction *) (symbol->value))->dims.empty()) {
            Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
            if (symbol->value->valueType == ValueType::Instruction) {
                for (auto dim:((Instruction *) symbol->value)->dims) {
                    loadInstruction->addDim(dim);
                }
            }
            use(symbol->value, loadInstruction, 0);
            *lValInstruction = loadInstruction;
        } else {
            auto *GEPIns = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
            use(symbol->value, GEPIns, 0);
            for (auto dim:((Instruction *) (symbol->value))->dims) {
                GEPIns->dims.push_back(dim);
            }
            auto *Const = buildFactory->genConst(nullptr, 0);
            use(Const, GEPIns, 1);
            int i = 2;
            for (auto *child:lVal->children) {
                if (child->getNodeType() == NodeType::Exp) {
                    Value *expIns = nullptr;
                    handleExp(child, &expIns, false);
                    use(expIns, GEPIns, i++);
                    GEPIns->dims.erase(GEPIns->dims.begin());
                }
            }
            Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
            use(GEPIns, loadInstruction, 0);
            *lValInstruction = loadInstruction;
        }
        //TODO
        // 左值先返回0
        return 0;
    } else if (symbol->value->valueType == ValueType::Instruction) {
        if (((Instruction *) (symbol->value))->dims.empty()) {
            // 不是数组
            Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
            if (symbol->value->valueType == ValueType::Instruction) {
                for (auto dim:((Instruction *) symbol->value)->dims) {
                    loadInstruction->addDim(dim);
                }
            }
            use(symbol->value, loadInstruction, 0);
            *lValInstruction = loadInstruction;
        } else {
            if (((Instruction *) (symbol->value))->dims[0] != 0) {
                auto *GEPIns = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
                use(symbol->value, GEPIns, 0);
                for (auto dim:((Instruction *) (symbol->value))->dims) {
                    GEPIns->dims.push_back(dim);
                }
                auto *Const = buildFactory->genConst(nullptr, 0);
                use(Const, GEPIns, 1);
                int i = 2;
                for (auto *child:lVal->children) {
                    if (child->getNodeType() == NodeType::Exp) {
                        Value *expIns = nullptr;
                        handleExp(child, &expIns, false);
                        use(expIns, GEPIns, i++);
                        GEPIns->dims.erase(GEPIns->dims.begin());
                    }
                }
                Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
                use(GEPIns, loadInstruction, 0);
                *lValInstruction = loadInstruction;
            } else {
                if (((Instruction *) (symbol->value))->dims.size() == 1) {
                    auto *loadIns = buildFactory->genInstruction(nullptr, InstructionType::Load, true);
                    use(symbol->value, loadIns, 0);
                    for(int i = 1; i < ((Instruction *) (symbol->value))->dims.size(); ++i) {
                        loadIns->addDim(((Instruction *) (symbol->value))->dims[i]);
                    }


                    auto *GEPIns = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
                    use(loadIns, GEPIns, 0);
                    for (auto dim:loadIns->dims){
                        GEPIns->addDim(dim);
                    }

                    int i = 1;
                    for (auto *child:lVal->children) {
                        if (child->getNodeType() == NodeType::Exp) {
                            Value *expIns = nullptr;
                            handleExp(child, &expIns, false);
                            use(expIns, GEPIns, i++);
                        }
                    } // 应该只会有一个
                    Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
                    use(GEPIns, loadInstruction, 0);
                    *lValInstruction = loadInstruction;
                } else if (((Instruction *) (symbol->value))->dims.size() == 2) {

                    auto *loadIns = buildFactory->genInstruction(nullptr, InstructionType::Load, true);
                    use(symbol->value, loadIns, 0);

                    for(int i = 1; i < ((Instruction *) (symbol->value))->dims.size(); ++i) {
                        loadIns->addDim(((Instruction *) (symbol->value))->dims[i]);
                    }

                    auto *GEPIns = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
                    use(loadIns, GEPIns, 0);
                    for (auto dim:loadIns->dims){
                        GEPIns->addDim(dim);
                    }

                    int i = 1;
                    Value *expIns = nullptr;
                    handleExp(lVal->children[0], &expIns, false);
                    use(expIns, GEPIns, i++);

                    auto *GEPIns1 = buildFactory->genInstruction(nullptr, InstructionType::GEP, true);
                    use(GEPIns, GEPIns1, 0);

                    auto* Const = buildFactory->genConst(nullptr, 0);
                    use(Const, GEPIns1, i++);
                    handleExp(lVal->children[1], &expIns, false);
                    use(expIns, GEPIns1, i++);

                    Instruction *loadInstruction = buildFactory->genInstruction(lVal, InstructionType::Load, true);
                    use(GEPIns1, loadInstruction, 0);

                    for(int i = 1; i < GEPIns1->dims.size(); ++i) {
                        loadInstruction->addDim(GEPIns1->dims[i]);
                    }

                    *lValInstruction = loadInstruction;
                } else {
                    std::cout << "invalid dim" << std::endl;
                }

            }
        }

        // 找到专门的alloc指令
        // 等一下还要向其他的一样传入Value的形参
    }
    return -114514;
}

int Visitor::handlePrimaryExp(Node *primaryExp, Value **primaryInstruction, bool isGlobal) {
    // 要生成指令了
    if (isGlobal) { // 就想要这个数 产生那个const
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            return handleExp(primaryExp->children[0], primaryInstruction, isGlobal);
        } else if (primaryExp->children[0]->nodeType == NodeType::LVal) {
            return handleLVal(primaryExp->children[0], primaryInstruction); // 寻找值的倒数第二个终结点
        } else if (primaryExp->children[0]->nodeType == NodeType::Number) {
            // 例如 return 0 应该直接返回0这个值
            *primaryInstruction = buildFactory->genConst(nullptr, primaryExp->children[0]->getVal()); // 寻找值的终结点
        }
    } else {
        if (primaryExp->children[0]->nodeType == NodeType::Exp) {
            Value *expInstruction = nullptr;
            handleExp(primaryExp->children[0], &expInstruction, isGlobal);
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

int NOT = -1;

int Visitor::handleUnaryExp(Node *unaryExp, Value **unaryInstruction, bool isGlobal) {
    // 无需产生指令
    if (isGlobal) { // 就想要这个数
        if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
            // unaryIns是一个Const
            return handlePrimaryExp(unaryExp->children[0], unaryInstruction, isGlobal);
        } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
            int sign = 1;
            int op = handleUnaryOp(unaryExp->children[0]);
            if (op == 1) {
                sign *= -1;
            } else if (op == 2) {
                NOT *= -1;
            }
            handleUnaryExp(unaryExp->children[1], unaryInstruction, isGlobal);
            if ((*unaryInstruction)->valueType == ValueType::Const) {
                //一定是
                ((Const *) (*unaryInstruction))->val *= op;
            }
        }
    } else {
        if (unaryExp->children.size() == 0) {
            Value *function = symbolTable->getSymbol(unaryExp->getWord(), true, true)->value;
            Instruction *call = buildFactory->genInstruction(unaryExp, InstructionType::Call, true);
            use(function, call, 0);
            *unaryInstruction = call;
            // 函数调用
        } else {
            if (unaryExp->children[0]->nodeType == NodeType::PrimaryExp) {
                Value *primaryInstruction = nullptr;
                handlePrimaryExp(unaryExp->children[0], &primaryInstruction, isGlobal);
                *unaryInstruction = primaryInstruction;
            } else if (unaryExp->children[0]->nodeType == NodeType::UnaryOp) {
                int op = handleUnaryOp(unaryExp->children[0]);
                if (op == 1) {
                    auto *c = new Const("", ValueType::Const, 0);

                    Value *right;
                    handleUnaryExp(unaryExp->children[1], &right, isGlobal);

                    Instruction *subInstruction = buildFactory->genInstruction(unaryExp, InstructionType::Sub, true);


                    use(c, subInstruction, 0);
                    use(right, subInstruction, 1);

                    *unaryInstruction = subInstruction;
                } else {
                    // 这里是为什么来着:
                    // + - !
                    if (op == 2) NOT *= -1;
                    handleUnaryExp(unaryExp->children[1], unaryInstruction, isGlobal);
                }
            } else {
                // Ident ()  调用函数
                vector<Value *> exps;
                for (auto *child: unaryExp->children) {
                    for (auto *child_: child->children) {
                        Value *exp = nullptr;
                        handleExp(child_, &exp, isGlobal);
                        exps.push_back(exp);
                    }
                }
                Value *function = symbolTable->getSymbol(unaryExp->getWord(), true, true)->value;
                Value *call = buildFactory->genInstruction(unaryExp, InstructionType::Call, true);
                use(function, ((Instruction *) call), 0);
                for (auto *child: exps) {
                    use(child, ((Instruction *) call), 0);
                }
                *unaryInstruction = call;
            }
        }
    }

    return -114514;
}

void Visitor::handleFuncRParams(Node *funcRParams, Value **call) {
    // 不用这个了
}


int Visitor::handleUnaryOp(Node *unaryOp) {
    return unaryOp->getType();
}


int Visitor::handleMulExp(Node *mulExp, Value **mulInstruction, bool isGlobal) {
    if (isGlobal) {
        // mulIns将会是一个Const
        if (mulExp->children.size() == 1) {
            handleUnaryExp(mulExp->children[0], mulInstruction, isGlobal);
        } else {
            Value *mul1 = nullptr, *mul2 = nullptr;
            handleMulExp(mulExp->children[0], &mul1, isGlobal);
            handleUnaryExp(mulExp->children[1], &mul2, isGlobal);
            int m1 = atoi(mul1->getName().c_str());
            int m2 = atoi(mul2->getName().c_str());
            int val = (mulExp->getOp() == 0) ? m1 * m2 :
                      (mulExp->getOp() == 1) ? m1 / m2 : m1 % m2;
            *mulInstruction = buildFactory->genConst(nullptr, val);
        }
    } else {
        if (mulExp->children.size() == 1) {
            Value *unaryInstruction = nullptr;
            //先不产生mul指令
            handleUnaryExp(mulExp->children[0], &unaryInstruction, isGlobal);
            *mulInstruction = unaryInstruction;
        } else if (mulExp->children.size() > 1) {
            //要产生mul指令了
            Value *leftMulInstruction = nullptr;
            Value *rightUnaryInstruction = nullptr;
            handleMulExp(mulExp->children[0], &leftMulInstruction, isGlobal);
            handleUnaryExp(mulExp->children[1], &rightUnaryInstruction, isGlobal);

            InstructionType instructionType = (mulExp->getOp() == 0) ? InstructionType::Mul :
                                              (mulExp->getOp() == 1) ? InstructionType::Div :
                                              InstructionType::Mod;

            if (instructionType == InstructionType::Mod) {
                // 先除再乘再减
                auto *instruction1 = buildFactory->genInstruction(mulExp, InstructionType::Div, true);

                use(leftMulInstruction, instruction1, 0);
                use(rightUnaryInstruction, instruction1, 1);

                auto *instruction2 = buildFactory->genInstruction(mulExp, InstructionType::Mul, true);
                use(rightUnaryInstruction, instruction2, 0);
                use(instruction1, instruction2, 1);

                auto *instruction3 = buildFactory->genInstruction(mulExp, InstructionType::Sub, true);
                use(leftMulInstruction, instruction3, 0);
                use(instruction2, instruction3, 1);

                *mulInstruction = instruction3;

            } else {
                *mulInstruction = buildFactory->genInstruction(mulExp, instructionType, true);
                use(leftMulInstruction, ((Instruction *) (*mulInstruction)), 0);
                use(rightUnaryInstruction, ((Instruction *) (*mulInstruction)), 1);
            }

        }
    }
    return -114514;
}

std::vector<Instruction *> brs;
std::vector<Instruction *> brs_;
std::vector<Instruction *> break_brs;
int inFor = 0;

void Visitor::handleStmt(Node *stmt) {
    if (stmt->getType() == 5) {
        // 是return语句
        Value *expInstruction = nullptr;
        for (auto *child: stmt->children) {
            // 只可能是exp
            handleExp(child, &expInstruction, false);
            // 需要得到装着返回值的寄存器号 那是一个 Instruction
        }
        Instruction *instruction = buildFactory->genInstruction(stmt, InstructionType::Ret, false);
        use(expInstruction, instruction, 0);
        // ret 语句中只会用到一个其他的寄存器号
        // ret 语句不需要加入符号表
        // 返回一个值 或 void 这个值来自于 handleExp
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
        handleLVal(stmt->children[0], &lVal);
        Value *alloca = ((User *) lVal)->operands[0]->value;
        auto *call = buildFactory->genInstruction(stmt, InstructionType::Call, true);
        auto *getint = symbolTable->getSymbol("getint", true, true)->value;
        use(getint, call, 0);

        auto *store = buildFactory->genInstruction(stmt, InstructionType::Store, false);
        use(call, store, 0);
        use(alloca, store, 1);
    } else if (stmt->getType() == 7) {
        // printf
        int j = 0;
        std::string str = stmt->getStr();
        vector<Value *> values;
        for (auto *child: stmt->children) {
            Value *value = nullptr;
            handleExp(child, &value, false);
            values.push_back(value);
        }
        for (int i = 1; i < str.size() - 1; ++i) {
            if (str[i] == '%' && str[i + 1] == 'd') {
                auto *call = buildFactory->genInstruction(stmt, InstructionType::Call, false);
                auto *putint = symbolTable->getSymbol("putint", true, true)->value;
                use(putint, call, 0);
                use(values[j], ((Instruction *) call), 0);
                j++;
                i++;
            } else if (str[i] == '\\' && str[i + 1] == 'n') {
                auto *Const = buildFactory->genConst(stmt, (int) '\n');
                auto *call = buildFactory->genInstruction(stmt, InstructionType::Call, false);
                auto *putch = symbolTable->getSymbol("putch", true, true)->value;
                use(putch, call, 0);
                use(Const, ((Instruction *) call), 0);
                j++;
                i++;
            } else {
                auto *Const = buildFactory->genConst(stmt, (int) str[i]);
                auto *call = buildFactory->genInstruction(stmt, InstructionType::Call, false);
                auto *putch = symbolTable->getSymbol("putch", true, true)->value;
                use(putch, call, 0);
                use(Const, ((Instruction *) call), 0);
            }
        }
    } else if (stmt->getType() == 0) {
        if (!stmt->children.empty()) {
            if (stmt->children[0]->getNodeType() == NodeType::Block) { // 是 block
                symbolTable->createSymbolTable();
                handleBlock(stmt->children[0]);
            } else if (stmt->children[0]->getNodeType() == NodeType::LVal) {
                // LVal = Exp
                Value *lValInstruction = nullptr;
                handleLVal(stmt->children[0], &lValInstruction);
                // 得到的其实是一个 load 指令 他的operand才是alloc
                // 生成一个store指令
                if (lValInstruction->valueType == ValueType::Instruction) {
                    Value *allocInstruction = ((Instruction *) lValInstruction)->operands[0]->value;

                    Value *expInstruction = nullptr;
                    handleExp(stmt->children[1], &expInstruction, false);

                    Instruction *storeInstruction = buildFactory->genInstruction(stmt, InstructionType::Store, false);
                    // 添加use
                    use(expInstruction, storeInstruction, 0);
                    use(allocInstruction, storeInstruction, 1);
                }
            } else {
                if (!stmt->children.empty()) {
                    Value *value;
                    handleExp(stmt->children[0], &value, false);
                }
            }
        }
    } else if (stmt->getType() == 1) {
        // if
        // 进入条件判断的跳转
        auto *br0 = buildFactory->genInstruction(nullptr, InstructionType::Br, false);

        buildFactory->genBasicBlock(nullptr);
        use(buildFactory->curBasicBlock, br0, 0);
        Value *cond = nullptr;
        auto *br = handleCond(stmt->children[0], &cond); // 产生两条指令 icmp 和 br
        handleStmt(stmt->children[1]);

        // 跳出if语句的跳转
        auto *br1 = buildFactory->genInstruction(nullptr, InstructionType::Br, false);

        buildFactory->genBasicBlock(nullptr);

        // 条件语句不成立，不执行if语句的label2
        for (auto *child: brs) {
            use(buildFactory->curBasicBlock, child, 2);
        }

        if (stmt->children.size() > 2) {
            handleStmt(stmt->children[2]); // 如果有else的话
            auto *br2 = buildFactory->genInstruction(nullptr, InstructionType::Br, false);

            buildFactory->genBasicBlock(nullptr);
            use(buildFactory->curBasicBlock, br1, 0);
            use(buildFactory->curBasicBlock, br2, 0);
        } else {
            use(buildFactory->curBasicBlock, br1, 0);
        }
    } else if (stmt->getType() == 2) {
        // for
        inFor++;
        int t = brs.size();
        int b_t = break_brs.size();
        Stmt *forStmt = (Stmt *) stmt;
        if (forStmt->forStmt1 != nullptr) {
            handleForStmt(forStmt->forStmt1);
        }
        auto *br0 = buildFactory->genInstruction(nullptr, InstructionType::Br, false);

        auto *beforCondLabel = buildFactory->genBasicBlock(nullptr);
        use(buildFactory->curBasicBlock, br0, 0);
        Value *cond = nullptr;
        Instruction *br = nullptr;
        if (forStmt->cond != nullptr) {
            br = handleCond(forStmt->cond, &cond);
        }

        handleStmt(forStmt->children[0]);
        if (forStmt->forStmt2 != nullptr) {
            handleForStmt(forStmt->forStmt2);
        }

        auto *endBr = buildFactory->genInstruction(nullptr, InstructionType::Br, false);
        use(beforCondLabel, endBr, 0);

        buildFactory->genBasicBlock(nullptr);
        // 跳出for循环的位置 break 产生的br跳出的位置

        for (int i = brs.size() - 1; i >= t; --i) {
            use(buildFactory->curBasicBlock, brs[i], 2);
            brs.pop_back();
        }

        if (!break_brs.empty()) {
            //buildFactory->genBasicBlock(nullptr);
            for (int i = break_brs.size() - 1; i >= b_t; --i) {
                use(buildFactory->curBasicBlock, break_brs[i], 0);
                break_brs.pop_back();
            }
        }

        inFor--;
    } else if (stmt->getType() == 4) {
        //continue
        if (inFor) {
            auto *br = buildFactory->genInstruction(nullptr, InstructionType::Br, false);
            brs.push_back(br);
        }
    } else if (stmt->getType() == 3) {
        // break
        if (inFor) {
            auto *br = buildFactory->genInstruction(nullptr, InstructionType::Br, false);
            break_brs.push_back(br);
        }
    }
}


Instruction *Visitor::handleCond(Node *cond, Value **c) {
    brs_.clear();
    Instruction *br = handleLOrExp(cond->children[0]);
    buildFactory->genBasicBlock(nullptr);
    for (auto *child: brs_) {
        use(buildFactory->curBasicBlock, child, 1);
    }
    brs_.clear();
    return br;
    // 生成一条跳转指令，进入条件的判断
}


Instruction *Visitor::handleLOrExp(Node *lOrExp) {
    int t = brs.size();
    if (lOrExp->children.size() == 1) {
        return handleLAndExp(lOrExp->children[0]);
    } else {
//        brs.clear();
        handleLOrExp(lOrExp->children[0]);
        buildFactory->genBasicBlock(nullptr);
        // 现在它们知道label2了
//        for (auto *child: brs) {
//            use(buildFactory->curBasicBlock, child, 2);
//        }
        for (int i = brs.size() - 1; i >= t; --i) {
            use(buildFactory->curBasicBlock, brs[i], 2);
            brs.pop_back();
        }
//        brs.clear();
        return handleLAndExp(lOrExp->children[1]);
    }
}

Instruction *Visitor::handleLAndExp(Node *lAndExp) {
    // 1 && 2
    Instruction *br = nullptr;
    if (lAndExp->children.size() == 1) {
        Value *v = nullptr;
        // 产生新的基本块
        br = handleEqExp(lAndExp->children[0], &v, true);
        brs_.push_back(br);
    } else {
        Value *br1 = handleLAndExp(lAndExp->children[0]);
        brs_.pop_back();
        // 产生新的基本块
        buildFactory->genBasicBlock(nullptr);
        // 在handleAnd中知道label1了 但还不知道label2
        use(buildFactory->curBasicBlock, ((Instruction *) br1), 1);

        Value *v = nullptr;
        br = handleEqExp(lAndExp->children[1], &v, true);
        brs_.push_back(br);
    }
    return br;
}


Instruction *Visitor::handleEqExp(Node *eqExp, Value **eq, bool isBr) {
    if (eqExp->children.size() == 1) {
        Value *rel = nullptr;
        //先不产生add指令
        NOT = -1;
        handleRelExp(eqExp->children[0], &rel);
        if (rel->ty != 32) {
            auto *zext = buildFactory->genInstruction(nullptr, InstructionType::Zext, true);
            use(rel, zext, 0);
            rel = zext;
        }
        *eq = rel;
        if (isBr) {
            InstructionType instructionType = (NOT == -1) ? InstructionType::Ne : InstructionType::Eq;
            auto *ne = buildFactory->genInstruction(nullptr, instructionType, true);
            auto *Const = buildFactory->genConst(nullptr, 0);
            use(Const, ne, 0);
            use((*eq), ne, 1);
            *eq = ne;
        }
    } else if (eqExp->children.size() > 1) {
        Value *leftEq = nullptr;
        Value *righRel = nullptr;
        handleEqExp(eqExp->children[0], &leftEq, false);
        handleRelExp(eqExp->children[1], &righRel);

        InstructionType instructionType = (eqExp->getOp() == 0) ? InstructionType::Eq : InstructionType::Ne;

        if (leftEq->ty != righRel->ty) {
            if (leftEq->ty == 1) {
                auto *zext = buildFactory->genInstruction(nullptr, InstructionType::Zext, true);
                use(leftEq, zext, 0);
                leftEq = zext;
            } else if (righRel->ty == 1) {
                auto *zext = buildFactory->genInstruction(nullptr, InstructionType::Zext, true);
                use(righRel, zext, 0);
                righRel = zext;
            }
        }

        *eq = buildFactory->genInstruction(eqExp, instructionType, true);
        use(leftEq, ((Instruction *) (*eq)), 0);
        use(righRel, ((Instruction *) (*eq)), 0);
    }
    // 这里才是最小的，产生新的br指令,并与使用*eq
    if (isBr) {
        auto *br = buildFactory->genInstruction(nullptr, InstructionType::Br, false);
        use((*eq), br, 0);
        // 此时的br还不知道自己要跳到哪里，但回到handleAnd中将会知道label1，即成立时要跳到哪里
        brs.push_back(br);
        // 先将它们装进一个向量里，回到handleOr中将会知道label2，即不成立时会跳到哪里
        return br;
    } else {
        return nullptr;
    }

}

void Visitor::handleRelExp(Node *relExp, Value **rel) {
    if (relExp->children.size() == 1) {
        Value *add = nullptr;
        handleAddExp(relExp->children[0], &add, false);
        *rel = add;
    } else if (relExp->children.size() > 1) {
        //要产生add指令了
        Value *leftRel = nullptr;
        Value *righAdd = nullptr;
        handleRelExp(relExp->children[0], &leftRel);
        handleAddExp(relExp->children[1], &righAdd, false);

        InstructionType instructionType = (relExp->getOp() == 1) ? InstructionType::Ge :
                                          (relExp->getOp() == 0) ? InstructionType::Gt :
                                          (relExp->getOp() == 2) ? InstructionType::Lt : InstructionType::Le;

        if (leftRel->ty != righAdd->ty) {
            if (leftRel->ty == 1) {
                auto *zext = buildFactory->genInstruction(nullptr, InstructionType::Zext, true);
                use(leftRel, zext, 0);
                leftRel = zext;
            } else if (righAdd->ty == 1) {
                auto *zext = buildFactory->genInstruction(nullptr, InstructionType::Zext, true);
                use(righAdd, zext, 0);
                righAdd = zext;
            }
        }

        *rel = buildFactory->genInstruction(relExp, instructionType, true);
        use(leftRel, ((Instruction *) (*rel)), 0);
        use(righAdd, ((Instruction *) (*rel)), 1);

    }
}

int Visitor::handleAddExp(Node *addExp, Value **addInstruction, bool isGlobal) {
    if (isGlobal) {
        // addIns将会是一个Const
        if (addExp->children.size() == 1) {
            handleMulExp(addExp->children[0], addInstruction, isGlobal);
        } else {
            Value *add1 = nullptr, *add2 = nullptr;
            handleAddExp(addExp->children[0], &add1, isGlobal);
            handleMulExp(addExp->children[1], &add2, isGlobal);
            int a1 = atoi(add1->getName().c_str());
            int a2 = atoi(add2->getName().c_str());
            int val = (addExp->getOp() == 1) ? (a1 - a2) : (a1 + a2);
            *addInstruction = buildFactory->genConst(nullptr, val);
        }
    } else {
        if (addExp->children.size() == 1) {
            Value *mulInstruction = nullptr;
            //先不产生add指令
            handleMulExp(addExp->children[0], &mulInstruction, isGlobal);
            *addInstruction = mulInstruction;
        } else if (addExp->children.size() > 1) {
            //要产生add指令了
            Value *leftAddInstruction = nullptr;
            Value *rightMulInstruction = nullptr;
            handleAddExp(addExp->children[0], &leftAddInstruction, isGlobal);
            handleMulExp(addExp->children[1], &rightMulInstruction, isGlobal);

            InstructionType instructionType = (addExp->getOp() == 0) ? InstructionType::Add : InstructionType::Sub;

            *addInstruction = buildFactory->genInstruction(addExp, instructionType, true);
            use(leftAddInstruction, ((Instruction *) (*addInstruction)), 0);
            use(rightMulInstruction, ((Instruction *) (*addInstruction)), 1);
        }
    }
    return -114514;
}

int Visitor::handleConstExp(Node *constExp, Value **constExpInstruction, bool isGlobal) {
    if (isGlobal) {
        return handleAddExp(constExp->children[0], constExpInstruction, isGlobal);
    }
    Value *addInstruction = nullptr;
    for (auto *child: constExp->children) {
        if (child->nodeType == NodeType::AddExp) {
            handleAddExp(child, &addInstruction, false);
        }
    }
    *constExpInstruction = addInstruction;
    return -114514;
}

Visitor::Visitor() {
    this->buildFactory = new BuildFactory();
    this->symbolTable = new SymbolTable();
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