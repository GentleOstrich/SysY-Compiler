//
// Created by lyh on 11/6/2023.
//

#include "Node.h"
Node::Node(Token token) {
    this->token = token;
}

Node::Node() {

}

void Node::addChild(Node *child) {
    this->children.push_back(child);
}
