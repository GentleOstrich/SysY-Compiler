//
// Created by lyh on 11/9/2023.
//

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
            handleFuncType(child);
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

void Visitor::handleFuncType(Node *funcType) {

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

}



