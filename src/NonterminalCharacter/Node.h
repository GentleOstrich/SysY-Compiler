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
    int lineNum;
    std::vector<Node*> children;
    explicit Node(NodeType nodeType1, int lineNum);
    explicit Node(Token token, NodeType nodeType1, int lineNum);
    void addChild(Node *child);
    NodeType getNodeType();
    virtual string getWord();
    virtual short getType();
    virtual bool hasEqual();
    virtual string getStr();
    virtual int getVal();
    int getLineNum();
};


#endif //SYSY_COMPILER_Node_H
