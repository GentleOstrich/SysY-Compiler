//
// Created by lyh on 11/9/2023.
//

#include "SymbolTable.h"

void SymbolTable::createSymbolTable() {
    table.push(this->symbolId);
}

void SymbolTable::addSymbol(Node* def) {
    if (def->getNodeType() == NodeType::FuncDef) {
        auto* funcDef = dynamic_cast<FuncDef *>(def);
        if (SymbolTable::findSymbol(funcDef->getWord(), true, false)) {

        }
    } else if (def->getNodeType() == NodeType::VarDef) {
        auto* varDef = dynamic_cast<VarDef *>(def);
        if (SymbolTable::findSymbol(varDef->getWord(), false, false)) {

        }
    } else {

    }
}

bool SymbolTable::findSymbol(const string& word, bool isFunc, bool all) {
    int end = (all) ? 0 : table.top();
    for (int i = this->symbolId - 1; i >= end; --i) {
        if (symbols[i]->word == word && ((isFunc && symbols[i]->type == -1) || (!isFunc && symbols[i]->type != -1))) {
            return true;
        }
    }
    return false;
}

void SymbolTable::deleteSymbolTable() {
    symbolId = table.top();
    table.pop();
}
