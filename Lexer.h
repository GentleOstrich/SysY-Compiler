//
// Created by yh on 2023/9/18.
//

#ifndef SYSY_COMPILER_LEXER_H
#define SYSY_COMPILER_LEXER_H

#include <string>
#include "LexType.h"

#define RESERVEWORDS_NUM 12

using namespace std;


class Lexer {
private:
    string source;
    int curPos = 0;
    string token;
    string reserveWords[RESERVEWORDS_NUM] = {
            "main", "const", "int", "break", "continue", "if", "else", "for", "getint", "printf", "return", "void"
    };
    LexType lexType;
    int lineNum = 0;
    int number;

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
        token.clear();
        //处理完毕
        if (curPos >= source.length()) {
            return 1;
        }
        // 空格 制表符 回车
        while (source[curPos] == '\t' || source[curPos] == ' ' || source[curPos] == '\n') {
            if (source[curPos] == '\n') {
                lineNum++;
            }
            curPos++;
        }

        // 标识符 保留字
        if (isalpha(source[curPos]) || source[curPos] == '_') {
            while (isalpha(source[curPos]) || isdigit(source[curPos]) || source[curPos] == '_') {
                token += source[curPos];
                curPos++;
            }
            int reserveValue = isReserveWord(token);
            cout << reserveValue << endl;
            switch (reserveValue) {
                case 0:
                    lexType = LexType::IDENFR;
                case 1:
                    lexType = LexType::MAINTK;
                case 2:
                    lexType = LexType::CONSTTK;
                case 3:
                    lexType = LexType::INTTK;
                case 4:
                    lexType = LexType::BREAKTK;
                case 5:
                    lexType = LexType::CONTINUETK;
                case 6:
                    lexType = LexType::IFTK;
                case 7:
                    lexType = LexType::ELSETK;
                case 8:
                    lexType = LexType::FORTK;
                case 9:
                    lexType = LexType::GETINTTK;
                case 10:
                    lexType = LexType::PRINTFTK;
                case 11:
                    lexType = LexType::RETURNTK;
                case 12:
                    lexType = LexType::VOIDTK;
                default:
                    lexType = LexType::ERROR;
            }
//            if (lexType == LexType::ERROR) {
//                return -1;
//            }
            return 0;
        }

        // 无符号整数
        if (isdigit(source[curPos])) {
            while (isdigit(source[curPos])) {
                token += source[curPos];
                curPos++;
            }
            number = atoi(token.c_str());
            lexType = LexType::INTCON;
            return 0;
        }

        // 字符串
        if (source[curPos] == '\"') {
            token += source[curPos];
            curPos++;
            while (source[curPos] != '\"') {
                token += source[curPos];
                curPos++;
            }
            token += source[curPos];
            curPos++;
            lexType = LexType::STRCON;
            return 0;
        }

        //  ! && || + - * / %  < <= > >= == != = ; , ( ) [ ] { }
        if (source[curPos] == '!') {
            token += '!';
            lexType = LexType::NOT;
            curPos++;
            return 0;
        }
        if (source[curPos] == '&' && source[curPos + 1] == '&') {
            token += "&&";
            lexType = LexType::AND;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '|' && source[curPos + 1] == '|') {
            token += "||";
            lexType = LexType::OR;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '+') {
            token += '+';
            lexType = LexType::PLUS;
            curPos++;
            return 0;
        }
        if (source[curPos] == '-') {
            token += '-';
            lexType = LexType::MINU;
            curPos++;
            return 0;
        }
        if (source[curPos] == '*') {
            token += '*';
            lexType = LexType::MULT;
            curPos++;
            return 0;
        }
        if (source[curPos] == '%') {
            token += '%';
            lexType = LexType::MOD;
            curPos++;
            return 0;
        }
        if (source[curPos] == '<' && source[curPos + 1] == '=') {
            token += "<=";
            lexType = LexType::LEQ;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '<') {
            token += '<';
            lexType = LexType::LSS;
            curPos++;
            return 0;
        }
        if (source[curPos] == '>' && source[curPos + 1] == '=') {
            token += ">=";
            lexType = LexType::GEQ;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '>') {
            token += '>';
            lexType = LexType::GRE;
            curPos += 1;
            return 0;
        }
        if (source[curPos] == '=' && source[curPos + 1] == '=') {
            token += "==";
            lexType = LexType::EQL;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '!' && source[curPos + 1] == '=') {
            token += "==";
            lexType = LexType::NEQ;
            curPos += 2;
            return 0;
        }
        if (source[curPos] == '=') {
            token += '=';
            lexType = LexType::ASSIGN;
            curPos++;
            return 0;
        }
        if (source[curPos] == ';') {
            token += ';';
            lexType = LexType::SEMICN;
            curPos++;
            return 0;
        }
        if (source[curPos] == ',') {
            token += ',';
            lexType = LexType::COMMA;
            curPos++;
            return 0;
        }
        if (source[curPos] == '(') {
            token += '(';
            lexType = LexType::LPARENT;
            curPos++;
            return 0;
        }
        if (source[curPos] == ')') {
            token += ')';
            lexType = LexType::RPARENT;
            curPos++;
            return 0;
        }
        if (source[curPos] == '[') {
            token += '[';
            lexType = LexType::LBRACK;
            curPos++;
            return 0;
        }
        if (source[curPos] == ']') {
            token += ']';
            lexType = LexType::RBRACK;
            curPos++;
            return 0;
        }
        if (source[curPos] == '{') {
            token += '{';
            lexType = LexType::LBRACE;
            curPos++;
            return 0;
        }
        if (source[curPos] == '}') {
            token += '}';
            lexType = LexType::RBRACE;
            curPos++;
            return 0;
        }

        // 注释
        if (source[curPos] == '/') {
            if (curPos < source.length() && source[curPos + 1] == '/') {
                curPos += 2;
                while (curPos < source.length() && source[curPos] != '\n') {
                    curPos++;
                }
                return next();
            } else if (curPos < source.length() && source[curPos + 1] == '*') {
                curPos += 2;
                while (curPos < source.length()) {
                    while (curPos < source.length() && source[curPos] != '*') {
                        if (source[curPos] == '\n') {
                            lineNum++;
                        }
                        curPos++;
                    }
                    while (curPos < source.length() && source[curPos] == '*') {
                        curPos++;
                    }
                    if (curPos < source.length() && source[curPos] == '/') {
                        curPos++;
                        break;
                    }
                }
                return next();
            } else {
                lexType = LexType::DIV;
                curPos++;
            }
        }
        return 0;
    }

    string getToken() {
        return token;
    }

    LexType getLexType() {
        return lexType;
    }

    void setSource(string source) {
        this->source = source;
    }
};


#endif //SYSY_COMPILER_LEXER_H
