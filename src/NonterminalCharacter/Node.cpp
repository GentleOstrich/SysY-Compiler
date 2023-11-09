//
// Created by lyh on 11/6/2023.
//

#include "Node.h"
Node::Node(Token token, NodeType nodeType) {
    this->token = &token;
    this->nodeType = nodeType;
}

Node::Node(NodeType nodeType) {
    this->nodeType = nodeType;
}

void Node::addChild(Node *child) {
    if (child != nullptr) {
        this->children.push_back(child);
    }
}

NodeType Node::getNodeType() {
    return this->nodeType;
}

string Node::getWord() {
    return std::string();
}



