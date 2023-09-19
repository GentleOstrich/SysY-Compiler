//
// Created by yh on 2023/9/18.
//
#include <iostream>
#include <fstream>
#include "Lexer.h"
//#define TEST
using namespace std;

#ifdef TEST
string INFILEPATH = "D:\\University\\Study\\2023fall\\compiler\\SysY-Compiler\\testfile.txt";//
string OUTFILEPATH = "D:\\University\\Study\\2023fall\\compiler\\SysY-Compiler\\output.txt";//
#else
string INFILEPATH = "testfile.txt"; //
string OUTFILEPATH = "output.txt"; //
#endif

string LexType2String(LexType lexType) {
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
        case LexType::ERROR:
            return "ERROR";
        default:
            return "ERROR";
    }
}

int main() {
    Lexer lexer;
    ifstream ifs(INFILEPATH);
    ofstream ofs(OUTFILEPATH);
    string source;
    if (ifs.is_open() && ofs.is_open()) {
        source = string((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        lexer.setSource(source);
        while (1) {
            bool isEnd = lexer.next();
            if (isEnd) {
                break;
            }
            string token = lexer.getToken();
            LexType lexType = lexer.getLexType();
            //cout << LexType2String(lexType) << " " << token << endl;
            ofs << LexType2String(lexType) << " " << token << endl;
        }
    }


    return 0;
}
