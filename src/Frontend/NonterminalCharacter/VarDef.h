//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_VARDEF_H
#define SYSY_COMPILER_VARDEF_H
#include "Node.h"
#include <vector>

class VarDef : public Node {
public:
    VarDef(NodeType nodeType, int lineNum);
    std::string word;
    bool Equal = false;
    int type = 0;
    // void setWord(const string& word);
    std::string getWord() override ;
    bool hasEqual() override ;
    int getType() override ;

};


#endif //SYSY_COMPILER_VARDEF_H
