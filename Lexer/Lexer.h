//
// Created by yh on 2023/9/18.
//

#ifndef SYSY_COMPILER_LEXER_H
#define SYSY_COMPILER_LEXER_H

#include <string>
#include <vector>
#include "LexType.h"

#define RESERVEWORDS_NUM 12
#define Token pair<string, LexType>

using namespace std;

class Lexer {
private:
    string source;
    int curPos = 0;
    string word;
    string reserveWords[RESERVEWORDS_NUM] = {
            "main", "const", "int", "break", "continue", "if", "else", "for", "getint", "printf", "return", "void"
    };
    LexType lexType;
    int lineNum = 1;
    int number;

    int isReserveWord(const string &word);

public:
    int next();

    Token getToken();

    int getLineNum();

    void setSource(string source);

    void scan(string source);
};


#endif //SYSY_COMPILER_LEXER_H
