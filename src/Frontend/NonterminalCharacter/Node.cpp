//
// Created by lyh on 11/6/2023.
//

#include "Node.h"

Node::Node(Token token, NodeType nodeType, int lineNum) {
    this->token = &token;
    this->nodeType = nodeType;
    this->lineNum = lineNum;
}

Node::Node(NodeType nodeType, int lineNum) {
    this->nodeType = nodeType;
    this->lineNum = lineNum;
}

void Node::addChild(std::unique_ptr<Node> child) {
    if (child != nullptr) {
        this->children.push_back(child);
    }
}

NodeType Node::getNodeType() {
    return this->nodeType;
}

std::string Node::getWord() {
    return std::string();
}

int Node::getType() {
    return 0;
}

bool Node::hasEqual() {
    return false;
}

std::string Node::getStr() {
    return std::string();
}

int Node::getVal() {
    return 0;
}

int Node::getLineNum() {
    if (this->children.empty()) {
        return this->lineNum;
    }
    return this->children[this->children.size() - 1]->lineNum;
}

int Node::getLastLine() {
    return 0;
}

int Node::getOp() {
    return 0;
}