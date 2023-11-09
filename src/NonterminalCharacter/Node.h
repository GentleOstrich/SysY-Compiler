//
// Created by lyh on 11/6/2023.
//

#ifndef SYSY_COMPILER_Node_H
#define SYSY_COMPILER_Node_H
#include <vector>
#include "../Lexer/LexType.h"
#include "../Lexer/Token.h"
#include "NodeType.h"

class Node {
public:
    NodeType nodeType;
    Token* token;
    int line;
    std::vector<Node*> children;
    explicit Node(NodeType nodeType1);
    explicit Node(Token token, NodeType nodeType1);
    void addChild(Node *child);
    NodeType getNodeType();
    virtual ~Node();
};


#endif //SYSY_COMPILER_Node_H
