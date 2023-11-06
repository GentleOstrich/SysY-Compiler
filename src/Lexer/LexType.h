//
// Created by lyh on 9/19/2023.
//
#ifndef SYSY_COMPILER_LEXTYPE_H
#define SYSY_COMPILER_LEXTYPE_H
#include <string>
using namespace std;
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


static string LexType2String(LexType lexType) {
    switch (lexType) {
        case LexType::IDENFR:
            return "IDENFR";
        case LexType::MAINTK:
            return "MAINTK";
        case LexType::CONSTTK:
            return "CONSTTK";
        case LexType::INTTK:
            return "INTTK";
        case LexType::BREAKTK:
            return "BREAKTK";
        case LexType::CONTINUETK:
            return "CONTINUETK";
        case LexType::IFTK:
            return "IFTK";
        case LexType::ELSETK:
            return "ELSETK";
        case LexType::FORTK:
            return "FORTK";
        case LexType::GETINTTK:
            return "GETINTTK";
        case LexType::PRINTFTK:
            return "PRINTFTK";
        case LexType::RETURNTK:
            return "RETURNTK";
        case LexType::VOIDTK:
            return "VOIDTK";
        case LexType::INTCON:
            return "INTCON";
        case LexType::STRCON:
            return "STRCON";
        case LexType::NOT:
            return "NOT";
        case LexType::AND:
            return "AND";
        case LexType::OR:
            return "OR";
        case LexType::PLUS:
            return "PLUS";
        case LexType::MINU:
            return "MINU";
        case LexType::MULT:
            return "MULT";
        case LexType::DIV:
            return "DIV";
        case LexType::MOD:
            return "MOD";
        case LexType::LSS:
            return "LSS";
        case LexType::LEQ:
            return "LEQ";
        case LexType::GRE:
            return "GRE";
        case LexType::GEQ:
            return "GEQ";
        case LexType::EQL:
            return "EQL";
        case LexType::NEQ:
            return "NEQ";
        case LexType::ASSIGN:
            return "ASSIGN";
        case LexType::SEMICN:
            return "SEMICN";
        case LexType::COMMA:
            return "COMMA";
        case LexType::LPARENT:
            return "LPARENT";
        case LexType::RPARENT:
            return "RPARENT";
        case LexType::LBRACK:
            return "LBRACK";
        case LexType::RBRACK:
            return "RBRACK";
        case LexType::LBRACE:
            return "LBRACE";
        case LexType::RBRACE:
            return "RBRACE";
        case LexType::NONE:
            return "NONE";
        default:
            return "NONE";
    }
}

#endif //SYSY_COMPILER_LEXTYPE_H
