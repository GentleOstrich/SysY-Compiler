//
// Created by lyh on 11/6/2023.
//

#ifndef SYSY_COMPILER_Node_H
#define SYSY_COMPILER_Node_H
#include <vector>
#include "../Lexer/LexType.h"
#include "../Lexer/Token.h"

class Node {
public:
    Token* token;
    int line;
    std::vector<Node*> children;
    explicit Node();
    explicit Node(Token token);
    void addChild(Node *child);
};


#endif //SYSY_COMPILER_Node_H
