//
// Created by lyh on 11/9/2023.
// build the symbol table and generate code

#include "Visitor.h"

//#define ERROR_CHECK

#ifdef ERROR_CHECK

struct Error {
    int line;
    char c;
};
extern Error errors[1000];
extern int e;

#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}

#endif

extern SymbolTable symbolTable;
extern ofstream c_ofs;
#define generateCode(code) c_ofs << code << std::endl

void Visitor::handleCompUnit(Node* node) {
    for (auto* child : node->children) {
        if (child->getNodeType() == NodeType::Decl) {
            handleDecl(child);
        } else if (child->getNodeType() == NodeType::FuncDef) {
            handleFuncDef(child);
        } else if (child->getNodeType() == NodeType::MainFuncDef) {
            handleMainFuncDef(child);
        }
    }
}

void Visitor::handleVarDef(Node *varDef) {
    string word = varDef->getWord();
    Symbol* symbol = new Symbol(0, word, false, nullptr);
    if (varDef->hasEqual()) {
        symbol->type += varDef->children.size() - 1;
    } else {
        symbol->type += varDef->children.size();
    }
    symbolTable.addSymbol(symbol, varDef->lineNum);

    for (auto* child : varDef->children) {
        if (child->getNodeType() == NodeType::InitVal) {
            handleInitVal(child);
        } else if (child->getNodeType() == NodeType::ConstExp) {
            handleConstExp(child);
        }
    }
}

void Visitor::handleConstDef(Node *constDef) {
    string word = constDef->getWord();
    Symbol* symbol = new Symbol(0, word, true, nullptr);
    symbol->type += constDef->children.size() - 1;
    // domention of def
    symbolTable.addSymbol(symbol, constDef->lineNum);

    for (auto* child : constDef->children) {
        if (child->getNodeType() == NodeType::ConstInitVal) {
            handleConstInitVal(child);
        } else if (child->getNodeType() == NodeType::ConstExp) {
            handleConstExp(child);
        }
    }
}

int Visitor::handleFuncFParam(Node *funcFParam) {
    string word = funcFParam->getWord();
    Symbol* symbol = new Symbol(funcFParam->getType(), word, false, nullptr);
    symbolTable.addSymbol(symbol, funcFParam->lineNum);
    return funcFParam->getType();
}

void Visitor::handleFuncDef(Node *funcDef) {
    int retType = funcDef->children[0]->getType();

    int paramNum = 0;
    Func* func = new Func(retType, paramNum);

    string word = funcDef->getWord();
    Symbol* symbol = new Symbol(-1, word, false, func);
    
    symbolTable.addSymbol(symbol, funcDef->lineNum);

    symbolTable.createSymbolTable(); // create new symbol table

    for (auto* child : funcDef->children) {
        if (child->getNodeType() == NodeType::FuncFParams) {
            func->paramNum += handleFuncFParams(child, &func->paramTypeList);
        } else if (child->getNodeType() == NodeType::FuncType) {
            func->retype = handleFuncType(child);
        } else if (child->getNodeType() == NodeType::Block) {
            handleBlock(child, retType, false);
        }
    }
}

void Visitor::handleDecl(Node *funcFParam) {
    for (auto* child : funcFParam->children) {
        if (child->getNodeType() == NodeType::ConstDecl) {
            handleConstDecl(child);
        } else if (child->getNodeType() == NodeType::VarDecl) {
            handleVarDecl(child);
        }
    }
}

void Visitor::handleMainFuncDef(Node *mainFuncFParam) {
    generateCode("define dso_local i32 @main() {");
    for (auto* child : mainFuncFParam->children) {
        symbolTable.createSymbolTable();
        handleBlock(child, 0, false);
    }
    generateCode("}");
}

void Visitor::handleConstDecl(Node *constDecl) {
    for (auto* child : constDecl->children) {
        if (child->getNodeType() == NodeType::BType) {
            handleBType(child);
        } else if (child->getNodeType() == NodeType::ConstDef) {
            handleConstDef(child);
        } 
    }
}

void Visitor::handleVarDecl(Node *varDecl) {
    for (auto* child : varDecl->children) {
        if (child->getNodeType() == NodeType::BType) {
            handleBType(child);
        } else if (child->getNodeType() == NodeType::VarDef) {
            handleVarDef(child);
        }
    }
}

void Visitor::handleBType(Node *BType) {
    return;
}

void Visitor::handleConstInitVal(Node *constInitVal) {
    for (auto* child : constInitVal->children) {
        if (child->getNodeType() == NodeType::ConstExp) {
            handleConstExp(child);
        } else if (child->getNodeType() == NodeType::ConstInitVal) {
            handleConstInitVal(child);
        }
    }
}

void Visitor::handleConstExp(Node *constExp) {
    for (auto* child : constExp->children) {
        if (child->getNodeType() == NodeType::AddExp) {
            handleAddExp(child);
        }
    }
}

void Visitor::handleInitVal(Node *initVal) {
    for (auto* child : initVal->children) {
        if (child->getNodeType() == NodeType::Exp) {
            handleExp(child);
        } else if (child->getNodeType() == NodeType::InitVal) {
            handleInitVal(child);
        }
    }
}

int Visitor::handleExp(Node *exp) {
    int ret;
    for (auto* child : exp->children) {
        ret = handleAddExp(child);
    }
    return ret;
}

int Visitor::handleFuncFParams(Node *funcFParams, vector<int>* paramTypeList) {
    int num = 0;
    for (auto* child : funcFParams->children) {
        if (child->getNodeType() == NodeType::FuncFParam) {
            num++;
            paramTypeList->push_back(handleFuncFParam(child));
        }
    }
    return num;
}

int Visitor::handleFuncType(Node *funcType) {
    return funcType->getType();
}

void Visitor::handleBlock(Node *block, int isNoRet, bool isLoop) {
    for (auto* child : block->children) {
        if (child->getNodeType() == NodeType::BlockItem) {
            handleBlockItem(child, isNoRet, isLoop);
        }
    }
#ifdef ERROR_CHECK
    if (!isNoRet && (block->children.empty() || block->children[block->children.size()-1]->children[0]->getType() != 5)) {
        printError(block->getLastLine(), "g");
    }
#endif
    symbolTable.deleteSymbolTable();
}

void Visitor::handleBlockItem(Node *blockItem, int isNoRet, bool isLoop) {
    for (auto* child : blockItem->children) {
        if (child->getNodeType() == NodeType::Decl) {
            handleDecl(child);
        } else if (child->getNodeType() == NodeType::Stmt) {
            handleStmt(child, isNoRet, isLoop);
        }
    }
}

void Visitor::handleStmt(Node *stmt, int isNoRet, bool isLoop) {
    if (stmt->getType() == 0) {
        // normal
        bool changeLVal = false;
        Symbol* symbol = nullptr;
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::LVal) {
                changeLVal = true;
                symbol = symbolTable.getSymbol(child->getWord(), false, true);
                handleLVal(child);
            } else if (child->getNodeType() == NodeType::Exp) {
#ifdef ERROR_CHECK
                if (changeLVal && symbol != nullptr && symbol->con) {
                    printError(stmt->lineNum, "h");
                }
#endif
                handleExp(child);
            } else if (child->getNodeType() == NodeType::Block) {
                symbolTable.createSymbolTable();
                handleBlock(child, isNoRet, isLoop);
            } else if (child->getNodeType() == NodeType::Stmt) {
                handleStmt(child, isNoRet, isLoop);
            }
        }
    } else if (stmt->getType() == 1) {
        // if
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::Cond) {
                handleCond(child);
            } else if (child->getNodeType() == NodeType::Stmt) {
                handleStmt(child, isNoRet, false);
            } // need to conisder else condition
        }
    } else if (stmt->getType() == 2) {
        // for 
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::ForStmt) {
                handleForStmt(child);
            } else if (child->getNodeType() == NodeType::Cond) {
                handleCond(child);
            } else if (child->getNodeType() == NodeType::Stmt) {
                handleStmt(child, isNoRet, true);
            }
        } // need to distinguish different ForStmt
    } else if (stmt->getType() == 3) {
        // break
        // generate branch code ??
#ifdef ERROR_CHECK
        if (!isLoop) {
            printError(stmt->lineNum, "m");
        }
#endif
    } else if (stmt->getType() == 4) {
        // continue
        // generate branch code ??
#ifdef ERROR_CHECK
        if (!isLoop) {
            printError(stmt->lineNum, "m");
        }
#endif
    } else if (stmt->getType() == 5) {
        // return
        // generate branch code ?? and fill code??
        for (auto* child : stmt->children) {
#ifdef ERROR_CHECK
            if (isNoRet) {
                printError(stmt->lineNum, "f");
            }
#endif
            if (child->getNodeType() == NodeType::Exp) {
                handleExp(child);
            }
        }
        generateCode("ret i32 \%sth");
    } else if (stmt->getType() == 6) {
        // getint
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::LVal) {
                handleLVal(child);
#ifdef ERROR_CHECK
                Symbol* symbol = symbolTable.getSymbol(child->getWord(), false, true);
                if (symbol != nullptr && symbol->con) {
                    printError(stmt->lineNum, "h");
                }
#endif
            }
        }
    } else if (stmt->getType() == 7) {
        // printf
        string str = stmt->getStr();
#ifdef ERROR_CHECK
        int n = 0;
        for (int i = 0; i < str.size() - 1; i++) {
            if (str[i] == '%' && str[i + 1] == 'd') {
                n++;
            }
        }
        if (stmt->children.size() != n) {
            printError(stmt->lineNum, "l");
        }
#endif
    } 
}

void Visitor::handleForStmt(Node *forStmt) {
    for (auto* child : forStmt->children) {
        if (child->getNodeType() == NodeType::LVal) {
            handleLVal(child);
        } else if (child->getNodeType() == NodeType::Exp) {
            handleExp(child);
        }
    }
}

void Visitor::handleCond(Node *cond) {
    for (auto* child : cond->children) {
        if (child->getNodeType() == NodeType::LOrExp) {
            handleLOrExp(child);
        }
    }
}

int Visitor::handleLVal(Node *lVal) {
    int ret;
    Symbol* Symbol = symbolTable.getSymbol(lVal->getWord(), false, true);
    ret = (Symbol == nullptr) ? 0 : Symbol->type;
    // need to consider if exsiting lVal
#ifdef ERROR_CHECK
    if (Symbol == nullptr) {
        printError(lVal->lineNum, "c");
    }
#endif
    for (auto *child : lVal->children) {
        if (child->getNodeType() == NodeType::Exp) {
            ret = (ret > 0) ? ret-1 : ret;
            handleExp(child);
        }
    }
    return ret;
}

int Visitor::handlePrimaryExp(Node *primaryExp) {
    int ret;
    for (auto* child : primaryExp->children) {
        if (child->getNodeType() == NodeType::LVal) {
            ret = handleLVal(child);
        } else if (child->getNodeType() == NodeType::Number) {
            ret = handleNumber(child);
        } else if (child->getNodeType() == NodeType::Exp) {
            ret = handleExp(child);
        }
    }
    return ret;
}

int Visitor::handleNumber(Node *number) {
    int num = number->getVal();
    return 0; // is int
    // generate code
}

int Visitor::handleUnaryExp(Node *unaryExp) {
    int ret = 0;
    if (unaryExp->getWord() != "") { // is Ident '(' [FuncRParams] ')'
        Symbol* symbol = symbolTable.getSymbol(unaryExp->getWord(), true, true);
        if (symbol != nullptr) {
            ret = symbol->func->retype;
        } else {
            ret = 0;
        }
#ifdef ERROR_CHECK
        if (symbol == nullptr) {
            printError(unaryExp->lineNum, "c");
        }
#endif
    }
    for (auto* child : unaryExp->children) {
        if (child->getNodeType() == NodeType::PrimaryExp) {
            ret = handlePrimaryExp(child);
        } else if (child->getNodeType() == NodeType::UnaryOp) {
            handleUnaryOp(child);
        } else if (child->getNodeType() == NodeType::UnaryExp) {
            ret = handleUnaryExp(child);
        } else if (child->getNodeType() == NodeType::FuncRParams) {
            int funcRParamsNum = child->children.size();
            Symbol* funcSymbol = symbolTable.getSymbol(unaryExp->getWord(), true, true);
#ifdef ERROR_CHECK
            if (funcSymbol && funcRParamsNum != funcSymbol->func->paramNum) {
                printError(unaryExp->lineNum, "d");
            }
#endif
            handleFuncRParams(child, funcSymbol);
        }
    }
    return ret;
}

void Visitor::handleUnaryOp(Node *unaryOp) {
    return; // + = !
}

void Visitor::handleFuncRParams(Node *funcRParams, Symbol* funcSymbol) {
    // 对调用的函数进行参数处理 funcSymbol是被调用函数的符号表项
    int i = 0;
    for (auto* child : funcRParams->children) {
        if (child->getNodeType() == NodeType::Exp) {
            int t = handleExp(child); // 返回实参的类型
#ifdef ERROR_CHECK
            if (funcSymbol != nullptr) {
                if (i > funcSymbol->func->paramNum) {
                    std::cout << "too much" << std::endl;
                }
                if (!funcSymbol->func->paramTypeList.empty() && t != funcSymbol->func->paramTypeList[i++]) {
                    printError(funcRParams->lineNum, "e");
                } // 逐个实参形参类型对比
            }
#endif
        }
    }
}

int Visitor::handleMulExp(Node *mulExp) {
    int ret = 0;
    vector<int>* op = mulExp->getOp();
    int opi = 0;
    // mul div mod
    for (auto* child : mulExp->children) {
        if (child->getNodeType() == NodeType::UnaryExp) {
            ret = handleUnaryExp(child);
        } else if (child->getNodeType() == NodeType::MulExp) {
            ret = handleMulExp(child);
            // 0 * 1 / 2 %
        }
        if (op->size() > 0 && opi < op->size()) {
            if (op->at(opi) == 0) {
                generateCode("\%sth = mul i32 \%sth, \%sth");
            } else if (op->at(opi) == 1) {
                generateCode("\%sth = div i32 \%sth, \%sth");
            } else if (op->at(opi) == 2) {
                generateCode("\%sth = mod i32 \%sth, \%sth");
            }
            opi++;
        }
    }
    return ret;
}

int Visitor::handleAddExp(Node *addExp) {
    // add sub
    int ret = 0;
    vector<int>* op = addExp->getOp();
    int opi = 0;
    for (auto* child : addExp->children) {
        if (child->getNodeType() == NodeType::MulExp) {
            ret = handleMulExp(child);
        } else if (child->getNodeType() == NodeType::AddExp) {
            ret = handleAddExp(child);
            // 0 + 1 -
        }
        if (op->size() > 0 && opi < op->size()) {
            if (op->at(opi) == 0) {
                generateCode("\%sth = add i32 \%sth, \%sth");
            } else if (op->at(opi) == 1) {
                generateCode("\%sth = sub i32 \%sth, \%sth");
            }
            opi++;
        }
    }
    return ret;
}

void Visitor::handleRelExp(Node *relExp) {
    // lt gt le ge
    for (auto* child : relExp->children) {
        if (child->getNodeType() == NodeType::AddExp) {
            handleAddExp(child);
        } else if (child->getNodeType() == NodeType::RelExp) {
            handleRelExp(child);
        }
    }
}

void Visitor::handleEqExp(Node *eqExp) {
    // eq ne
    for (auto* child : eqExp->children) {
        if (child->getNodeType() == NodeType::RelExp) {
            handleRelExp(child);
        } else if (child->getNodeType() == NodeType::EqExp) {
            handleEqExp(child);
        }
    }
}

void Visitor::handleLAndExp(Node *lAndExp) {
    for (auto* child : lAndExp->children) {
        if (child->getNodeType() == NodeType::EqExp) {
            handleEqExp(child);
        } else if (child->getNodeType() == NodeType::LAndExp) {
            handleLAndExp(child);
        }
    }
}

void Visitor::handleLOrExp(Node *lOrExp) {
    for (auto* child : lOrExp->children) {
        if (child->getNodeType() == NodeType::LAndExp) {
            handleLAndExp(child);
        } else if (child->getNodeType() == NodeType::LOrExp) {
            handleLOrExp(child);
        }
    }
}
