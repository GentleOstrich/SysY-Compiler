//
// Created by lyh on 2023/11/1.
//

#ifndef SYSY_COMPILER_CONSTDEF_H
#define SYSY_COMPILER_CONSTDEF_H
#include "Node.h"
#include "vector"

class ConstDef : public Node {
public:
    ConstDef(NodeType nodeType1, int lineNum);
    string word;
    int type = 0;
    void setWord(const string& word);
    string getWord() override ;
    int getType() override ;
};


#endif //SYSY_COMPILER_CONSTDEF_H
