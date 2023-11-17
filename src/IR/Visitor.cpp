////
//// Created by lyh on 11/9/2023.
//// build the symbol table and generate code
//
//#include "Visitor.h"
//
//// #define ERROR_CHECK
//
//#ifdef ERROR_CHECK
//
//struct Error
//{
//    int line;
//    char c;
//};
//extern Error errors[1000];
//extern int e;
//
//#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}
//
//#endif
//
//extern SymbolTable symbolTable;
//extern std::ofstream c_ofs;
//int TY = 1;
//int REG = 1;
//#define generateCode(code) c_ofs << code
//
//void Visitor::handleCompUnit(std::unique_ptr<Node> node) {
//    generateCode("declare i32 @getint()" << endl);
//    generateCode("declare void @putint(i32)" << endl);
//    generateCode("declare void @putch(i32)" << endl);
//    generateCode("declare void @putstr(i8*)" << endl);
//    for (auto child : node->children) {
//        if (child->getNodeType() == NodeType::Decl) {
//            handleDecl(child, true);
//        } else if (child->getNodeType() == NodeType::FuncDef) {
//            handleFuncDef(child);
//        } else if (child->getNodeType() == NodeType::MainFuncDef) {
//            handleMainFuncDef(child);
//        }
//    }
//}
//
//void Visitor::handleVarDef(std::unique_ptr<Node>varDef, bool isGlobal) {
//    string word = varDef->getWord();
//    Symbol *symbol = new Symbol(0, word, false, nullptr);
//    if (varDef->hasEqual()) {
//        symbol->type += varDef->children.size() - 1;
//    } else {
//        symbol->type += varDef->children.size();
//    }
//
//    int des = TY, src;
//    if (!isGlobal) {
//        symbol->ty = des;
//        TY++;
//        generateCode("%" << des << " = alloca i32" << endl);
//    } else {
//        symbol->global = true;
//    }
//
//    int initVal;
//
//    for (auto *child : varDef->children) {
//        if (child->getNodeType() == NodeType::InitVal) {
//            initVal = handleInitVal(child, isGlobal, &src);
//        } else if (child->getNodeType() == NodeType::ConstExp) {
//            handleConstExp(child, isGlobal, &src);
//        }
//    }
//
//    if (isGlobal) {
//        if (varDef->hasEqual()) {
//            generateCode("@" << word << " = dso_local global i32 " << initVal << endl);
//        } else {
//            generateCode("@" << word << " = dso_local global i32 " << endl);
//        }
//    } else {
//        if (varDef->hasEqual())
//            generateCode("store i32 "
//                                 << "%" << src << ", "
//                                 << "i32* "
//                                 << "%" << des << endl);
//    }
//
//    symbolTable.addSymbol(symbol, varDef->lineNum);
//}
//
//void Visitor::handleConstDef(std::unique_ptr<Node>constDef, bool isGlobal) {
//    string word = constDef->getWord();
//    Symbol *symbol = new Symbol(0, word, true, nullptr);
//    symbol->type += constDef->children.size() - 1;
//    // domention of def
//
//    int des = TY, src;
//    if (!isGlobal) {
//        symbol->ty = des;
//        TY++;
//        generateCode("%" << des << " = alloca i32" << endl);
//    } else {
//        symbol->global = true;
//    }
//
//    int initVal = -1;
//    for (auto *child : constDef->children) {
//        if (child->getNodeType() == NodeType::ConstInitVal) {
//            initVal = handleConstInitVal(child, isGlobal);
//        } else if (child->getNodeType() == NodeType::ConstExp) {
//            handleConstExp(child, isGlobal, &src);
//        }
//    }
//    if (isGlobal) {
//        generateCode("@" << word << " = dso_local constant i32 " << initVal << endl);
//        symbol->val = initVal;
//    } else {
//        generateCode("store i32 "
//                             << "%" << src << ", "
//                             << "i32* "
//                             << "%" << des << endl);
//    }
//
//    symbolTable.addSymbol(symbol, constDef->lineNum);
//}
//
//int Visitor::handleFuncFParam(std::unique_ptr<Node>funcFParam, string *code) {
//    string word = funcFParam->getWord();
//    Symbol *symbol = new Symbol(funcFParam->getType(), word, false, nullptr);
//    symbolTable.addSymbol(symbol, funcFParam->lineNum);
//    symbol->param = true;
//    symbol->ty = TY;
//    *code += "i32 %" + to_string(TY) + ", ";
//    TY++;
//    return funcFParam->getType();
//}
//
//void Visitor::handleFuncDef(std::unique_ptr<Node>funcDef) {
//    int retType = funcDef->children[0]->getType();
//
//    int paramNum = 0;
//    Func *func = new Func(retType, paramNum);
//
//    string word = funcDef->getWord();
//    Symbol *symbol = new Symbol(-1, word, false, func);
//
//    symbolTable.addSymbol(symbol, funcDef->lineNum);
//
//    symbolTable.createSymbolTable(); // create new symbol table
//
//    int oldTY = TY;
//    TY = 0;
//    generateCode("define dso_local i32 @" << symbol->word << "(");
//
//    for (auto *child : funcDef->children) {
//        if (child->getNodeType() == NodeType::FuncFParams) {
//            func->paramNum += handleFuncFParams(child, &func->paramTypeList);
//        } else if (child->getNodeType() == NodeType::FuncType) {
//            func->retype = handleFuncType(child);
//        } else if (child->getNodeType() == NodeType::Block) {
//            generateCode("){" << endl);
//            TY++;
//            handleBlock(child, retType, false);
//        }
//    }
//    if (func->retype == 1) {
//        generateCode("ret void" << endl);
//    }
//    generateCode("}" << endl);
//    TY = oldTY;
//}
//
//void Visitor::handleDecl(std::unique_ptr<Node>funcFParam, bool isGlobal) {
//    for (auto *child : funcFParam->children) {
//        if (child->getNodeType() == NodeType::ConstDecl) {
//            handleConstDecl(child, isGlobal);
//        } else if (child->getNodeType() == NodeType::VarDecl) {
//            handleVarDecl(child, isGlobal);
//        }
//    }
//}
//
//void Visitor::handleMainFuncDef(std::unique_ptr<Node>mainFuncFParam) {
//    generateCode("define dso_local i32 @main() {" << endl);
//    for (auto *child : mainFuncFParam->children) {
//        symbolTable.createSymbolTable();
//        handleBlock(child, 0, false);
//    }
//    generateCode("}" << endl);
//}
//
//void Visitor::handleConstDecl(std::unique_ptr<Node>constDecl, bool isGlobal) {
//    for (auto *child : constDecl->children) {
//        if (child->getNodeType() == NodeType::BType) {
//            handleBType(child);
//        } else if (child->getNodeType() == NodeType::ConstDef) {
//            handleConstDef(child, isGlobal);
//        }
//    }
//}
//
//void Visitor::handleVarDecl(std::unique_ptr<Node>varDecl, bool isGlobal) {
//    for (auto *child : varDecl->children) {
//        if (child->getNodeType() == NodeType::BType) {
//            handleBType(child);
//        } else if (child->getNodeType() == NodeType::VarDef) {
//            handleVarDef(child, isGlobal);
//        }
//    }
//}
//
//void Visitor::handleBType(std::unique_ptr<Node>BType) {
//    return;
//}
//
//int Visitor::handleConstInitVal(std::unique_ptr<Node>constInitVal, bool isGlobal) {
//    for (auto *child : constInitVal->children) {
//        if (child->getNodeType() == NodeType::ConstExp) {
//            int c;
//            return handleConstExp(child, isGlobal, &c);
//        } else if (child->getNodeType() == NodeType::ConstInitVal) {
//            return handleConstInitVal(child, isGlobal);
//        }
//    }
//    return -1;
//}
//
//int Visitor::handleConstExp(std::unique_ptr<Node>constExp, bool isGlobal, int *c) {
//    int initVal;
//    for (auto *child : constExp->children) {
//        if (child->getNodeType() == NodeType::AddExp) {
//            handleAddExp(child, c, &initVal, isGlobal);
//        }
//    }
//    return initVal;
//}
//
//int Visitor::handleInitVal(std::unique_ptr<Node>initVal, bool isGlobal, int *c) {
//    int val;
//    for (auto *child : initVal->children) {
//        if (child->getNodeType() == NodeType::Exp) {
//            handleExp(child, c, &val, isGlobal);
//        } else if (child->getNodeType() == NodeType::InitVal) {
//            handleInitVal(child, isGlobal, c);
//        }
//    }
//    return val;
//}
//
//int Visitor::handleExp(std::unique_ptr<Node>exp, int *c, int *val, bool isGlobal) {
//    int ret;
//    for (auto *child : exp->children) {
//        ret = handleAddExp(child, c, val, isGlobal);
//    }
//    return ret;
//}
//
//int Visitor::handleFuncFParams(std::unique_ptr<Node>funcFParams, vector<int> *paramTypeList) {
//    int num = 0;
//    string code = "";
//    for (auto *child : funcFParams->children) {
//        if (child->getNodeType() == NodeType::FuncFParam) {
//            num++;
//            paramTypeList->push_back(handleFuncFParam(child, &code));
//        }
//    }
//    code = code.substr(0, code.size() - 2);
//    generateCode(code);
//    return num;
//}
//
//int Visitor::handleFuncType(std::unique_ptr<Node>funcType) {
//    return funcType->getType();
//}
//
//void Visitor::handleBlock(std::unique_ptr<Node>block, int isNoRet, bool isLoop) {
//    for (auto *child : block->children) {
//        if (child->getNodeType() == NodeType::BlockItem) {
//            handleBlockItem(child, isNoRet, isLoop);
//        }
//    }
//#ifdef ERROR_CHECK
//    if (!isNoRet && (block->children.empty() || block->children[block->children.size() - 1]->children[0]->getType() != 5))
//    {
//        printError(block->getLastLine(), "g");
//    }
//#endif
//    symbolTable.deleteSymbolTable();
//}
//
//void Visitor::handleBlockItem(std::unique_ptr<Node>blockItem, int isNoRet, bool isLoop) {
//    for (auto *child : blockItem->children) {
//        if (child->getNodeType() == NodeType::Decl) {
//            handleDecl(child, false);
//        } else if (child->getNodeType() == NodeType::Stmt) {
//            handleStmt(child, isNoRet, isLoop);
//        }
//    }
//}
//
//void Visitor::handleStmt(std::unique_ptr<Node>stmt, int isNoRet, bool isLoop) {
//    if (stmt->getType() == 0) {
//        // normal
//        bool changeLVal = false;
//        Symbol *symbol = nullptr;
//        if (stmt->children.size() == 1) {
//            if (stmt->children[0]->getNodeType() == NodeType::Block) {
//                symbolTable.createSymbolTable();
//                handleBlock(stmt->children[0], isNoRet, isLoop);
//            } else if (stmt->children[0]->getNodeType() == NodeType::Stmt) {
//                handleStmt(stmt->children[0], isNoRet, isLoop);
//            }
//        } else if (stmt->children.size() == 2) {
//#ifdef ERROR_CHECK
//            if (changeLVal && symbol != nullptr && symbol->con)
//            {
//                printError(stmt->lineNum, "h");
//            }
//#endif
//            int c;
//            int foo;
//            handleExp(stmt->children[1], &c, &foo, false);
//            Symbol *symbol1 = symbolTable.getSymbol(stmt->children[0]->getWord(), false, true);
//            if (symbol1->global) {
//                generateCode("store i32 "
//                                     << "%" << c << ", "
//                                     << "i32* @" << symbol1->word << endl);
//            } else {
//                generateCode("store i32 "
//                                     << "%" << c << ", "
//                                     << "i32 %" << symbol1->ty << endl);
//            }
//        }
//    } else if (stmt->getType() == 1) {
//        // if
//        for (auto *child : stmt->children) {
//            if (child->getNodeType() == NodeType::Cond) {
//                handleCond(child);
//            } else if (child->getNodeType() == NodeType::Stmt) {
//                handleStmt(child, isNoRet, false);
//            } // need to conisder else condition
//        }
//    } else if (stmt->getType() == 2) {
//        // for
//        for (auto *child : stmt->children) {
//            if (child->getNodeType() == NodeType::ForStmt) {
//                handleForStmt(child);
//            } else if (child->getNodeType() == NodeType::Cond) {
//                handleCond(child);
//            } else if (child->getNodeType() == NodeType::Stmt) {
//                handleStmt(child, isNoRet, true);
//            }
//        } // need to distinguish different ForStmt
//    } else if (stmt->getType() == 3) {
//        // break
//        // generate branch code ??
//#ifdef ERROR_CHECK
//        if (!isLoop)
//        {
//            printError(stmt->lineNum, "m");
//        }
//#endif
//    } else if (stmt->getType() == 4) {
//        // continue
//        // generate branch code ??
//#ifdef ERROR_CHECK
//        if (!isLoop)
//        {
//            printError(stmt->lineNum, "m");
//        }
//#endif
//    } else if (stmt->getType() == 5) {
//        // return
//        // generate branch code ?? and fill code??
//        for (auto *child : stmt->children) {
//#ifdef ERROR_CHECK
//            if (isNoRet)
//            {
//                printError(stmt->lineNum, "f");
//            }
//#endif
//            if (child->getNodeType() == NodeType::Exp) {
//                int c;
//                int foo;
//                handleExp(child, &c, &foo, false);
//                generateCode("ret i32 \%" << c << endl);
//            }
//        }
//    } else if (stmt->getType() == 6) {
//        // getint
//        for (auto *child : stmt->children) {
//            if (child->getNodeType() == NodeType::LVal) {
//                Symbol *symbol = symbolTable.getSymbol(child->getWord(), false, true);
//                if (symbol->global) {
//                    int ty1 = TY++;
//                    generateCode("%" << ty1 << " = load i32, i32* "
//                                     << "%" << symbol->word << endl);
//                    int ty2 = TY++;
//                    generateCode("%" << ty2 << " = call i32 @getint()"
//                                     << endl);
//                    generateCode("store i32 "
//                                         << "%" << ty2 << ", "
//                                         << "i32 "
//                                         << "%" << symbol->word << endl);
//                } else {
//                    int ty = symbol->ty;
//                    int ty1 = TY++;
//                    generateCode("%" << ty1 << " = load i32, i32* "
//                                     << "%" << ty << endl);
//                    int ty2 = TY++;
//                    generateCode("%" << ty2 << " = "
//                                     << "call i32 @getint()" << endl);
//                    generateCode("store i32 "
//                                         << "%" << ty2 << ", "
//                                         << "i32 "
//                                         << "%" << ty << endl);
//                }
//#ifdef ERROR_CHECK
//                Symbol *symbol = symbolTable.getSymbol(child->getWord(), false, true);
//                if (symbol != nullptr && symbol->con)
//                {
//                    printError(stmt->lineNum, "h");
//                }
//#endif
//            }
//        }
//    } else if (stmt->getType() == 7) {
//        // printf
//        string str = stmt->getStr();
//        vector<int> vars;
//        int cnt = 0;
//        for (auto *child : stmt->children) {
//            int ty;
//            int val;
//            handleExp(child, &ty, &val, false);
//            vars.push_back(ty);
//            // generateCode("%" << TY++ << " = load i32, i32* %" << ty << endl);
//        }
//        int n = 0;
//        for (int i = 1; i < str.size() - 2; i++) {
//            if (str[i] == '%' && str[i + 1] == 'd') {
//                generateCode("call void @putint(i32 %" << vars[cnt++] << ')' << endl);
//                i++;
//            } else {
//                generateCode("call void @putch(i32 " << int(str[i]) << ')' << endl);
//            }
//        }
//#ifdef ERROR_CHECK
//        int n = 0;
//        for (int i = 0; i < str.size() - 1; i++)
//        {
//            if (str[i] == '%' && str[i + 1] == 'd')
//            {
//                n++;
//            }
//        }
//        if (stmt->children.size() != n)
//        {
//            printError(stmt->lineNum, "l");
//        }
//#endif
//    }
//}
//
//void Visitor::handleForStmt(std::unique_ptr<Node>forStmt) {
//    for (auto *child : forStmt->children) {
//        if (child->getNodeType() == NodeType::LVal) {
//            int foo;
//            int c;
//            handleLVal(child, &foo, &c, false);
//        } else if (child->getNodeType() == NodeType::Exp) {
//            int c;
//            int foo;
//            handleExp(child, &c, &foo, false);
//        }
//    }
//}
//
//void Visitor::handleCond(std::unique_ptr<Node>cond) {
//    for (auto *child : cond->children) {
//        if (child->getNodeType() == NodeType::LOrExp) {
//            handleLOrExp(child);
//        }
//    }
//}
//
//int Visitor::handleLVal(std::unique_ptr<Node>lVal, int *initVal, int *c, bool isGlobal) {
//    int ret;
//    Symbol *symbol = symbolTable.getSymbol(lVal->getWord(), false, true);
//    ret = (symbol == nullptr) ? 0 : symbol->type;
//    if (symbol != nullptr && symbol->type != -1) {
//        *initVal = symbol->val;
//    }
//    if (symbol != nullptr && symbol->ty != -1 && !symbol->param) {
//        *c = (isGlobal) ? TY : TY++;
//        generateCode("%" << *c << " = "
//                         << "load i32, "
//                         << "i32* %" << symbol->ty << endl);
//    }
//    if (symbol != nullptr && symbol->global && !isGlobal) {
//        *c = TY++;
//        generateCode("%" << *c << " = "
//                         << "load i32, "
//                         << "i32* @" << symbol->word << endl);
//    }
//    if (symbol != nullptr && symbol->param && symbol->ty != -1) {
//        symbol->param = false;
//        *c = TY++;
//        generateCode("%" << *c << " = alloca i32" << endl);
//        generateCode("store i32 %" << symbol->ty << ", "
//                                   << "i32* %" << *c << endl);
//        symbol->ty = *c;
//        *c = TY++;
//        generateCode("%" << *c << " = "
//                         << "load i32, i32* %" << symbol->ty << endl);
//    }
//    // need to consider if exsiting lVal
//#ifdef ERROR_CHECK
//    if (Symbol == nullptr)
//    {
//        printError(lVal->lineNum, "c");
//    }
//#endif
//    for (auto *child : lVal->children) {
//        if (child->getNodeType() == NodeType::Exp) {
//            ret = (ret > 0) ? ret - 1 : ret;
//            int foo;
//            handleExp(child, c, &foo, false);
//        }
//    }
//    return ret;
//}
//
//int Visitor::handlePrimaryExp(std::unique_ptr<Node>primaryExp, int *c, int pos, int *initVal, bool isGlobal) {
//    int ret = -2;
//    for (auto *child : primaryExp->children) {
//        if (child->getNodeType() == NodeType::LVal) {
//            ret = handleLVal(child, initVal, c, isGlobal);
//        } else if (child->getNodeType() == NodeType::Number) {
//            ret = handleNumber(child, c, pos, initVal, isGlobal);
//        } else if (child->getNodeType() == NodeType::Exp) {
//            ret = handleExp(child, c, initVal, isGlobal);
//        }
//    }
//    return ret;
//}
//
//int Visitor::handleNumber(std::unique_ptr<Node>number, int *c, int pos, int *initVal, bool isGlobal) {
//    if (!isGlobal) {
//        *c = TY++;
//    } else {
//        *c = TY;
//    }
//    if (pos == 1) {
//        if (!isGlobal)
//            generateCode("%" << *c << " = add i32 " << 0 << ", " << number->getVal() << endl);
//    } else {
//        if (!isGlobal)
//            generateCode("%" << *c << " = sub i32 " << 0 << ", " << number->getVal() << endl);
//    }
//    *initVal = number->getVal() * pos;
//    // generateCode(number->getVal() << " ");
//    return 0; // is int
//    // generate code
//}
//
//int Visitor::handleUnaryExp(std::unique_ptr<Node>unaryExp, int *c, int pos, int *initVal, bool isGlobal) {
//    int ret = 0;
//    if (!unaryExp->getWord().empty()) { // is Ident '(' [FuncRParams] ')'
//        Symbol *symbol = symbolTable.getSymbol(unaryExp->getWord(), true, true);
//        if (symbol != nullptr) {
//            ret = symbol->func->retype;
//        } else {
//            ret = 0;
//        }
//#ifdef ERROR_CHECK
//        if (symbol == nullptr)
//        {
//            printError(unaryExp->lineNum, "c");
//        }
//#endif
//    }
//    for (auto *child : unaryExp->children) {
//        if (child->getNodeType() == NodeType::PrimaryExp) {
//            ret = handlePrimaryExp(child, c, pos, initVal, isGlobal);
//        } else if (child->getNodeType() == NodeType::UnaryOp) {
//            if (handleUnaryOp(child) == 1) {
//                pos = -pos;
//            }
//        } else if (child->getNodeType() == NodeType::UnaryExp) {
//            ret = handleUnaryExp(child, c, pos, initVal, isGlobal);
//        } else if (child->getNodeType() == NodeType::FuncRParams) {
//            Symbol *funcSymbol = symbolTable.getSymbol(unaryExp->getWord(), true, true);
//#ifdef ERROR_CHECK
//            if (funcSymbol && funcRParamsNum != funcSymbol->func->paramNum)
//            {
//                printError(unaryExp->lineNum, "d");
//            }
//#endif
//            int ty;
//            string code = "call i32 @" + funcSymbol->word + "(";
//            handleFuncRParams(child, funcSymbol, &code);
//            code = code.substr(0, code.size() - 2);
//            code += ")";
//            *c = TY++;
//            generateCode("%" << *c << " = " << code << endl);
//        }
//    }
//    return ret;
//}
//
//int Visitor::handleUnaryOp(std::unique_ptr<Node>unaryOp) {
//    return unaryOp->getType(); // 0 + 1 - 2 !
//}
//
//void Visitor::handleFuncRParams(std::unique_ptr<Node>funcRParams, Symbol *funcSymbol, string *code) {
//    // 对调用的函数进行参数处理 funcSymbol是被调用函数的符号表项
//    int i = 0;
//    for (auto *child : funcRParams->children) {
//        if (child->getNodeType() == NodeType::Exp) {
//            int foo;
//            int c;
//            int t = handleExp(child, &c, &foo, false); // 返回实参的类型
//            *code += "i32 %" + to_string(c) + ", ";
//#ifdef ERROR_CHECK
//            if (funcSymbol != nullptr)
//            {
//                if (i > funcSymbol->func->paramNum)
//                {
//                    std::cout << "too much" << std::endl;
//                }
//                if (!funcSymbol->func->paramTypeList.empty() && t != funcSymbol->func->paramTypeList[i++])
//                {
//                    printError(funcRParams->lineNum, "e");
//                } // 逐个实参形参类型对比
//            }
//#endif
//        }
//    }
//}
//
//int Visitor::handleMulExp(std::unique_ptr<Node>mulExp, int *c, int *initVal, bool isGlobal) {
//    int ret = 0;
//    // mul div mod
//    int c1 = -1, c2 = -1;
//    int unary, mul;
//    for (auto *child : mulExp->children) {
//        if (child->getNodeType() == NodeType::UnaryExp) {
//            ret = handleUnaryExp(child, &c2, 1, &unary, isGlobal);
//        } else if (child->getNodeType() == NodeType::MulExp) {
//            ret = handleMulExp(child, &c1, &mul, isGlobal);
//            // 0 * 1 / 2 %
//        }
//    }
//
//    if (mulExp->getOp() == 0) {
//        *initVal = mul * unary;
//        *c = (isGlobal) ? TY : TY++;
//        if (!isGlobal)
//            generateCode("%" << *c << " = mul i32 "
//                             << "%" << c1 << ", "
//                             << "%" << c2 << endl);
//    } else if (mulExp->getOp() == 1) {
//        *initVal = mul / unary;
//        *c = (isGlobal) ? TY : TY++;
//        if (!isGlobal)
//            generateCode("%" << *c << " = div i32 "
//                             << "%" << c1 << ", "
//                             << "%" << c2 << endl);
//    } else if (mulExp->getOp() == 2) {
//        *initVal = mul % unary;
//        *c = (isGlobal) ? TY : TY++;
//        if (!isGlobal)
//            generateCode("%" << *c << " = mod i32 "
//                             << "%" << c1 << ", "
//                             << "%" << c2 << endl);
//    } else {
//        *initVal = unary;
//        *c = c2;
//    }
//
//    return ret;
//}
//
//int Visitor::handleAddExp(std::unique_ptr<Node>addExp, int *c, int *initVal, bool isGlobal) {
//    // add sub
//    int ret = 0;
//    int c1 = -1, c2 = -1;
//    int add, mul;
//    for (auto *child : addExp->children) {
//        if (child->getNodeType() == NodeType::MulExp) {
//            ret = handleMulExp(child, &c2, &mul, isGlobal);
//        } else if (child->getNodeType() == NodeType::AddExp) {
//            ret = handleAddExp(child, &c1, &add, isGlobal);
//        }
//        // 0 + 1 -
//    }
//    if (addExp->getOp() == 0) {
//        *initVal = add + mul;
//        *c = (isGlobal) ? TY : TY++;
//        if (!isGlobal)
//            generateCode("%" << *c << " = add i32 "
//                             << "%" << c1 << ", "
//                             << "%" << c2 << endl);
//    } else if (addExp->getOp() == 1) {
//        *initVal = add - mul;
//        *c = (isGlobal) ? TY : TY++;
//        if (!isGlobal)
//            generateCode("%" << *c << " = sub i32 "
//                             << "%" << c1 << ", "
//                             << "%" << c2 << endl);
//    } else {
//        *initVal = mul;
//        *c = c2;
//    }
//    return ret;
//}
//
//void Visitor::handleRelExp(std::unique_ptr<Node>relExp) {
//    // lt gt le ge
//    int c;
//    for (auto *child : relExp->children) {
//        if (child->getNodeType() == NodeType::AddExp) {
//            int foo;
//            handleAddExp(child, &c, &foo, false);
//        } else if (child->getNodeType() == NodeType::RelExp) {
//            handleRelExp(child);
//        }
//    }
//}
//
//void Visitor::handleEqExp(std::unique_ptr<Node>eqExp) {
//    // eq ne
//    for (auto *child : eqExp->children) {
//        if (child->getNodeType() == NodeType::RelExp) {
//            handleRelExp(child);
//        } else if (child->getNodeType() == NodeType::EqExp) {
//            handleEqExp(child);
//        }
//    }
//}
//
//void Visitor::handleLAndExp(std::unique_ptr<Node>lAndExp) {
//    for (auto *child : lAndExp->children) {
//        if (child->getNodeType() == NodeType::EqExp) {
//            handleEqExp(child);
//        } else if (child->getNodeType() == NodeType::LAndExp) {
//            handleLAndExp(child);
//        }
//    }
//}
//
//void Visitor::handleLOrExp(std::unique_ptr<Node>lOrExp) {
//    for (auto *child : lOrExp->children) {
//        if (child->getNodeType() == NodeType::LAndExp) {
//            handleLAndExp(child);
//        } else if (child->getNodeType() == NodeType::LOrExp) {
//            handleLOrExp(child);
//        }
//    }
//}
