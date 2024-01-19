//
// Created by lyh on 11/6/2023.
//

#ifndef SYSY_COMPILER_Node_H
#define SYSY_COMPILER_Node_H

#include <memory>
#include <vector>
#include "../Lexer/LexType.h"
#include "../Lexer/Token.h"
#include "NodeType.h"

class Node
{
public:
    NodeType nodeType;
    Token *token;
    int lineNum;
    std::vector<Node *> children;
    explicit Node(NodeType nodeType, int lineNum);
    explicit Node(Token token, NodeType nodeType, int lineNum);
    void addChild(Node *child);
    NodeType getNodeType();
    virtual std::string getWord();
    virtual int getType();
    virtual bool hasEqual();
    virtual std::string getStr();
    virtual int getVal();
    int getLineNum();
    virtual int getLastLine();
    virtual int getOp();
};

#endif // SYSY_COMPILER_Node_H
