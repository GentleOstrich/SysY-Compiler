//
// Created by yh on 2023/9/25.
//
#include "Parser.h"
#include <iostream>

#define readToken token = (lexer.next() == 0) ? lexer.getToken() : make_pair(LexType::NONE, nullptr);
#define LEXTYPE token.first
using namespace std;
extern Lexer lexer;
Token token = make_pair(LexType::NONE, nullptr);

// 正常返回 0 错误返回 -1
int Parser::parseCompUnit() {
    readToken;
    while (LEXTYPE != LexType::NONE) {
        if (LEXTYPE == LexType::CONSTTK) {
            int Decl = parseDecl();
            if (Decl == 0) {
                cout << "<Decl>" << endl;
            } else {
                return Decl;
            }
        } else if (LEXTYPE == LexType::INTTK) {
            LexType nnextType = lexer.nnext();
            if (nnextType == LexType::MAINTK) {
                int MainFuncDef = parseMainFuncDef();
                if (MainFuncDef == 0) {
                    cout << "<MainFuncDef>" << endl;
                    return 0;
                } else {
                    return MainFuncDef;
                }
            } else if (nnextType == LexType::IDENFR) {
                LexType nnnextType = lexer.nnnext();
                if (nnnextType == LexType::LPARENT) {
                    int FuncDef = parseFuncDef();
                    if (FuncDef == 0) {
                        cout << "<FuncDef" << endl;
                    } else {
                        return FuncDef;
                    }
                } else if (nnnextType == LexType::ASSIGN) {
                    int Decl = parseDecl();
                    if (Decl == 0) {
                        cout << "<Decl>" << endl;
                    } else {
                        return Decl;
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
}

int Parser::parseDecl() {
    if (LEXTYPE == LexType::CONSTTK) {
        int ConstDecl = parseConstDecl();
        if (ConstDecl == 0) {
            cout << "<ConstDecl>" << endl;
        }
        return ConstDecl;
    } else if (LEXTYPE == LexType::INTTK) {
        int VarDecl = parseVarDecl();
        if (VarDecl == 0) {
            cout << "<VarDecl>" << endl;
        }
        return VarDecl;
    }
    return 0;
}

int Parser::parseConstDecl() {
    if (LEXTYPE == LexType::CONSTTK) {
        readToken;
        if (LEXTYPE == LexType::INTTK) {
            readToken;
            int ConstDef = parseConstDef();
            if (ConstDef == 0) {
                cout << "<ConstDef>" << endl;
                while (LEXTYPE == LexType::COMMA) {
                    readToken;
                    int ConstDef = parseConstDef();
                    if (ConstDef == 0) {
                        cout << "<ConstDef>" << endl;
                    } else {
                        return ConstDef;
                    }
                }
            } else {
                return ConstDef;
            }
        } else {
            return -1;
        }
        if (LEXTYPE == LexType::SEMICN) {
            readToken;
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseBType() {
    if (LEXTYPE == LexType::INTTK) {
        readToken;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseConstDef() {
    if (LEXTYPE == LexType::IDENFR) {
        readToken;
        while (LEXTYPE == LexType::LBRACK) {
            readToken;
            int ConstExp = parseConstExp();
            if (ConstExp == 0) {
                cout << "<ConstExp>" << endl;
                if (LEXTYPE == LexType::RBRACK) {
                    readToken;
                } else {
                    return -1;
                }
            } else {
                return ConstExp;
            }
        }
        if (LEXTYPE == LexType::ASSIGN) {
            readToken;
            int ConstInitVal = parseConstInitVal();
            if (ConstInitVal == 0) {
                cout << "<ConstInitVal>" << endl;
                return 0;
            } else {
                return ConstInitVal;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseConstInitVal() {
    if (LEXTYPE == LexType::LBRACE) {
        readToken;
        if (LEXTYPE == LexType::RBRACE) {
            readToken;
            return 0;
        }
        int ConstInitVal = parseConstInitVal();
        if (ConstInitVal == 0) {
            cout << "<ConstInitVal>" << endl;
            while (LEXTYPE == LexType::COMMA) {
                readToken;
                int ConstInitVal = parseConstInitVal();
                if (ConstInitVal == 0) {
                    cout << "<ConstInitVal>" << endl;
                } else {
                    return ConstInitVal;
                }
            }
            if (LEXTYPE == LexType::RBRACE) {
                readToken;
                return 0;
            } else {
                return -1;
            }
        } else {
            return ConstInitVal;
        }
    } else {
        int ConstExp = parseConstExp();
        if (ConstExp == 0) {
            cout << "<ConstExp>" << endl;
            return 0;
        } else {
            return ConstExp;
        }
    }
}

int Parser::parseVarDecl() {
    int BType = parseBType();
    if (BType == 0) {
        int VarDef = parseVarDef();
        if (VarDef == 0) {
            cout << "<VarDef>" << endl;
            while (LEXTYPE == LexType::COMMA) {
                readToken;
                int VarDef = parseVarDef();
                if (VarDef == 0) {
                    cout << "<VarDef>" << endl;
                } else {
                    return VarDef;
                }
            }
            if (LEXTYPE == LexType::SEMICN) {
                readToken;
                return 0;
            } else {
                return -1;
            }
        } else {
            return VarDef;
        }
    } else {
        return BType;
    }
}

int Parser::parseVarDef() {
    if (LEXTYPE == LexType::IDENFR) {
        readToken;
        while (LEXTYPE == LexType::LBRACK) {
            readToken;
            int ConstExp = parseConstExp();
            if (ConstExp == 0) {
                cout << "<ConstExp>" << endl;
                if (LEXTYPE == LexType::RBRACK) {
                    readToken;
                } else {
                    return -1;
                }
            } else {
                return ConstExp;
            }
        }
        if (LEXTYPE == LexType::ASSIGN) {
            readToken;
            int InitVal = parseInitVal();
            if (InitVal == 0) {
                cout << "<InitVal>" << endl;
                return 0;
            } else {
                return InitVal;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseInitVal() {
    if (LEXTYPE == LexType::LBRACE) {
        readToken;
        if (LEXTYPE == LexType::RBRACE) {
            readToken;
            return 0;
        }
        int InitVal = parseInitVal();
        if (InitVal == 0) {
            cout << "<InitVal>" << endl;
            while (LEXTYPE == LexType::COMMA) {
                int InitVal = parseInitVal();
                if (InitVal == 0) {
                    cout << "<InitVal>" << endl;
                } else {
                    return InitVal;
                }
            }
            if (LEXTYPE == LexType::RBRACE) {
                return 0;
            } else {
                return -1;
            }
        } else {
            return InitVal;
        }
    } else {
        int Exp = parseExp();
        if (Exp == 0) {
            cout << "<Exp>" << endl;
            return 0;
        } else {
            return Exp;
        }
    }
}

int Parser::parseFuncDef() {
    int FuncType = parseFuncType();
    if (FuncType == 0) {
        cout << "<FuncType>" << endl;
        if (LEXTYPE == LexType::IDENFR) {
            readToken;
            if (LEXTYPE == LexType::LPARENT) {
                readToken;
                if (LEXTYPE == LexType::RPARENT) {
                    readToken;
                } else {
                    int FuncFParams = parseFuncFParams();
                    if (FuncFParams == 0) {
                        cout << "<FuncFParams>" << endl;
                        if (LEXTYPE == LexType::RPARENT) {
                            readToken;
                        } else {
                            return -1;
                        }
                    } else {
                        return FuncFParams;
                    }
                }
                int Block = parseBlock();
                if (Block == 0) {
                    cout << "<Block>" << endl;
                    return 0;
                } else {
                    return Block;
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

int Parser::parseMainFuncDef() {
    if (LEXTYPE == LexType::INTTK) {
        readToken;
        if (LEXTYPE == LexType::MAINTK) {
            readToken;
            if (LEXTYPE == LexType::LPARENT) {
                readToken;
                if (LEXTYPE == LexType::RPARENT) {
                    readToken;
                    int Block = parseBlock();
                    if (Block == 0) {
                        cout << "<Block>" << endl;
                        return 0;
                    } else {
                        return Block;
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
}

int Parser::parseFuncType() {
    if (LEXTYPE == LexType::INTTK) {
        readToken;
        return 0;
    } else if (LEXTYPE == LexType::VOIDTK) {
        readToken;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseFuncFParams() {
    int FuncFParam = parseFuncFParam();
    if (FuncFParam == 0) {
        cout << "<FuncFParam>" << endl;
    } else {
        return FuncFParam;
    }
    while (LEXTYPE == LexType::COMMA) {
        readToken;
        int FuncFParam = parseFuncFParam();
        if (FuncFParam == 0) {
            cout << "<FuncFParam>" << endl;
        } else {
            return FuncFParam;
        }
    }
    return 0;
}

int Parser::parseFuncFParam() {
    if (LEXTYPE == LexType::INTTK) {
        readToken;
        if (LEXTYPE == LexType::IDENFR) {
            readToken;
            if (LEXTYPE == LexType::LBRACK) {
                readToken;
                if (LEXTYPE == LexType::RBRACK) {
                    readToken;
                } else {
                    return -1;
                }
                while (LEXTYPE == LexType::LBRACK) {
                    readToken;
                    int ConstExp = parseConstExp();
                    if (ConstExp == 0) {
                        cout << "<ConstExp>" << endl;
                        if (LEXTYPE == LexType::RBRACK) {
                            readToken;
                        } else {
                            return -1;
                        }
                    } else {
                        return ConstExp;
                    }
                }
                return 0;
            } else {
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
    if (LEXTYPE == LexType::LBRACE) {
        readToken;
        if (LEXTYPE == LexType::RBRACE) {
            readToken;
            return 0;
        }
        int BlockItem = parseBlockItem();
        if (BlockItem == 0) {
            if (LEXTYPE == LexType::RBRACE) {
                readToken;
                return 0;
            } else {
                return -1;
            }
        } else {
            return BlockItem;
        }
    } else {
        return -1;
    }
}

int Parser::parseBlockItem() {
    int Decl = parseDecl();
    if (Decl == 0) {
        cout << "<Decl>" << endl;
        return 0;
    } else {
        int Stmt = parseStmt();
        if (Stmt == 0) {
            cout << "<Stmt>" << endl;
            return 0;
        } else {
            return -1;
        }
    }
}

int Parser::parseStmt() {
    if (LEXTYPE == LexType::IFTK) {
        readToken;
        if (LEXTYPE == LexType::LPARENT) {
            readToken;
            int Cond = parseCond();
            if (Cond == 0) {
                if (LEXTYPE == LexType::RPARENT) {
                    readToken;
                    int Stmt = parseStmt();
                    if (Stmt == 0) {
                        cout << "<Stmt>" << endl;
                        if (LEXTYPE == LexType::ELSETK) {
                            readToken;
                            int Stmt = parseStmt();
                            if (Stmt == 0) {
                                cout << "<Stmt>" << endl;
                                return 0;
                            } else {
                                return Stmt;
                            }
                        }
                    } else {
                        return Stmt;
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
    } else if (LEXTYPE == LexType::FORTK) {
        readToken;
        if (LEXTYPE == LexType::LPARENT) {
            readToken;
            int ForStmt = parseForStmt();
            if (ForStmt == 0) {
                cout << "<ForStmt>" << endl;
            }
            if (LEXTYPE == LexType::SEMICN) {
                readToken;
                int Cond = parseCond();
                if (Cond == 0) {
                    cout << "<Cond>" << endl;
                }
                if (LEXTYPE == LexType::SEMICN) {
                    readToken;
                    int ForStmt = parseForStmt();
                    if (ForStmt == 0) {
                        cout << "<ForStmt>" << endl;
                    }
                    if (LEXTYPE == LexType::RPARENT) {
                        readToken;
                        int Stmt = parseStmt();
                        if (Stmt == 0) {
                            cout << "<Stmt>" << endl;
                            return 0;
                        } else {
                            return Stmt;
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
    } else if (LEXTYPE == LexType::BREAKTK) {
        readToken;
        if (LEXTYPE == LexType::SEMICN) {
            readToken;
            return 0;
        } else {
            return -1;
        }
    } else if (LEXTYPE == LexType::CONTINUETK) {
        readToken;
        if (LEXTYPE == LexType::SEMICN) {
            readToken;
            return 0;
        } else {
            return -1;
        }
    } else if (LEXTYPE == LexType::RETURNTK) {
        readToken;
        if (LEXTYPE == LexType::SEMICN) {
            readToken;
            return 0;
        } else {
            int Exp = parseExp();
            if (Exp == 0) {
                if (LEXTYPE == LexType::SEMICN) {
                    readToken;
                    return 0;
                } else {
                    return -1;
                }
            } else {
                return Exp;
            }
        }
    } else if (LEXTYPE == LexType::PRINTFTK) {
        readToken;
        if (LEXTYPE == LexType::LPARENT) {
            readToken;
            if (LEXTYPE == LexType::STRCON) {
                readToken;
                while (LEXTYPE == LexType::COMMA) {
                    readToken;
                    int Exp = parseExp();
                    if (Exp == 0) {
                        cout << "<Exp>" << endl;
                    } else {
                        return -1;
                    }
                }
                if (LEXTYPE == LexType::RPARENT) {
                    readToken;
                    if (LEXTYPE == LexType::SEMICN) {
                        readToken;
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
    } else {
        int LVal = parseLVal();
        if (LVal == 0) {
            if (LEXTYPE == LexType::ASSIGN) {
                readToken;
                if (LEXTYPE == LexType::GETINTTK) {
                    readToken;
                    if (LEXTYPE == LexType::LPARENT) {
                        readToken;
                        if (LEXTYPE == LexType::RPARENT) {
                            readToken;
                            if (LEXTYPE == LexType::SEMICN) {
                                readToken;
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
                    if (Exp == 0) {
                        cout << "<Exp>" << endl;
                        if (LEXTYPE == LexType::SEMICN) {
                            readToken;
                            return 0;
                        } else {
                            return -1;
                        }
                    } else {
                        return -1;
                    }
                }
            } else {
                return -1;
            }
        } else {
            if (LEXTYPE == LexType::LBRACE) {
                int Block = parseBlock();
                if (Block == 0) {
                    cout << "<Block>" << endl;
                    return 0;
                } else {
                    return Block;
                }
            } else {
                if (LEXTYPE == LexType::SEMICN) {
                    readToken;
                    return 0;
                } else {
                    int Exp = parseExp();
                    if (Exp == 0) {
                        cout << "<Exp>" << endl;
                        if (LEXTYPE == LexType::SEMICN) {
                            readToken;
                            return 0;
                        } else {
                            return -1;
                        }
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
        cout << "<LVal>" << endl;
        if (LEXTYPE == LexType::ASSIGN) {
            readToken;
            int Exp = parseExp();
            if (Exp == 0) {
                cout << "<Exp>" << endl;
                return 0;
            } else {
                return Exp;
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
        cout << "<AddExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseCond() {
    int LOrExp = parseLOrExp();
    if (LOrExp == 0) {
        cout << "<LOrExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseLVal() {
    if (LEXTYPE == LexType::IDENFR) {
        readToken;
        while (LEXTYPE == LexType::LBRACK) {
            readToken;
            int Exp = parseExp();
            if (Exp == 0) {
                cout << "<Exp>" << endl;
            } else {
                return Exp;
            }
            if (LEXTYPE == LexType::RBRACK) {
                readToken;
            } else {
                return -1;
            }
        }
        return 0;
    } else {
        return -1;
    }
}

int Parser::parsePrimaryExp() {
    if (LEXTYPE == LexType::LPARENT) {
        int Exp = parseExp();
        if (Exp == 0) {
            cout << "<Exp>" << endl;
            if (LEXTYPE == LexType::RPARENT) {
                readToken;
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
            cout << "<Number>" << endl;
            return 0;
        } else {
            int LVal = parseLVal();
            if (LVal == 0) {
                cout << "<LVal>" << endl;
                return 0;
            } else {
                return -1;
            }
        }
    }
}

int Parser::parseNumber() {
    if (LEXTYPE == LexType::INTCON) {
        readToken;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseUnaryExp() {
    int UnaryOp = parseUnaryOp();
    if (UnaryOp == 0) {
        cout << "<UnaryOp>" << endl;
        int UnaryExp = parseUnaryExp();
        if (UnaryExp == 0) {
            cout << "<UnaryExp>" << endl;
            return 0;
        } else {
            return -1;
        }
    } else {
        LexType nnType = lexer.nnnext();
        if (LEXTYPE == LexType::IDENFR && nnType == LexType::LPARENT) {
            readToken;
            readToken;
            if (LEXTYPE == LexType::RPARENT) {
                return 0;
            } else {
                int FuncRParams = parseFuncRParams();
                if (FuncRParams == 0) {
                    cout << "<FuncRParams>" << endl;
                    readToken;
                    if (LEXTYPE == LexType::RPARENT) {
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
                cout << "<PrimaryExp>" << endl;
                return 0;
            } else {
                return PrimaryExp;
            }
        }
    }
}

int Parser::parseUnaryOp() {
    if (LEXTYPE == LexType::PLUS || LEXTYPE == LexType::MINU || LEXTYPE == LexType::NOT) {
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseFuncRParams() {
    int Exp = parseExp();
    if (Exp == 0) {
        cout << "<Exp>" << endl;
        while (LEXTYPE == LexType::COMMA) {
            readToken;
            int Exp = parseExp();
            if (Exp == 0) {
                cout << "<Exp>" << endl;
            } else {
                return -1;
            }
        }
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseMulExp() {
    int UnaryExp = parseUnaryExp();
    if (UnaryExp == 0) {
        cout << "<UnaryExp>" << endl;
        if (LEXTYPE == LexType::MULT || LEXTYPE == LexType::DIV || LEXTYPE == LexType::MOD) {
            readToken;
            int MulExp = parseMulExp();
            if (MulExp == 0) {
                cout << "<MulExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseAddExp() {
    int MulExp = parseMulExp();
    if (MulExp == 0) {
        cout << "<MulExp>" << endl;
        if (LEXTYPE == LexType::PLUS || LEXTYPE == LexType::MINU) {
            readToken;
            int AddExp = parseAddExp();
            if (AddExp == 0) {
                cout << "<AddExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseRelExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        cout << "<AddExp>" << endl;
        if (LEXTYPE == LexType::GRE || LEXTYPE == LexType::GEQ ||
            LEXTYPE == LexType::LSS || LEXTYPE == LexType::LEQ) {
            readToken;
            int RelExp = parseRelExp();
            if (RelExp == 0) {
                cout << "<RelExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseEqExp() {
    int RelExp = parseRelExp();
    if (RelExp == 0) {
        cout << "<RelExp>" << endl;
        if (LEXTYPE == LexType::EQL || LEXTYPE == LexType::NEQ) {
            readToken;
            int EqExp = parseEqExp();
            if (EqExp == 0) {
                cout << "<EqExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseLAndExp() {
    int EqExp = parseEqExp();
    if (EqExp == 0) {
        cout << "<EqExp>" << endl;
        if (LEXTYPE == LexType::AND) {
            readToken;
            int LAndExp = parseLAndExp();
            if (LAndExp == 0) {
                cout << "<LAndExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseLOrExp() {
    int LAndExp = parseLAndExp();
    if (LAndExp == 0) {
        cout << "<LAndExp>" << endl;
        if (LEXTYPE == LexType::OR) {
            readToken;
            int LOrExp = parseLOrExp();
            if (LOrExp == 0) {
                cout << "<LOrExp>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return 0;
        }
    } else {
        return -1;
    }
}

int Parser::parseConstExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        cout << "<AddExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}
