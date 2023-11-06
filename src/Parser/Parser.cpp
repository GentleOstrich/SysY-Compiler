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
#define panic(error) std::cout << error << endl; return nullptr

using namespace std;
extern Lexer lexer;
extern ifstream ifs;
extern ofstream ofs;
Token token = make_pair(LexType::NONE, "");

// 正常返回 0 错误返回 -1
CompUnit* Parser::parseCompUnit() {
    CompUnit* compUnit = new CompUnit();
    readTk;
    while (tkType != LexType::NONE) {
        if (tkType == LexType::CONSTTK) {
            compUnit->addChild(parseDecl());
        } else if (tkType == LexType::INTTK) {
            if (preRead == LexType::MAINTK) {
                compUnit->addChild(parseMainFuncDef());
            } else if (preRead == LexType::IDENFR) {
                if (prePreRead == LexType::LPARENT) {
                    compUnit->addChild(parseFuncDef());
                } else {
                    compUnit->addChild(parseDecl());
                }
            }
        } else if (tkType == LexType::VOIDTK) {
            compUnit->addChild(parseFuncDef());
        }
    }
    ofs << "<CompUnit>" << endl;
    return compUnit;
}

Decl* Parser::parseDecl() {
    Decl *decl = new Decl();
    if (tkType == LexType::CONSTTK) {
        decl->addChild(parseConstDecl());
    } else if (tkType == LexType::INTTK) {
        decl->addChild(parseVarDecl());
    }
    return decl;
}

ConstDecl* Parser::parseConstDecl() {
    ConstDecl* constDecl = new ConstDecl();
    if (tkType == LexType::CONSTTK) {
        printTk;
        readTk;
        if (tkType == LexType::INTTK) {
            printTk;
            readTk;
            constDecl->addChild(parseConstDef());
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                constDecl->addChild(parseConstDef());
            }
        }
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<ConstDecl>" << endl;
            readTk;
            return constDecl;
        }
    }
    panic("ConstDecl");
}

BType* Parser::parseBType() {
    BType* bType = new BType();
    if (tkType == LexType::INTTK) {
        printTk;
        readTk;
        return bType;
    }
    panic("BType");
}

ConstDef* Parser::parseConstDef() {
    ConstDef* constDef = new ConstDef();
    if (tkType == LexType::IDENFR) {
        Node* ident = new Node(lexer.getToken());
        constDef->addChild(ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            constDef->addChild(parseConstExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            constDef->addChild(parseConstInitVal());
            ofs << "<ConstDef>" << endl;
            return constDef;
        }
    }
    panic("ConstDef");
}

ConstInitVal* Parser::parseConstInitVal() {
    ConstInitVal* constInitVal = new ConstInitVal();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<ConstInitVal>" << endl;
            readTk;
            return constInitVal;
        }
        constInitVal->addChild(parseConstInitVal());
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            constInitVal->addChild(parseConstInitVal());
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<ConstInitVal>" << endl;
            readTk;
            return constInitVal;
        }
    } else {
        constInitVal->addChild(parseConstExp());
        ofs << "<ConstInitVal>" << endl;
        return constInitVal;
    }
    panic("ConstInitVal");
}

VarDecl* Parser::parseVarDecl() {
    VarDecl* varDecl = new VarDecl();
    varDecl->addChild(parseBType());
    varDecl->addChild(parseVarDef());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        varDecl->addChild(parseVarDef());
    }
    if (tkType == LexType::SEMICN) {
        printTk;
        ofs << "<VarDecl>" << endl;
        readTk;
        return varDecl;
    }
    panic("VarDecl");
}

VarDef* Parser::parseVarDef() {
    VarDef* varDef = new VarDef();
    if (tkType == LexType::IDENFR) {
        Node* ident = new Node(lexer.getToken());
        varDef->addChild(ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            varDef->addChild(parseConstExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            varDef->addChild(parseInitVal());
            ofs << "<VarDef>" << endl;
            return varDef;
        } else {
            ofs << "<VarDef>" << endl;
            return varDef;
        }
    }
    panic("VarDef");
}

InitVal* Parser::parseInitVal() {
    InitVal* initVal = new InitVal();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<InitVal>" << endl;
            readTk;
            return initVal;
        }
        initVal->addChild(parseInitVal());
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            initVal->addChild(parseInitVal());
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<InitVal>" << endl;
            readTk;
            return initVal;
        }
    } else {
        initVal->addChild(parseExp());
        return initVal;
    }
    panic("InitVal");
}

FuncDef* Parser::parseFuncDef() {
    FuncDef* funcDef = new FuncDef();
    funcDef->addChild(parseFuncType());
    if (tkType == LexType::IDENFR) {
        Node* ident = new Node(lexer.getToken());
        funcDef->addChild(ident);
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::RPARENT) {
                printTk;
                readTk;
            } else {
                funcDef->addChild(parseFuncFParams());
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                }
            }
            funcDef->addChild(parseBlock());
            ofs << "<FuncDef>" << endl;
            return funcDef;
        } 
    }
    panic("FuncDef");
}

MainFuncDef* Parser::parseMainFuncDef() {
    MainFuncDef* mainFuncDef = new MainFuncDef();
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
                    mainFuncDef->addChild(parseBlock());
                    ofs << "<MainFuncDef>" << endl;
                    return mainFuncDef;
                }
            }
        }
    }
    panic("MainFuncDef");
}

FuncType* Parser::parseFuncType() {
    FuncType* funcType = new FuncType();
    if (tkType == LexType::INTTK) {
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return funcType;
    } else if (tkType == LexType::VOIDTK) {
        printTk;
        ofs << "<FuncType>" << endl;
        readTk;
        return funcType;
    }
    panic("FuncType");
}

FuncFParams* Parser::parseFuncFParams() {
    FuncFParams* funcFParams = new FuncFParams();
    funcFParams->addChild(parseFuncFParam());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcFParams->addChild(parseFuncFParam());
    }
    ofs << "<FuncFParams>" << endl;
    return funcFParams;
}

FuncFParam* Parser::parseFuncFParam() {
    FuncFParam* funcFParam = new FuncFParam();
    funcFParam->addChild(parseBType());
    if (tkType == LexType::IDENFR) {
        Node* ident = new Node(lexer.getToken());
        funcFParam->addChild(ident);
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
                funcFParam->addChild(parseConstExp());
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                }
            }
            ofs << "<FuncFParam>" << endl;
            return funcFParam;
        } else {
            ofs << "<FuncFParam>" << endl;
            return funcFParam;
        }
    }
    panic("FuncFParam");
}

Block* Parser::parseBlock() {
    Block* block = new Block();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        while (tkType != LexType::RBRACE) {
            block->addChild(parseBlockItem());
        }
        if (tkType == LexType::RBRACE) {
            printTk;
            ofs << "<Block>" << endl;
            readTk;
            return block;
        }
    }
    panic("Block");
}

BlockItem* Parser::parseBlockItem() {
    BlockItem* blockItem = new BlockItem();
    if (tkType == LexType::CONSTTK || tkType == LexType::INTTK) {
        blockItem->addChild(parseDecl());
    } else{
        blockItem->addChild(parseStmt());
    }
    return blockItem;
}

Stmt* Parser::parseStmt() {
    Stmt* stmt = new Stmt();
    if (tkType == LexType::IFTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            stmt->addChild(parseCond());
            if (tkType == LexType::RPARENT) {
                printTk;
                readTk;
                stmt->addChild(parseStmt());
                if (tkType == LexType::ELSETK) {
                    printTk;
                    readTk;
                    stmt->addChild(parseStmt());
                    ofs << "<Stmt>" << endl;
                    return stmt;   
                } else {
                    ofs << "<Stmt>" << endl;
                    return stmt;
                }
            }
        }
    } else if (tkType == LexType::FORTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            stmt->addChild(parseForStmt());
            if (tkType == LexType::SEMICN) {
                printTk;
                readTk;
                stmt->addChild(parseCond());
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                    stmt->addChild(parseForStmt());
                    if (tkType == LexType::RPARENT) {
                        printTk;
                        readTk;
                        stmt->addChild(parseStmt());
                        ofs << "<Stmt>" << endl;
                    }
                }
            }
        }
    } else if (tkType == LexType::BREAKTK) {
        stmt->setBreak();
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return stmt;
        }
    } else if (tkType == LexType::CONTINUETK) {
        stmt->setContinue();
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return stmt;
        }
    } else if (tkType == LexType::RETURNTK) {
        printTk;
        readTk;
        stmt->setReturn();
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return stmt;
        } else {
            stmt->addChild(parseExp());
            if (tkType == LexType::SEMICN) {
                printTk;
                ofs << "<Stmt>" << endl;
                readTk;
                return stmt;
            }
        }
    } else if (tkType == LexType::PRINTFTK) {
        stmt->setPrintf();
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::STRCON) {
                Node* str = new Node(lexer.getToken());
                stmt->addChild(str);
                printTk;
                readTk;
                while (tkType == LexType::COMMA) {
                    printTk;
                    readTk;
                    stmt->addChild(parseExp());
                }
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                    if (tkType == LexType::SEMICN) {
                        printTk;
                        ofs << "<Stmt>" << endl;
                        readTk;
                        return stmt;
                    }
                }
            }
        }
    } else if (tkType == LexType::LBRACE) {
        stmt->addChild(parseBlock());
        ofs << "<Stmt>" << endl;
        return stmt;
    } else {
        if (tkType == LexType::SEMICN) {
            printTk;
            ofs << "<Stmt>" << endl;
            readTk;
            return stmt;
        } else {
            if (lexer.hasAUntilB('=', ';')) {
                stmt->addChild(parseLVal());
                if (tkType == LexType::ASSIGN) {
                    printTk;
                    readTk;
                    if (tkType == LexType::GETINTTK) {
                        stmt->setGetInt();
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
                                    return stmt;
                                }
                            }
                        }
                    } else {
                        stmt->addChild(parseExp());
                        if (tkType == LexType::SEMICN) {
                            printTk;
                            ofs << "<Stmt>" << endl;
                            readTk;
                            return 0;
                        }
                    }
                }
                
            } else {
                stmt->addChild(parseExp());
                if (tkType == LexType::SEMICN) {
                    printTk;
                    ofs << "<Stmt>" << endl;
                    readTk;
                    return stmt;
                }
            }
        }
    }
    return 0;
}

ForStmt* Parser::parseForStmt() {
    ForStmt* forStmt = new ForStmt();
    forStmt->addChild(parseLVal());
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        Exp* exp = new Exp();
        ofs << "<ForStmt>" << endl;
        forStmt->addChild(exp);
        return forStmt;
    }
    panic("ForStmt");
}

Exp* Parser::parseExp() {
    Exp* exp = new Exp();
    exp->addChild(parseAddExp());
    ofs << "<Exp>" << endl;
    return exp;
}

Cond* Parser::parseCond() {
    Cond* cond = new Cond();
    cond->addChild(parseLOrExp());
    ofs << "<Cond>" << endl;
    return cond;
}

LVal* Parser::parseLVal() {
    LVal* lVal = new LVal();
    if (tkType == LexType::IDENFR) {
        Node* ident = new Node(lexer.getToken());
        lVal->addChild(ident);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            lVal->addChild(parseExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            }
        }
        return lVal;
    }
    panic("LVal");
}

PrimaryExp* Parser::parsePrimaryExp() {
    PrimaryExp* primaryExp = new PrimaryExp();
    if (tkType == LexType::LPARENT) {
        printTk;
        readTk;
        primaryExp->addChild(parseExp());
        if (tkType == LexType::RPARENT) {
            printTk;
            ofs << "<PrimaryExp>" << endl;
            readTk;
            return primaryExp;
        }
    } else {
        if (tkType == LexType::INTCON) {
            primaryExp->addChild(parseNumber());
            ofs << "<PrimaryExp>" << endl;
            return primaryExp;
        } else {
            primaryExp->addChild(parseLVal());
            ofs << "<PrimaryExp>" << endl;
            return primaryExp;
        }
    }
    panic("UnaryPrimaryExp");
}

Number* Parser::parseNumber() {
    Number* number = new Number();
    if (tkType == LexType::INTCON) {
        printTk;
        ofs << "<Number>" << endl;
        readTk;
        return number;
    } else {
        delete number;
        return nullptr;
    }
}

UnaryExp* Parser::parseUnaryExp() {
    UnaryExp* unaryExp = new UnaryExp();
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        unaryExp->addChild(parseUnaryOp());
        unaryExp->addChild(parseUnaryExp());
        ofs << "<UnaryExp>" << endl;
        return unaryExp;
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
                unaryExp->addChild(parseFuncRParams());
                if (tkType == LexType::RPARENT) {
                    printTk;
                    ofs << "<UnaryExp>" << endl;
                    readTk;
                    return unaryExp;
                }
            }
        } else {
            unaryExp->addChild(parsePrimaryExp());
            ofs << "<UnaryExp>" << endl;
            return unaryExp;
        }
    }
    panic("UnaryExp");
}

UnaryOp* Parser::parseUnaryOp() {
    UnaryOp* unaryOp = new UnaryOp();
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        printTk;
        ofs << "<UnaryOp>" << endl;
        readTk;
        return unaryOp;
    }
    panic("UnaryOp");
}

FuncRParams* Parser::parseFuncRParams() {
    FuncRParams* funcRParams = new FuncRParams();
    funcRParams->addChild(parseExp());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcRParams->addChild(parseExp());
    }
    ofs << "<FuncRParams>" << endl;
    return funcRParams;
    
}

MulExp* Parser::parseMulExp() {
    MulExp* mulExp = new MulExp();
    mulExp->addChild(parseUnaryExp());
    while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
        ofs << "<MulExp>" << endl;
        printTk;
        readTk;
        mulExp->addChild(parseUnaryExp());
    }
    ofs << "<MulExp>" << endl;
    return 0;
    
}

AddExp* Parser::parseAddExp() {
    AddExp* addExp = new AddExp();
    addExp->addChild(parseMulExp());
    while (tkType == LexType::PLUS || tkType == LexType::MINU) {
        ofs << "<AddExp>" << endl;
        printTk;
        readTk;
        addExp->addChild(parseMulExp());
    }
    ofs << "<AddExp>" << endl;
    return 0;

}

RelExp* Parser::parseRelExp() {
    RelExp* relExp = new RelExp();
    relExp->addChild(parseAddExp());
    while (tkType == LexType::GRE || tkType == LexType::GEQ ||
            tkType == LexType::LSS || tkType == LexType::LEQ) {
        ofs << "<RelExp>" << endl;
        printTk;
        readTk;
        relExp->addChild(parseAddExp());
    }
    ofs << "<RelExp>" << endl;
    return relExp; 
}

EqExp* Parser::parseEqExp() {
    EqExp* eqExp = new EqExp();
    eqExp->addChild(parseRelExp());
    while (tkType == LexType::EQL || tkType == LexType::NEQ) {
        ofs << "<EqExp>" << endl;
        printTk;
        readTk;
        eqExp->addChild(parseRelExp());
    }
    ofs << "<EqExp>" << endl;
    return eqExp;
}

LAndExp* Parser::parseLAndExp() {
    LAndExp* lAndExp = new LAndExp();
    lAndExp->addChild(parseEqExp());
    while (tkType == LexType::AND) {
        ofs << "<LAndExp>" << endl;
        printTk;
        readTk;
        lAndExp->addChild(parseEqExp());
    }
    ofs << "<LAndExp>" << endl;
    return lAndExp;
}

LOrExp* Parser::parseLOrExp() {
    LOrExp* lOrExp = new LOrExp();
    lOrExp->addChild(parseLAndExp());
    while (tkType == LexType::OR) {
        ofs << "<LOrExp>" << endl;
        printTk;
        readTk;
        lOrExp->addChild(parseLAndExp());
    }
    ofs << "<LOrExp>" << endl;
    return lOrExp;
}

ConstExp* Parser::parseConstExp() {
    ConstExp* constExp = new ConstExp();
    constExp->addChild(parseAddExp());
    ofs << "<ConstExp>" << endl;
    return constExp;
}