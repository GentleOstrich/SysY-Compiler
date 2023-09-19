//
// Created by lyh on 9/19/2023.
//

#ifndef SYSY_COMPILER_LEXTYPE_H
#define SYSY_COMPILER_LEXTYPE_H


enum class LexType {
    IDENFR,
    MAINTK,
    CONSTTK,
    INTTK,
    BREAKTK,
    CONTINUETK,
    IFTK,
    ELSETK,
    FORTK,
    GETINTTK,
    PRINTFTK,
    RETURNTK,
    VOIDTK,
    INTCON,
    STRCON,
    NOT,
    AND,
    OR,
    PLUS,
    MINU,
    MULT,
    DIV,
    MOD,
    LSS,
    LEQ,
    GRE,
    GEQ,
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
    RBRACE,
    NONE
};


#endif //SYSY_COMPILER_LEXTYPE_H
