//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDEF_H
#define SYSY_COMPILER_VARDEF_H
#include "Node.h"
#include <vector>

class VarDef : public Node {
public:
    explicit VarDef(NodeType nodeType1);
    string word;
    bool Equal = false;
    short type = 0;
    void setWord(const string& word);
    string getWord() override ;
    bool hasEqual() override ;
    short getType() override ;

};


#endif //SYSY_COMPILER_VARDEF_H
