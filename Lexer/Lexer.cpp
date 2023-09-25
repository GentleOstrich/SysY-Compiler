//
// Created by yh on 2023/9/25.
//
#include "Lexer.h"
vector<pair<Token, int>> tokenVec;

int Lexer::isReserveWord(const string &word) {
    return 0;
}

int Lexer::next() {
    //cout << curPos << endl;
    word.clear();
    lexType = LexType::NONE;
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
            word += source[curPos];
            curPos++;
        }
        int reserveValue = isReserveWord(word);
        switch (reserveValue) {
            case 0:
                lexType = LexType::IDENFR;
                break;
            case 1:
                lexType = LexType::MAINTK;
                break;
            case 2:
                lexType = LexType::CONSTTK;
                break;
            case 3:
                lexType = LexType::INTTK;
                break;
            case 4:
                lexType = LexType::BREAKTK;
                break;
            case 5:
                lexType = LexType::CONTINUETK;
                break;
            case 6:
                lexType = LexType::IFTK;
                break;
            case 7:
                lexType = LexType::ELSETK;
                break;
            case 8:
                lexType = LexType::FORTK;
                break;
            case 9:
                lexType = LexType::GETINTTK;
                break;
            case 10:
                lexType = LexType::PRINTFTK;
                break;
            case 11:
                lexType = LexType::RETURNTK;
                break;
            case 12:
                lexType = LexType::VOIDTK;
                break;
            default:
                lexType = LexType::NONE;
        }
        if (lexType == LexType::NONE) {
            return -1;
        }
        return 0;
    }

    // 无符号整数
    if (isdigit(source[curPos])) {
        while (isdigit(source[curPos])) {
            word += source[curPos];
            curPos++;
        }
        number = atoi(word.c_str());
        lexType = LexType::INTCON;
        return 0;
    }

    // 字符串
    if (source[curPos] == '\"') {
        word += source[curPos];
        curPos++;
        while (source[curPos] != '\"') {
            word += source[curPos];
            curPos++;
        }
        word += source[curPos];
        curPos++;
        lexType = LexType::STRCON;
        return 0;
    }

    //  ! && || + - * / %  < <= > >= == != = ; , ( ) [ ] { }
    if (source[curPos] == '&' && source[curPos + 1] == '&') {
        word += "&&";
        lexType = LexType::AND;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '|' && source[curPos + 1] == '|') {
        word += "||";
        lexType = LexType::OR;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '!' && source[curPos + 1] == '=') {
        word += "!=";
        lexType = LexType::NEQ;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '<' && source[curPos + 1] == '=') {
        word += "<=";
        lexType = LexType::LEQ;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '>' && source[curPos + 1] == '=') {
        word += ">=";
        lexType = LexType::GEQ;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '=' && source[curPos + 1] == '=') {
        word += "==";
        lexType = LexType::EQL;
        curPos += 2;
        return 0;
    }
    if (source[curPos] == '!') {
        word += '!';
        lexType = LexType::NOT;
        curPos++;
        return 0;
    }
    if (source[curPos] == '+') {
        word += '+';
        lexType = LexType::PLUS;
        curPos++;
        return 0;
    }
    if (source[curPos] == '-') {
        word += '-';
        lexType = LexType::MINU;
        curPos++;
        return 0;
    }
    if (source[curPos] == '*') {
        word += '*';
        lexType = LexType::MULT;
        curPos++;
        return 0;
    }
    if (source[curPos] == '%') {
        word += '%';
        lexType = LexType::MOD;
        curPos++;
        return 0;
    }
    if (source[curPos] == '<') {
        word += '<';
        lexType = LexType::LSS;
        curPos++;
        return 0;
    }
    if (source[curPos] == '>') {
        word += '>';
        lexType = LexType::GRE;
        curPos += 1;
        return 0;
    }

    if (source[curPos] == '=') {
        word += '=';
        lexType = LexType::ASSIGN;
        curPos++;
        return 0;
    }
    if (source[curPos] == ';') {
        word += ';';
        lexType = LexType::SEMICN;
        curPos++;
        return 0;
    }
    if (source[curPos] == ',') {
        word += ',';
        lexType = LexType::COMMA;
        curPos++;
        return 0;
    }
    if (source[curPos] == '(') {
        word += '(';
        lexType = LexType::LPARENT;
        curPos++;
        return 0;
    }
    if (source[curPos] == ')') {
        word += ')';
        lexType = LexType::RPARENT;
        curPos++;
        return 0;
    }
    if (source[curPos] == '[') {
        word += '[';
        lexType = LexType::LBRACK;
        curPos++;
        return 0;
    }
    if (source[curPos] == ']') {
        word += ']';
        lexType = LexType::RBRACK;
        curPos++;
        return 0;
    }
    if (source[curPos] == '{') {
        word += '{';
        lexType = LexType::LBRACE;
        curPos++;
        return 0;
    }
    if (source[curPos] == '}') {
        word += '}';
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
            word += '/';
            lexType = LexType::DIV;
            curPos++;
        }
    }
    return 0;
}

Token Lexer::getToken()  {
    return Token(word, lexType);
}

int Lexer::getLineNum()  {
    return lineNum;
}

void Lexer::setSource(string source)  {
    this->source = source;
}

void Lexer::scan(string source) {
    setSource(source);
    while (true) {
        bool isEnd = next();
        if (isEnd) {
            break;
        }
        Token token = getToken();
        int lineNum = getLineNum();
        tokenVec.emplace_back(token, lineNum);
    }
}






