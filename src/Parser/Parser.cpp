//
// Created by yh on 2023/9/25.
//
#include "Parser.h"

#define tkType token.first
#define tkWord token.second
#define readTk token = (lexer.next() == 0) ? lexer.getToken() : make_pair(LexType::NONE, "")
#define printTk ofs << LexType2String(tkType) << " " << tkWord << endl
#define preRead lexer.nnext()
#define prePreRead lexer.nnnext()

extern Lexer lexer;
extern ifstream ifs;
extern ofstream ofs;
Token token = make_pair(LexType::NONE, "");

// 正常返回 0 错误返回 -1
CompUnit Parser::parseCompUnit() {
    CompUnit compUnit;
    readTk;
    while (tkType != LexType::NONE) {
        if (tkType == LexType::CONSTTK) {
            Decl decl = parseDecl();
            compUnit.addDecl(&decl);
        } else if (tkType == LexType::INTTK) {
            if (preRead == LexType::MAINTK) {
                MainFuncDef mainFuncDef = parseMainFuncDef();
                compUnit.setMainFuncDef(&mainFuncDef);
            } else if (preRead == LexType::IDENFR) {
                if (prePreRead == LexType::LPARENT) {
                    FuncDef funcDef = parseFuncDef();
                    compUnit.addFuncDef(&funcDef);
                } else {
                    Decl decl = parseDecl();
                    compUnit.addDecl(&decl);
                }
            }
        } else if (tkType == LexType::VOIDTK) {
            FuncDef funcDef = parseFuncDef();
            compUnit.addFuncDef(&funcDef);
        }
    }
    ofs << "<CompUnit>" << endl;
    return compUnit;
}

Decl Parser::parseDecl() {
    Decl decl;
    if (tkType == LexType::CONSTTK) {
        ConstDecl constDecl = parseConstDecl();
        decl.setConstDecl(&constDecl);
    } else if (tkType == LexType::INTTK) {
        VarDecl varDecl = parseVarDecl();
        decl.setVarDecl(&varDecl);
    }
    return decl;
}

ConstDecl Parser::parseConstDecl() {
    ConstDecl constDecl;
    if (tkType == LexType::CONSTTK) {
        printTk;
        readTk;
        if (tkType == LexType::INTTK) {
            printTk;
            readTk;
            ConstDef constDef = parseConstDef();
            constDecl.addConstDef(&constDef);
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                ConstDef constDef = parseConstDef();
                constDecl.addConstDef(&constDef);
            }
        }
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<ConstDecl>" << endl;
            readTk;
            return constDecl;
        }
    }
}

Btype Parser::parseBType() {
    if (tkType == LexType::INTTK) {
        Btype btype("int");
        printTk;
        readTk;
        return btype;
    }
}

ConstDef Parser::parseConstDef() {
    ConstDef constDef;
    if (tkType == LexType::IDENFR) {
        Ident ident(tkWord);
        constDef.setIdent(&ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            ConstExp constExp = parseConstExp();
            constDef.addConstExps(&constExp);
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            ConstInitVal constInitVal = parseConstInitVal();
            constDef.setConstInitVal(&constInitVal);
            ofs << "<ConstDef>" << endl;
            return constDef;
        }
    }
}

ConstInitVal Parser::parseConstInitVal() {
    ConstInitVal constInitVal;
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<ConstInitVal>" << endl;
            readTk;
            return constInitVal;
        }
        ConstInitVal son_constInitVal1 = parseConstInitVal();
        constInitVal.addConstInitVal(&son_constInitVal1);
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            ConstInitVal son_constInitVal = parseConstInitVal();
            constInitVal.addConstInitVal(&son_constInitVal);
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<ConstInitVal>" << endl;
            readTk;
            return constInitVal;
        }
    } else {
        ConstExp constExp = parseConstExp();
        constInitVal.setConstExp(&constExp);
        ofs << "<ConstInitVal>" << endl;
        return constInitVal;
    }
}

VarDecl Parser::parseVarDecl() {
    VarDecl varDecl;
    Btype btype = parseBType();
    varDecl.setBType(&btype);
    VarDef varDef = parseVarDef();
    varDecl.addVarDef(&varDef);
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        VarDef varDef = parseVarDef();
        varDecl.addVarDef(&varDef);
    }
    if (tkType == LexType::SEMICN) {
        printTk;
        ofs << "<VarDecl>" << endl;
        readTk;
        return varDecl;
    }
}

VarDef Parser::parseVarDef() {
    VarDef varDef;
    if (tkType == LexType::IDENFR) {
        Ident ident(tkWord);
        varDef.setIdent(&ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            ConstExp constExp = parseConstExp();
            varDef.addConstExp(&constExp);
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            InitVal initVal = parseInitVal();
            varDef.setInitVal(&initVal);
            ofs << "<VarDef>" << endl;
            return varDef;
        } else {
            ofs << "<VarDef>" << endl;
            return varDef;
        }
    }
}

InitVal Parser::parseInitVal() {
    InitVal initVal;
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<InitVal>" << endl;
            readTk;
            return initVal;
        }
        InitVal son_initVal1 = parseInitVal();
        initVal.addInitVal(&son_initVal1);
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            InitVal son_initVal1 = parseInitVal();
            initVal.addInitVal(&son_initVal1);
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<InitVal>" << endl;
            readTk;
            return initVal;
        }
    } else {
        Exp exp = parseExp();
        initVal.setExp(&exp);
        return initVal;
    }
}

FuncDef Parser::parseFuncDef() {
    FuncDef funcDef;
    FuncType funcType = parseFuncType();
    funcDef.setFuncType(&funcType);
    if (tkType == LexType::IDENFR) {
        Ident ident(tkWord);
        funcDef.setIdent(&ident);
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::RPARENT) {
                printTk;
                readTk;
            } else {
                FuncFParams funcFParams = parseFuncFParams();
                funcDef.setFuncFParams(&funcFParams);
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                }
            }
            Block block = parseBlock();
            funcDef.setBlock(&block);
            ofs << "<FuncDef>" << endl;
            return funcDef;
        } 
    }
}

MainFuncDef Parser::parseMainFuncDef() {
    MainFuncDef mainFuncDef;
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
                    Block block = parseBlock();
                    mainFuncDef.setBlock(&block);
                    ofs << "<MainFuncDef>" << endl;
                    return mainFuncDef;
                }
            }
        }
    }
}

FuncType Parser::parseFuncType() {
    if (tkType == LexType::INTTK) {
        FuncType funcType("int");
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return funcType;
    } else if (tkType == LexType::VOIDTK) {
        FuncType funcType("int");
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return funcType;
    }
}

FuncFParams Parser::parseFuncFParams() {
    FuncFParams funcFParams;
    FuncFParam funcFParam = parseFuncFParam();
    funcFParams.addFuncFParam(&funcFParam);
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        FuncFParams funcFParams;
        FuncFParam funcFParam = parseFuncFParam();
        funcFParams.addFuncFParam(&funcFParam);
    }
    ofs << "<FuncFParams>" << endl;
    return funcFParams;
}

FuncFParam Parser::parseFuncFParam() {
    FuncFParam funcFparam;
    if (tkType == LexType::INTTK) {
        Btype btype("int");
        funcFparam.setBtype(&btype);
        printTk;
        readTk;
        if (tkType == LexType::IDENFR) {
            Ident ident(tkWord);
            funcFparam.setIdent(&ident);
            printTk;
            readTk;
            if (tkType == LexType::LBRACK) {
                printTk;
                readTk;
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                }
                while (tkType == LexType::LBRACK) {
                    printTk;
                    readTk;
                    ConstExp constExp = parseConstExp();
                    funcFparam.addConstExp(&constExp);
                    if (tkType == LexType::RBRACK) {
                        printTk;
                        readTk;
                    }
                }
                ofs << "<FuncFParam>" << endl;
                return funcFparam;
            } else {
                ofs << "<FuncFParam>" << endl;
                return funcFparam;
            }
        }
    }
}

Block Parser::parseBlock() {
    Block block;
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        while (tkType != LexType::RBRACE) {
            BlockItem blockItem = parseBlockItem();
            block.addBlockItem(&blockItem);
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<Block>" << endl;
            readTk;
            return block;
        }
    }
}

BlockItem Parser::parseBlockItem() {
    BlockItem blockItem;
    Decl decl = parseDecl();
    blockItem.setDecl(&decl);
    Stmt stmt = parseStmt();
    blockItem.setStmt(&stmt);
    return blockItem;
}

Stmt Parser::parseStmt() {
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

ForStmt Parser::parseForStmt() {
    ForStmt forStmt;
    LVal lVal = parseLVal();
    forStmt.setLVal(&lVal);
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        Exp exp = parseExp();
        ofs << "<ForStmt>" << endl;
        forStmt.setExp(&exp);
        return forStmt;
    }
}

Exp Parser::parseExp() {
    Exp exp;
    AddExp addExp = parseAddExp();
    exp.setAddExp(&addExp);
    ofs << "<Exp>" << endl;
    return exp;
}

Cond Parser::parseCond() {
    Cond cond;
    LOrExp lOrExp = parseLOrExp();
    cond.setLOrExp(&lOrExp);
    ofs << "<Cond>" << endl;
    return cond;
}

LVal Parser::parseLVal() {
    LVal lVal;
    if (tkType == LexType::IDENFR) {
        Ident ident(tkWord);
        lVal.setIdent(&ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            Exp exp = parseExp();
            lVal.addExp(&exp);
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        return lVal;
    }
}

PrimaryExp Parser::parsePrimaryExp() {
    if (tkType == LexType::LPARENT) {
        printTk;
        readTk;
        Exp exp = parseExp();
        if (tkType == LexType::RPARENT) {
            printTk;
            ofs << "<PrimaryExp>" << endl;
            readTk;
            return 0;
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

Number Parser::parseNumber() {
    if (tkType == LexType::INTCON) {
        printTk;
        ofs << "<Number>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

UnaryExp Parser::parseUnaryExp() {
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

UnaryOp Parser::parseUnaryOp() {
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        printTk;
        ofs << "<UnaryOp>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

FuncRParams Parser::parseFuncRParams() {
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

MulExp Parser::parseMulExp() {
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

AddExp Parser::parseAddExp() {
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

RelExp Parser::parseRelExp() {
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
EqExp Parser::parseEqExp() {
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

LAndExp Parser::parseLAndExp() {
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

LOrExp Parser::parseLOrExp() {
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

ConstExp Parser::parseConstExp() {
    int AddExp = parseAddExp();
    if (AddExp == 0) {
        ofs << "<ConstExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}