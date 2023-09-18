//
// Created by yh on 2023/9/18.
//

#ifndef SYSY_COMPILER_LEXER_H
#define SYSY_COMPILER_LEXER_H

#include <string>

#define RESERVEWORDS_NUM 12
#define SOURCE_LEN_MAX 1024
#define TOKEN_LEN_MAX 10

using namespace std;
enum LexType {
    IDENFR,
    INTCON,
    STRCON,
    MAINTK,
    CONSTTK,
    INTTK,
    BREAKTK,
    CONTINUETK,
    IFTK,
    ELSETK,
    NOT,
    AND,
    OR,
    FORTK,
    GETINTTK,
    PRINTFTK,
    RETURNTK,
    PLUS,
    MINU,
    VOIDTK,
    MULT,
    DIV,
    MOD,
    LSS,
    LEQ,
    GRE,
    EQL,
    NEQ,
    ASSIGN,
    SEMICN,
    COMMA,
    LPARENT,
    RPARENT,
    LBRACK,
    RBRACK,
    LBRACE,
    RBRACE
};


class Lexer {
private:
    string source[SOURCE_LEN_MAX];
    int curPos = 0;
    string token[TOKEN_LEN_MAX];
    string reserveWords[RESERVEWORDS_NUM] = {
            "main", "const", "int", "break", "continue", "if", "else", "for", "getint", "printf", "return", "void"
    };
    int lineNum = 0;
    int number = 0;

    int isReserveWord(const string &token) {
        for (int i = 0; i < RESERVEWORDS_NUM; ++i) {
            if (reserveWords[i] == token) {
                return i + 1;
            }
        }
        return 0;
    }

public:
    int next() {

    }

    string getToken() {
        if (isReserveWord("hello") == 0) {

        }
    }

    LexType getLexType() {

    }


};


#endif //SYSY_COMPILER_LEXER_H
