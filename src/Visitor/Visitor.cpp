//
// Created by lyh on 11/9/2023.
// build the symbol table and generate code

#include "Visitor.h"
extern SymbolTable symbolTable;

void Visitor::handleCompUnit(Node* node) {
    for (auto* child : node->children) {
        if (node->getNodeType() == NodeType::Decl) {
            handleDecl(child);
        } else if (node->getNodeType() == NodeType::FuncDef) {
            handleFuncDef(child);
        } else if (node->getNodeType() == NodeType::MainFuncDef) {
            handleMainFuncDef(child);
        }
    }
}

void Visitor::handleVarDef(Node *varDef) {
    string word = varDef->getWord();
    Symbol symbol(0, word, false, nullptr);
    if (varDef->hasEqual()) {
        symbol.type += varDef->children.size() - 1;
    } else {
        symbol.type += varDef->children.size();
    }
    symbolTable.addSymbol(&symbol);

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
    Symbol symbol(0, word, true, nullptr);
    symbol.type += constDef->children.size() - 1;
    // domention of def
    symbolTable.addSymbol(&symbol);

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
    Symbol symbol(funcFParam->getType(), word, false, nullptr);
    symbolTable.addSymbol(&symbol);
    return funcFParam->getType();
}

void Visitor::handleFuncDef(Node *funcDef) {
    int retType = funcDef->children[0]->getType();
    int paramNum = 0;
    Func func(retType, paramNum);

    string word = funcDef->getWord();
    Symbol symbol(-1, word, false, &func);
    
    Node* funcFParams = funcDef->children[1];
    symbolTable.addSymbol(&symbol);

    symbolTable.createSymbolTable(); // create new symbol table

    for (auto* child : funcFParams->children) {
        if (child->getNodeType() == NodeType::FuncFParams) {
            handleFuncFParams(child, func.paramTypeList);
            func.paramTypeList.push_back(child->getType());
            func.paramNum++;
        } else if (child->getNodeType() == NodeType::FuncType) {
            func.retype = handleFuncType(child);
        } else if (child->getNodeType() == NodeType::Block) {
            handleBlock(child);
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

void Visitor::handleMainFuncDef(Node *funcFParam) {

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

void Visitor::handleExp(Node *exp) {
    for (auto* child : exp->children) {
        handleAddExp(child);
    }
}

int Visitor::handleFuncFParams(Node *funcFParams, vector<int> paramTypeList) {
    int num = 0;
    for (auto* child : funcFParams->children) {
        if (child->getNodeType() == NodeType::FuncFParam) {
            num++;
            paramTypeList.push_back(handleFuncFParam(child));
        }
    }
    return num;
}

short Visitor::handleFuncType(Node *funcType) {
    return funcType->getType();
}

void Visitor::handleBlock(Node *block) {
    for (auto* child : block->children) {
        if (child->getNodeType() == NodeType::BlockItem) {
            handleBlockItem(child);
        }
    }
    symbolTable.deleteSymbolTable();
}

void Visitor::handleBlockItem(Node *blockItem) {
    for (auto* child : blockItem->children) {
        if (child->getNodeType() == NodeType::Decl) {
            handleDecl(child);
        } else if (child->getNodeType() == NodeType::Stmt) {
            handleStmt(child);
        }
    }
}

void Visitor::handleStmt(Node *stmt) {
    if (stmt->getType() == 0) {
        // normal
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::LVal) {
                handleLVal(child);
            } else if (child->getNodeType() == NodeType::Exp) {
                handleExp(child);
            } else if (child->getNodeType() == NodeType::Block) {
                handleBlock(child);
            } else if (child->getNodeType() == NodeType::Stmt) {
                handleStmt(child);
            }
        }
    } else if (stmt->getType() == 1) {
        // if
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::Cond) {
                handleCond(child);
            } else if (child->getNodeType() == NodeType::Stmt) {
                handleStmt(child);
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
                handleStmt(child);
            }
        } // need to distinguish different ForStmt
    } else if (stmt->getType() == 3) {
        // break
        // generate branch code ??
    } else if (stmt->getType() == 4) {
        // continue
        // generate branch code ??
    } else if (stmt->getType() == 5) {
        // return
        // generate branch code ?? and fill code??
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::Exp) {
                handleExp(child);
            }
        }
    } else if (stmt->getType() == 6) {
        // getint
        for (auto* child : stmt->children) {
            if (child->getNodeType() == NodeType::LVal) {
                handleLVal(child);
            }
        }
    } else if (stmt->getType() == 7) {
        // printf

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

void Visitor::handleLVal(Node *lVal) {
    // need to consider if exsiting lVal 
    for (auto *child : lVal->children) {
        if (child->getNodeType() == NodeType::Exp) {
            handleExp(child);
        }
    }
}

void Visitor::handlePrimaryExp(Node *primaryExp) {
    for (auto* child : primaryExp->children) {
        if (child->getNodeType() == NodeType::LVal) {
            handleLVal(child);
        } else if (child->getNodeType() == NodeType::Number) {
            handleNumber(child);
        } else if (child->getNodeType() == NodeType::Exp) {
            handleExp(child);
        }
    }
}

void Visitor::handleNumber(Node *number) {
    int num = number->getVal();
    // generate code
}

void Visitor::handleUnaryExp(Node *unaryExp) {
    for (auto* child : unaryExp->children) {
        if (child->getNodeType() == NodeType::PrimaryExp) {
            handlePrimaryExp(child);
        } else if (child->getNodeType() == NodeType::UnaryOp) {
            handleUnaryOp(child);
        } else if (child->getNodeType() == NodeType::UnaryExp) {
            handleUnaryExp(child);
        } else if (child->getNodeType() == NodeType::FuncRParams) {
            handleFuncRParams(child);
        }
    }
}

void Visitor::handleUnaryOp(Node *unaryOp) {
    return; // + = !
}

void Visitor::handleFuncRParams(Node *funcRParams) {
    for (auto* child : funcRParams->children) {
        if (child->getNodeType() == NodeType::Exp) {
            handleExp(child);
        }
    }
}

void Visitor::handleMulExp(Node *mulExp) {
    // mul div mod
    for (auto* child : mulExp->children) {
        if (child->getNodeType() == NodeType::UnaryExp) {
            handleUnaryExp(child);
        } else if (child->getNodeType() == NodeType::MulExp) {
            handleMulExp(child);
        }
    }
}

void Visitor::handleAddExp(Node *addExp) {
    // add sub
    for (auto* child : addExp->children) {
        if (child->getNodeType() == NodeType::MulExp) {
            handleMulExp(child);
        } else if (child->getNodeType() == NodeType::AddExp) {
            handleAddExp(child);
        }
    }
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
