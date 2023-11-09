//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_FUNCDEF_H
#define SYSY_COMPILER_FUNCDEF_H
#include "Node.h"
#include <vector>

class FuncDef : public Node {
public:
    explicit FuncDef(NodeType nodeType1);
    string word;
    void setWord(const string& word);
    string getWord() ;

    virtual ~FuncDef();
};


#endif //SYSY_COMPILER_FUNCDEF_H
