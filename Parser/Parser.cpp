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
    while(true) {
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
                } else if (nnnextType == LexType::EQL) {
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
        readToken;
        return ConstDecl;
    } else if (LEXTYPE == LexType::INTTK) {
        int VarDecl = parseVarDecl();
        if (VarDecl == 0) {
            cout << "<VarDecl>" << endl;
        }
        readToken;
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
                readToken;
                if (LEXTYPE == LexType::COMMA) {
                    readToken;
                    int ConstDef = parseConstDef();
                    if (ConstDef == 0) {
                        cout << "<ConstDef>" << endl;
                        readToken;
                    } else {
                        return ConstDef;
                    }
                }
            } else {
                return ConstDef;
            }
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
        if (LEXTYPE == LexType::LBRACK) {
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
                readToken;
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
            readToken;
            if (LEXTYPE == LexType::COMMA) {
                readToken;
                int ConstInitVal = parseConstInitVal();
                if (ConstInitVal == 0) {
                    cout << "<ConstInitVal>" << endl;
                    readToken;
                    return 0;
                } else {
                    return ConstInitVal;
                }
            } else if (LEXTYPE == LexType::RBRACE) {
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
            readToken;
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
                    readToken;
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
                readToken;
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
                readToken;
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
            readToken;
            if (LEXTYPE == LexType::COMMA) {
                int InitVal = parseInitVal();
                if (InitVal == 0) {
                    cout << "<InitVal>" << endl;
                    readToken;
                    return 0;
                } else {
                    return InitVal;
                }
            } else if (LEXTYPE == LexType::RBRACE) {
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
            readToken;
            return 0;
        } else {
            return Exp;
        }
    }
    return 0;
}

int Parser::parseFuncDef() {
    int FuncType = parseFuncType();
    if (FuncType == 0) {
        cout << "<FuncType>" << endl;
        readToken;
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
                        readToken;
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
                    readToken;
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
                        readToken;
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
                if (LEXTYPE == LexType::LBRACK) {
                    readToken;
                    int ConstExp = parseConstExp();
                    if (ConstExp == 0) {
                        cout << "<ConstExp>" << endl;
                        readToken;
                        if (LEXTYPE == LexType::RBRACK) {
                            readToken;
                        } else {
                            return -1;
                        }
                    } else {
                        return ConstExp;
                    }
                }
            }
            return 0;
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
        readToken;
        return 0;
    } else {
        int Stmt = parseStmt();
        if (Stmt == 0) {
            cout << "<Stmt>" << endl;
            readToken;
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
                readToken;
                if (LEXTYPE == LexType::RPARENT) {
                    readToken;
                    int Stmt = parseStmt();
                    if (Stmt == 0) {
                        cout << "<Stmt>" << endl;
                        readToken;
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
    } else if (LEXTYPE == LexType::FORTK) {
        readToken;
        if (LEXTYPE == LexType::LPARENT) {
            readToken;
            int ForStmt = parseForStmt();
            if (ForStmt == 0) {
                cout << "<ForStmt>" << endl;
                readToken;
            }
            if (LEXTYPE == LexType::SEMICN) {
                readToken;
                int Cond = parseCond();
                if (Cond == 0) {
                    cout << "<Cond>" << endl;
                    readToken;
                }
                if (LEXTYPE == LexType::SEMICN) {
                        readToken;
                        int ForStmt = parseForStmt();
                        if (ForStmt == 0) {
                            cout << "<ForStmt>" << endl;
                            readToken;
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
        
    } else if (LEXTYPE == LexType::CONTINUETK) {
        
    } else if (LEXTYPE == LexType::RETURNTK) {
    } else if (LEXTYPE == LexType::PRINTFTK) {

    } else 
    return 0;
}

int Parser::parseForStmt() {

    return 0;
}

int Parser::parseExp() {

    return 0;
}

int Parser::parseCond() {

    return 0;
}

int Parser::parseLVal() {

    return 0;
}

int Parser::parsePrimaryExp() {

    return 0;
}

int Parser::parseNumber() {

    return 0;
}

int Parser::parseUnaryExp() {

    return 0;
}

int Parser::parseUnaryOp() {

    return 0;
}

int Parser::parseFuncRParams() {

    return 0;
}

int Parser::parseMulExp() {

    return 0;
}

int Parser::parseAddExp() {

    return 0;
}

int Parser::parseRelExp() {

    return 0;
}

int Parser::parseEqExp() {

    return 0;
}

int Parser::parseLAndExp() {

    return 0;
}

int Parser::parseLOrExp() {

    return 0;
}

int Parser::parseConstExp() {
    
    return 0;
}
