//
// Created by lyh on 2023/11/8.
//

#include "Token.h"

#include <utility>


    Token::Token(LexType lexType, std::string word, int lineNum) {
        this->lexType = lexType;
        this->word = std::move(word);
        this->lineNum = lineNum;
    }

    Token::Token(const Token &token) {
        this->lexType = token.lexType;
        this->word = token.word;
        this->lineNum = token.lineNum;
    }

    void Token::setToken(const Token& token) {
        this->lexType = token.lexType;
        this->word = token.word;
        this->lineNum = token.lineNum;
    }

    Token::Token() {

    }
