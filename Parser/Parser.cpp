//
// Created by yh on 2023/9/25.
//
#include "Parser.h"
#include <iostream>
#include <fstream>

#define tkType token.first
#define tkWord token.second
#define readTk token = (lexer.next() == 0) ? lexer.getToken() : make_pair(LexType::NONE, "")
#define printTk ofs << LexType2String(tkType) << " " << tkWord << endl
#define preRead lexer.nnext()
#define prePreRead lexer.nnnext()
#define printError(lineNum, errorType) e_ofs << lineNum << errorType << endl;

using namespace std;

extern Lexer lexer;
extern ifstream ifs;
extern ofstream ofs;
extern ofstream e_ofs;
Token token = make_pair(LexType::NONE, "");

// 正常返回 0 错误返回 -1
int Parser::parseCompUnit() {
    readTk;
    while (tkType != LexType::NONE) {
        if (tkType == LexType::CONSTTK) {
            int Decl = parseDecl();
            if (Decl != 0) {
                return -1;
            }
        } else if (tkType == LexType::INTTK) {
            if (preRead == LexType::MAINTK) {
                int MainFuncDef = parseMainFuncDef();
                if (MainFuncDef != 0) {
                    return -1;
                }
            } else if (preRead == LexType::IDENFR) {
                if (prePreRead == LexType::LPARENT) {
                    int FuncDef = parseFuncDef();
                    if (FuncDef != 0) {
                        return -1;
                    }
                } else {
                    int Decl = parseDecl();
                    if (Decl != 0) {
                        return -1;
                    }
                }
            } else {
                return -1;
            }
        } else if (tkType == LexType::VOIDTK) {
            int FuncDef = parseFuncDef();
            if (FuncDef != 0) {
                return -1;
            }
        } else {
            return -1;
        }
    }
    ofs << "<CompUnit>" << endl;
    return 0;
}

int Parser::parseDecl() {
    if (tkType == LexType::CONSTTK) {
        int ConstDecl = parseConstDecl();
        if (ConstDecl != 0) {
            return -1;
        } else {
            return 0;
        }
    } else if (tkType == LexType::INTTK) {
        int VarDecl = parseVarDecl();
        if (VarDecl != 0) {
            return -1;
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseConstDecl() {
    if (tkType == LexType::CONSTTK) {
        printTk;
        readTk;
        if (tkType == LexType::INTTK) {
            printTk;
            readTk;
            int ConstDef = parseConstDef();
            if (ConstDef != 0) {
                return -1;
            } else {
                while (tkType == LexType::COMMA) {
                    printTk;
                    readTk;
                    int ConstDef = parseConstDef();
                    if (ConstDef != 0) {
                        return -1;
                    }
                }
            }
        } else {
            return -1;
        }
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<ConstDecl>" << endl;
            readTk;
            return 0;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseBType() {
    if (tkType == LexType::INTTK) {
        printTk;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseConstDef() {
    if (tkType == LexType::IDENFR) {
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int ConstExp = parseConstExp();
            if (ConstExp != 0) {
                return -1;
            } else {
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    return -1;
                }
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            int ConstInitVal = parseConstInitVal();
            if (ConstInitVal != 0) {
                return -1;
            } else {
                ofs << "<ConstDef>" << endl;
                return 0;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseConstInitVal() {
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<ConstInitVal>" << endl;
            readTk;
            return 0;
        }
        int ConstInitVal = parseConstInitVal();
        if (ConstInitVal != 0) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int ConstInitVal = parseConstInitVal();
                if (ConstInitVal != 0) {
                    return -1;
                }
            }
            if (tkType == LexType::RBRACE) {
                printTk;
                ofs << "<ConstInitVal>" << endl;
                readTk;
                return 0;
            } else {
                return -1;
            }
        }
    } else {
        int ConstExp = parseConstExp();
        if (ConstExp != 0) {
            return -1;
        } else {
            ofs << "<ConstInitVal>" << endl;
            return 0;
        }
    }
}

int Parser::parseVarDecl() {
    int BType = parseBType();
    if (BType != 0) {
        return -1;
    } else {
        int VarDef = parseVarDef();
        if (VarDef != 0) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int VarDef = parseVarDef();
                if (VarDef != 0) {
                    return -1;
                }
            }
            if (tkType == LexType::SEMICN) {
                printTk;
                ofs << "<VarDecl>" << endl;
                readTk;
                return 0;
            } else {
                return -1;
            }
        }
    }
}

int Parser::parseVarDef() {
    if (tkType == LexType::IDENFR) {
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int ConstExp = parseConstExp();
            if (ConstExp != 0) {
                return -1;
            } else {
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    return -1;
                }
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            int InitVal = parseInitVal();
            if (InitVal != 0) {
                return -1;
            } else {
                ofs << "<VarDef>" << endl;
                return 0;
            }
        } else {
            ofs << "<VarDef>" << endl;
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseInitVal() {
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<InitVal>" << endl;
            readTk;
            return 0;
        }
        int InitVal = parseInitVal();
        if (InitVal != 0) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int InitVal = parseInitVal();
                if (InitVal != 0) {
                    return -1;
                }
            }
            if (tkType == LexType::RBRACE) {
                printTk;
                ofs << "<InitVal>" << endl;
                readTk;
                return 0;
            } else {
                return -1;
            }
        }
    } else {
        int Exp = parseExp();
        if (Exp != 0) {
            return -1;
        } else {
            ofs << "<InitVal>" << endl;
            return 0;
        }
    }
}

int Parser::parseFuncDef() {
    int FuncType = parseFuncType();
    if (FuncType != 0) {
        return -1;
    } else {
        if (tkType == LexType::IDENFR) {
            printTk;
            readTk;
            if (tkType == LexType::LPARENT) {
                printTk;
                readTk;
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                } else {
                    int FuncFParams = parseFuncFParams();
                    if (FuncFParams != 0) {
                        return FuncFParams;
                    } else {
                        if (tkType == LexType::RPARENT) {
                            printTk;
                            readTk;
                        } else {
                            return -1;
                        }
                    }
                }
                int Block = parseBlock();
                if (Block == 0) {
                    ofs << "<FuncDef>" << endl;
                    return 0;
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
}

int Parser::parseMainFuncDef() {
    if (tkType == LexType::INTTK) {
        printTk;
        readTk;
        if (tkType == LexType::MAINTK) {
            printTk;
            readTk;
            if (tkType == LexType::LPARENT) {
                printTk;
                readTk;
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                    int Block = parseBlock();
                    if (Block != 0) {
                        return -1;
                    } else {
                        ofs << "<MainFuncDef>" << endl;
                        return 0;
                    }
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseFuncType() {
    if (tkType == LexType::INTTK) {
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return 0;
    } else if (tkType == LexType::VOIDTK) {
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseFuncFParams() {
    int FuncFParam = parseFuncFParam();
    if (FuncFParam != 0) {
        return -1;
    }
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        int FuncFParam = parseFuncFParam();
        if (FuncFParam != 0) {
            return -1;
        }
    }
    ofs << "<FuncFParams>" << endl;
    return 0;
}

int Parser::parseFuncFParam() {
    if (tkType == LexType::INTTK) {
        printTk;
        readTk;
        if (tkType == LexType::IDENFR) {
            printTk;
            readTk;
            if (tkType == LexType::LBRACK) {
                printTk;
                readTk;
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    return -1;
                }
                while (tkType == LexType::LBRACK) {
                    printTk;
                    readTk;
                    int ConstExp = parseConstExp();
                    if (ConstExp != 0) {
                        return -1;
                    } else {
                        if (tkType == LexType::RBRACK) {
                            printTk;
                            readTk;
                        } else {
                            return -1;
                        }
                    }
                }
                ofs << "<FuncFParam>" << endl;
                return 0;
            } else {
                ofs << "<FuncFParam>" << endl;
                return 0;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseBlock() {
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        while (tkType != LexType::RBRACE) {
            int BlockItem = parseBlockItem();
            if (BlockItem != 0) {
                return -1;
            }
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<Block>" << endl;
            readTk;
            return 0;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseBlockItem() {
    int Decl = parseDecl();
    if (Decl == 0) {
        return 0;
    } else {
        int Stmt = parseStmt();
        if (Stmt != 0) {
            return -1;
        } else {
            return 0;
        }
    }
}

int Parser::parseStmt() {
    if (tkType == LexType::IFTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            int Cond = parseCond();
            if (Cond != 0) {
                return -1;
            } else {
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                    int Stmt = parseStmt();
                    if (Stmt != 0) {
                        return -1;
                    } else {
                        if (tkType == LexType::ELSETK) {
                            printTk;
                            readTk;
                            int Stmt = parseStmt();
                            if (Stmt != 0) {
                                return -1;
                            } else {
                                ofs << "<Stmt>" << endl;
                                return 0;
                            }
                        } else {
                            ofs << "<Stmt>" << endl;
                            return 0;
                        }
                    }
                } else {
                    return -1;
                }
            }
        } else {
            return -1;
        }
    } else if (tkType == LexType::FORTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            int ForStmt = parseForStmt();
            if (tkType == LexType::SEMICN) {
                printTk;
                readTk;
                int Cond = parseCond();
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                    int ForStmt = parseForStmt();
                    if (tkType == LexType::RPARENT) {
                        printTk;
                        readTk;
                        int Stmt = parseStmt();
                        if (Stmt != 0) {
                            return -1;
                        } else {
                            ofs << "<Stmt>" << endl;
                            return 0;
                        }
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else if (tkType == LexType::BREAKTK) {
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            return -1;
        }
    } else if (tkType == LexType::CONTINUETK) {
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            return -1;
        }
    } else if (tkType == LexType::RETURNTK) {
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            int Exp = parseExp();
            if (Exp != 0) {
                return -1;
            } else {
                if (tkType == LexType::SEMICN) {
                    printTk;
                    ofs << "<Stmt>" << endl;
                    readTk;
                    return 0;
                } else {
                    return -1;
                }
            }
        }
    } else if (tkType == LexType::PRINTFTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::STRCON) {
                printTk;
                readTk;
                while (tkType == LexType::COMMA) {
                    printTk;
                    readTk;
                    int Exp = parseExp();
                    if (Exp != 0) {
                        return -1;
                    }
                }
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                    if (tkType == LexType::SEMICN) {
                        printTk;
                        ofs << "<Stmt>" << endl;
                        readTk;
                        return 0;
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else if (tkType == LexType::LBRACE) {
        int Block = parseBlock();
        if (Block != 0) {
            return -1;
        } else {
            ofs << "<Stmt>" << endl;
            return 0;
        }
    } else {
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            if (lexer.hasAUntilB('=', ';')) {
                int LVal = parseLVal();
                if (LVal == 0) {
                    if (tkType == LexType::ASSIGN) {
                        printTk;
                        readTk;
                        if (tkType == LexType::GETINTTK) {
                            printTk;
                            readTk;
                            if (tkType == LexType::LPARENT) {
                                printTk;
                                readTk;
                                if (tkType == LexType::RPARENT) {
                                    printTk;
                                    readTk;
                                    if (tkType == LexType::SEMICN) {
                                        printTk;
                                        ofs << "<Stmt>" << endl;
                                        readTk;
                                        return 0;
                                    } else {
                                        return -1;
                                    }
                                } else {
                                    return -1;
                                }
                            } else {
                                return -1;
                            }
                        } else {
                            int Exp = parseExp();
                            if (Exp != 0) {
                                return -1;
                            } else {
                                if (tkType == LexType::SEMICN) {
                                    printTk;
                                    ofs << "<Stmt>" << endl;
                                    readTk;
                                    return 0;
                                } else {
                                    return -1;
                                }
                            }
                        }
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            } else {
                int Exp = parseExp();
                if (Exp != 0) {
                    return -1;
                } else {
                    if (tkType == LexType::SEMICN) {
                        printTk;
                        ofs << "<Stmt>" << endl;
                        readTk;
                        return 0;
                    } else {
                        return -1;
                    }
                }
            }

        }


    }
    return 0;
}

int Parser::parseForStmt() {
    int LVal = parseLVal();
    if (LVal == 0) {
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            int Exp = parseExp();
            if (Exp == 0) {
                ofs << "<ForStmt>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        ofs << "<Exp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseCond() {
    int LOrExp = parseLOrExp();
    if (LOrExp == 0) {
        ofs << "<Cond>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseLVal() {
    if (tkType == LexType::IDENFR) {
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int Exp = parseExp();
            if (Exp != 0) {
                return -1;
            }
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
                return -1;
            }
        }
        ofs << "<LVal>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parsePrimaryExp() {
    if (tkType == LexType::LPARENT) {
        printTk;
        readTk;
        int Exp = parseExp();
        if (Exp == 0) {
            if (tkType == LexType::RPARENT) {
                printTk;
                ofs << "<PrimaryExp>" << endl;
                readTk;
                return 0;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        int Number = parseNumber();
        if (Number == 0) {
            ofs << "<PrimaryExp>" << endl;
            return 0;
        } else {
            int LVal = parseLVal();
            if (LVal == 0) {
                ofs << "<PrimaryExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        }
    }
}

int Parser::parseNumber() {
    if (tkType == LexType::INTCON) {
        printTk;
        ofs << "<Number>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseUnaryExp() {
    int UnaryOp = parseUnaryOp();
    if (UnaryOp == 0) {
        int UnaryExp = parseUnaryExp();
        if (UnaryExp == 0) {
            ofs << "<UnaryExp>" << endl;
            return 0;
        } else {
            return -1;
        }
    } else {
        if (tkType == LexType::IDENFR && preRead == LexType::LPARENT) {
            printTk;
            readTk;
            printTk;
            readTk;
            if (tkType == LexType::RPARENT) {
                printTk;
                ofs << "<UnaryExp>" << endl;
                readTk;
                return 0;
            } else {
                int FuncRParams = parseFuncRParams();
                if (FuncRParams == 0) {
                    if (tkType == LexType::RPARENT) {
                        printTk;
                        ofs << "<UnaryExp>" << endl;
                        readTk;
                        return 0;
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }
            }
        } else {
            int PrimaryExp = parsePrimaryExp();
            if (PrimaryExp == 0) {
                ofs << "<UnaryExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        }
    }
}

int Parser::parseUnaryOp() {
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        printTk;
        ofs << "<UnaryOp>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseFuncRParams() {
    int Exp = parseExp();
    if (Exp == 0) {
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            int Exp = parseExp();
            if (Exp != 0) {
                return -1;
            }
        }
        ofs << "<FuncRParams>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseMulExp() {
    int UnaryExp = parseUnaryExp();
    if (UnaryExp == 0) {
        while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
            ofs << "<MulExp>" << endl;
            printTk;
            readTk;
            int UnaryExp = parseUnaryExp();
            if (UnaryExp != 0) {
                return -1;
            }
        }
        ofs << "<MulExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseAddExp() {
    int MulExp = parseMulExp();
    if (MulExp == 0) {
        while (tkType == LexType::PLUS || tkType == LexType::MINU) {
            ofs << "<AddExp>" << endl;
            printTk;
            readTk;
            int MulExp = parseMulExp();
            if (MulExp != 0) {
                return -1;
            }
        }
        ofs << "<AddExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseRelExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        while (tkType == LexType::GRE || tkType == LexType::GEQ ||
               tkType == LexType::LSS || tkType == LexType::LEQ) {
            ofs << "<RelExp>" << endl;
            printTk;
            readTk;
            int AddExp = parseAddExp();
            if (AddExp != 0) {
                return -1;
            }
        }
        ofs << "<RelExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

//TODO
int Parser::parseEqExp() {
    int RelExp = parseRelExp();
    if (RelExp == 0) {
        while (tkType == LexType::EQL || tkType == LexType::NEQ) {
            ofs << "<EqExp>" << endl;
            printTk;
            readTk;
            int RelExp = parseRelExp();
            if (RelExp != 0) {
                return -1;
            }
        }
        ofs << "<EqExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseLAndExp() {
    int EqExp = parseEqExp();
    if (EqExp == 0) {
        while (tkType == LexType::AND) {
            ofs << "<LAndExp>" << endl;
            printTk;
            readTk;
            int EqExp = parseEqExp();
            if (EqExp != 0) {
                return -1;
            }
        }
        ofs << "<LAndExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseLOrExp() {
    int LAndExp = parseLAndExp();
    if (LAndExp == 0) {
        while (tkType == LexType::OR) {
            ofs << "<LOrExp>" << endl;
            printTk;
            readTk;
            int LAndExp = parseLAndExp();
            if (LAndExp != 0) {
                return -1;
            }
        }
        ofs << "<LOrExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseConstExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        ofs << "<ConstExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}