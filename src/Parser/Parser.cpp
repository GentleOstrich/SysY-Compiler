//
// Created by yh on 2023/9/25.
//
#include "Parser.h"
#define tkType token.lexType
#define tkWord token.word
#define readTk lexer.next(); token.setToken(lexer.getToken())
#define printTk ofs << LexType2String(tkType) << " " << tkWord << endl
#define preRead lexer.nnext()
#define prePreRead lexer.nnnext()

//#define ERROR_CHECK

#ifdef ERROR_CHECK

struct Error {
    int line;
    char c;
};
extern Error errors[1000];
extern int e;

#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}

#endif

using namespace std;

extern Lexer lexer;
extern ifstream ifs;
extern ofstream ofs;
Token token;
// 正常返回 0 错误返回 -1
CompUnit* Parser::parseCompUnit() {
    auto* compUnit = new CompUnit(NodeType::CompUnit, lexer.getLineNum());
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
    Decl *decl = new Decl(NodeType::Decl, lexer.getLineNum());
    if (tkType == LexType::CONSTTK) {
        decl->addChild(parseConstDecl());
    } else if (tkType == LexType::INTTK) {
        decl->addChild(parseVarDecl());
    }
    return decl;
}

ConstDecl* Parser::parseConstDecl() {
    auto* constDecl = new ConstDecl(NodeType::ConstDecl, lexer.getLineNum());
    if (tkType == LexType::CONSTTK) {
        printTk;
        readTk;
        constDecl->addChild(parseBType());
        constDecl->addChild(parseConstDef());
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            constDecl->addChild(parseConstDef());
        }
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        } else {
#ifdef ERROR_CHECK
            printError(constDecl->getLineNum(), "i");
#endif
        }
    }
    ofs << "<ConstDecl>" << endl;
    return constDecl;
}

BType* Parser::parseBType() {
    auto* bType = new BType(NodeType::BType, lexer.getLineNum());
    if (tkType == LexType::INTTK) {
        bType->type = 0;
        printTk;
        readTk;
    }
    return bType;
}

ConstDef* Parser::parseConstDef() {
    auto* constDef = new ConstDef(NodeType::ConstDef, lexer.getLineNum());
    if (tkType == LexType::IDENFR) {
        constDef->setWord(tkWord);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            constDef->type++;
            constDef->addChild(parseConstExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(constDef->getLineNum(), "k");
#endif
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            constDef->addChild(parseConstInitVal());
        }
    }
    ofs << "<ConstDef>" << endl;
    return constDef;
}

ConstInitVal* Parser::parseConstInitVal() {
    auto* constInitVal = new ConstInitVal(NodeType::ConstInitVal, lexer.getLineNum());
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            readTk;
        } else {
            constInitVal->addChild(parseConstInitVal());
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                constInitVal->addChild(parseConstInitVal());
            }
            if (tkType == LexType::RBRACE) {
                printTk;
                readTk;
            }
        }
    } else {
        constInitVal->addChild(parseConstExp());
    }
    ofs << "<ConstInitVal>" << endl;
    return constInitVal;
}

VarDecl* Parser::parseVarDecl() {
    auto* varDecl = new VarDecl(NodeType::VarDecl, lexer.getLineNum());
    varDecl->addChild(parseBType());
    varDecl->addChild(parseVarDef());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        varDecl->addChild(parseVarDef());
    }
    if (tkType == LexType::SEMICN) {
        printTk;
        readTk;
    } else {
#ifdef ERROR_CHECK
        printError(varDecl->getLineNum(), "i");
#endif
    }
    ofs << "<VarDecl>" << endl;
    return varDecl;
}

VarDef* Parser::parseVarDef() {
    auto* varDef = new VarDef(NodeType::VarDef, lexer.getLineNum());
    if (tkType == LexType::IDENFR) {
        varDef->setWord(tkWord);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            varDef->type++;
            varDef->addChild(parseConstExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(varDef->getLineNum(), "k");
#endif
            }
        }
        if (tkType == LexType::ASSIGN) {
            varDef->Equal = true;
            printTk;
            readTk;
            varDef->addChild(parseInitVal());
        }
    }
    ofs << "<VarDef>" << endl;
    return varDef;
}

InitVal* Parser::parseInitVal() {
    auto* initVal = new InitVal(NodeType::InitVal, lexer.getLineNum());
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            readTk;
        } else {
            initVal->addChild(parseInitVal());
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                initVal->addChild(parseInitVal());
            }
            if (tkType == LexType::RBRACE) {
                printTk;
                readTk;
            }
        }
    } else {
        initVal->addChild(parseExp());
    }
    ofs << "<InitVal>" << endl;
    return initVal;
}

FuncDef* Parser::parseFuncDef() {
    auto* funcDef = new FuncDef(NodeType::FuncDef, lexer.getLineNum());
    funcDef->addChild(parseFuncType());
    if (tkType == LexType::IDENFR) {
        funcDef->setWord(tkWord);
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
                } else {
#ifdef ERROR_CHECK
                    printError(funcDef->getLineNum(), "j");
#endif
                }
            }
            funcDef->addChild(parseBlock());
        }
    }
    ofs << "<FuncDef>" << endl;
    return funcDef;
}

MainFuncDef* Parser::parseMainFuncDef() {
    auto* mainFuncDef = new MainFuncDef(NodeType::MainFuncDef, lexer.getLineNum());
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
                } else {
#ifdef ERROR_CHECK
                    printError(mainFuncDef->getLineNum(), "j");
#endif
                }
                mainFuncDef->addChild(parseBlock());
            }
        }
    }
    ofs << "<MainFuncDef>" << endl;
    return mainFuncDef;
}

FuncType* Parser::parseFuncType() {
    auto* funcType = new FuncType(NodeType::FuncType, lexer.getLineNum());
    if (tkType == LexType::INTTK) {
        funcType->type = 0;
        printTk;
        readTk;
    } else if (tkType == LexType::VOIDTK) {
        funcType->type = 1;
        printTk;
        readTk;
    }
    ofs << "<FuncType>" << endl;
    return funcType;
}

FuncFParams* Parser::parseFuncFParams() {
    auto* funcFParams = new FuncFParams(NodeType::FuncFParams, lexer.getLineNum());
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
    auto* funcFParam = new FuncFParam(NodeType::FuncFParam, lexer.getLineNum());
    funcFParam->addChild(parseBType());
    if (tkType == LexType::IDENFR) {
        funcFParam->setWord(tkWord);
        printTk;
        readTk;
        if (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            funcFParam->type++;
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(funcFParam->getLineNum(), "k");
#endif
            }
            while (tkType == LexType::LBRACK) {
                printTk;
                readTk;
                funcFParam->type++;
                funcFParam->addChild(parseConstExp());
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
#ifdef ERROR_CHECK
                    printError(funcFParam->getLineNum(), "k");
#endif
                }
            }
        }
    }
    ofs << "<FuncFParam>" << endl;
    return funcFParam;
}

Block* Parser::parseBlock() {
    auto* block = new Block(NodeType::Block, lexer.getLineNum());
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        while (tkType != LexType::RBRACE) {
            block->addChild(parseBlockItem());
        }
        if (tkType == LexType::RBRACE) {
            block->lastLine = lexer.getLineNum();
            printTk;
            readTk;
        }
    }
    ofs << "<Block>" << endl;
    return block;
}

BlockItem* Parser::parseBlockItem() {
    auto* blockItem = new BlockItem(NodeType::BlockItem, lexer.getLineNum());
    if (tkType == LexType::CONSTTK || tkType == LexType::INTTK) {
        blockItem->addChild(parseDecl());
    } else {
        blockItem->addChild(parseStmt());
    }
    return blockItem;
}

Stmt* Parser::parseStmt() {
    auto* stmt = new Stmt(NodeType::Stmt, lexer.getLineNum());
    if (tkType == LexType::IFTK) {
        stmt->type = 1;
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            stmt->addChild(parseCond());
            if (tkType == LexType::RPARENT) {
                printTk;
                readTk;
            }  else {
#ifdef ERROR_CHECK
                printError(stmt->getLineNum(), "j");
#endif
            }
            stmt->addChild(parseStmt());
            if (tkType == LexType::ELSETK) {
                printTk;
                readTk;
                stmt->addChild(parseStmt());
            }
        }
    } else if (tkType == LexType::FORTK) {
        stmt->type = 2;
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType != LexType::SEMICN) {
                stmt->addChild(parseForStmt());
            }
            if (tkType == LexType::SEMICN) {
                printTk;
                readTk;
                if (tkType != LexType::SEMICN) {
                    stmt->addChild(parseCond());
                }
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                    if (tkType != LexType::RPARENT) {
                        stmt->addChild(parseForStmt());
                    }
                    if (tkType == LexType::RPARENT) {
                        printTk;
                        readTk;
                    }
                    stmt->addChild(parseStmt());
                }
            }
        }
    } else if (tkType == LexType::BREAKTK) {
        stmt->type = 3;
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        } else {
#ifdef ERROR_CHECK
            printError(stmt->getLineNum(), "i");
#endif
        }
    } else if (tkType == LexType::CONTINUETK) {
        stmt->type = 4;
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        } else {
#ifdef ERROR_CHECK
            printError(stmt->getLineNum(), "i");
#endif
        }
    } else if (tkType == LexType::RETURNTK) {
        stmt->type = 5;
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        } else {
            stmt->addChild(parseExp());
            if (tkType == LexType::SEMICN) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(stmt->getLineNum(), "i");
#endif
            }
        }
    } else if (tkType == LexType::PRINTFTK) {
        stmt->type = 7;
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::STRCON) {
                stmt->setStr(tkWord);
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
                } else {
#ifdef ERROR_CHECK
                    printError(stmt->getLineNum(), "j");
#endif
                }
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                } else {
#ifdef ERROR_CHECK
                    printError(stmt->getLineNum(), "i");
#endif
                }

            }
        }
    } else if (tkType == LexType::LBRACE) {
        stmt->addChild(parseBlock());
    } else if (tkType == LexType::SEMICN) {
        printTk;
        readTk;
    } else {
        if (lexer.hasAUntilB('=', ';')) {
            stmt->addChild(parseLVal());
            if (tkType == LexType::ASSIGN) {
                printTk;
                readTk;
                if (tkType == LexType::GETINTTK) {
                    stmt->type = 6;
                    printTk;
                    readTk;
                    if (tkType == LexType::LPARENT) {
                        printTk;
                        readTk;
                        if (tkType == LexType::RPARENT) {
                            printTk;
                            readTk;
                        } else {
#ifdef ERROR_CHECK
                            printError(stmt->getLineNum(), "j");
#endif
                        }
                        if (tkType == LexType::SEMICN) {
                            printTk;
                            readTk;
                        } else {
#ifdef ERROR_CHECK
                            printError(stmt->getLineNum(), "i");
#endif
                        }
                    }
                } else {
                    stmt->addChild(parseExp());
                    if (tkType == LexType::SEMICN) {
                        printTk;
                        readTk;
                    } else {
#ifdef ERROR_CHECK
                        printError(stmt->getLineNum(), "i");
#endif
                    }
                }
            }
        } else {
            stmt->addChild(parseExp());
            if (tkType == LexType::SEMICN) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(stmt->getLineNum(), "i");
#endif
            }
        }
    }
    ofs << "<Stmt>" << endl;
    return stmt;
}

ForStmt* Parser::parseForStmt() {
    auto* forStmt = new ForStmt(NodeType::ForStmt, lexer.getLineNum());
    forStmt->addChild(parseLVal());
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        forStmt->addChild(parseExp());
    }
    ofs << "<ForStmt>" << endl;
    return forStmt;
}

Exp* Parser::parseExp() {
    auto* exp = new Exp(NodeType::Exp, lexer.getLineNum());
    exp->addChild(parseAddExp());
    ofs << "<Exp>" << endl;
    return exp;
}

Cond* Parser::parseCond() {
    auto* cond = new Cond(NodeType::Cond, lexer.getLineNum());
    cond->addChild(parseLOrExp());
    ofs << "<Cond>" << endl;
    return cond;
}

LVal* Parser::parseLVal() {
    auto* lVal = new LVal(NodeType::LVal, lexer.getLineNum());
    if (tkType == LexType::IDENFR) {
        lVal->setWord(tkWord);
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            lVal->type++;
            lVal->addChild(parseExp());
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
#ifdef ERROR_CHECK
                printError(lVal->getLineNum(), "k");
#endif
            }
        }
    }
    /////
    ofs << "<LVal>" << endl;
    return lVal;

}

PrimaryExp* Parser::parsePrimaryExp() {
    auto* primaryExp = new PrimaryExp(NodeType::PrimaryExp, lexer.getLineNum());
    if (tkType == LexType::LPARENT) {
        printTk;
        readTk;
        primaryExp->addChild(parseExp());
        if (tkType == LexType::RPARENT) {
            printTk;
            readTk;
        }
    } else {
        if (tkType == LexType::INTCON) {
            primaryExp->addChild(parseNumber());
        } else {
            primaryExp->addChild(parseLVal());
        }
    }
    ofs << "<PrimaryExp>" << endl;
    return primaryExp;
}

Number* Parser::parseNumber() {
    auto* number = new Number(NodeType::Number, lexer.getLineNum());
    if (tkType == LexType::INTCON) {
        // TODO
        number->val = 1145414;
        printTk;
        readTk;
    }
    ofs << "<Number>" << endl;
    return number;
}

UnaryExp* Parser::parseUnaryExp() {
    auto* unaryExp = new UnaryExp(NodeType::UnaryExp, lexer.getLineNum());
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        unaryExp->addChild(parseUnaryOp());
        unaryExp->addChild(parseUnaryExp());
    } else {
        if (tkType == LexType::IDENFR && preRead == LexType::LPARENT) {
            unaryExp->setWord(tkWord);
            printTk;
            readTk;
            printTk;
            readTk;
            if (tkType == LexType::RPARENT) {
                printTk;
                readTk;
            } else {
                unaryExp->addChild(parseFuncRParams());
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                } else {
#ifdef ERROR_CHECK
                    printError(unaryExp->getLineNum(), "j");
#endif
                }
            }
        } else {
            unaryExp->addChild(parsePrimaryExp());
        }
    }
    ofs << "<UnaryExp>" << endl;
    return unaryExp;
}

UnaryOp* Parser::parseUnaryOp() {
    auto* unaryOp = new UnaryOp(NodeType::UnaryOp, lexer.getLineNum());
    if (tkType == LexType::PLUS) {
        unaryOp->type = 0;
        printTk;
        readTk;
    } else if (tkType == LexType::MINU) {
        unaryOp->type = 1;
        printTk;
        readTk;
    } else if (tkType == LexType::NOT) {
        unaryOp->type = 2;
        printTk;
        readTk;
    }
    ofs << "<UnaryOp>" << endl;
    return unaryOp;
}

FuncRParams* Parser::parseFuncRParams() {
    auto* funcRParams = new FuncRParams(NodeType::FuncRParams, lexer.getLineNum());
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
    auto* mulExp = new MulExp(NodeType::MulExp, lexer.getLineNum());
    mulExp->addChild(parseUnaryExp());
    while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
        switch (tkType) {
            case LexType::MULT:
                mulExp->addOp(0);
                break;
            case LexType::DIV:
                mulExp->addOp(1);
                break;
            case LexType::MOD:
                mulExp->addOp(2);
                break;
            default:
                break;
        }
        ofs << "<MulExp>" << endl;
        printTk;
        readTk;
        mulExp->addChild(parseUnaryExp());
    }
    ofs << "<MulExp>" << endl;
    return mulExp;
}

AddExp* Parser::parseAddExp() {
    auto* addExp = new AddExp(NodeType::AddExp, lexer.getLineNum());
    Node* leftAdd = parseMulExp();
    bool flag = false;
    while (tkType == LexType::PLUS || tkType == LexType::MINU) {
        flag = true;
        switch(tkType) {
            case LexType::PLUS:
                addExp->addOp(0);
                break;
            case LexType::MINU:
                addExp->addOp(1);
                break;
            default:
                break;
        }
        auto* temp = new AddExp(NodeType::AddExp, lexer.getLineNum());
        ofs << "<AddExp>" << endl;
        printTk;
        readTk;
        temp->addChild(leftAdd);
        temp->addChild(parseMulExp());
        leftAdd = temp;
    }
    if (!flag) {
        addExp->addChild(leftAdd);
    } else {
        addExp = dynamic_cast<AddExp *>(leftAdd);
    }
    ofs << "<AddExp>" << endl;
    return addExp;
}

RelExp* Parser::parseRelExp() {
    auto* relExp = new RelExp(NodeType::RelExp, lexer.getLineNum());
    relExp->addChild(parseAddExp());
    while (tkType == LexType::GRE || tkType == LexType::GEQ || tkType == LexType::LSS || tkType == LexType::LEQ) {
        switch (tkType) {
            case LexType::GRE:
                relExp->addOp(0);
                break;
            case LexType::GEQ:
                relExp->addOp(1);
                break;
            case LexType::LSS:
                relExp->addOp(2);
                break;
            case LexType::LEQ:
                relExp->addOp(3);
                break;
            default:
                break;
        }
        ofs << "<RelExp>" << endl;
        printTk;
        readTk;
        relExp->addChild(parseAddExp());
    }
    ofs << "<RelExp>" << endl;
    return relExp;
}

EqExp* Parser::parseEqExp() {
    auto* eqExp = new EqExp(NodeType::EqExp, lexer.getLineNum());
    eqExp->addChild(parseRelExp());
    while (tkType == LexType::EQL || tkType == LexType::NEQ) {
        switch(tkType) {
            case LexType::EQL:
                eqExp->addOp(0);
                break;
            case LexType::NEQ:
                eqExp->addOp(1);
                break;
            default:
                break;
        }
        ofs << "<EqExp>" << endl;
        printTk;
        readTk;
        eqExp->addChild(parseRelExp());
    }
    ofs << "<EqExp>" << endl;
    return eqExp;
}

LAndExp* Parser::parseLAndExp() {
    auto* lAndExp = new LAndExp(NodeType::LAndExp, lexer.getLineNum());
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
    auto* lOrExp = new LOrExp(NodeType::LOrExp, lexer.getLineNum());
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
    auto* constExp = new ConstExp(NodeType::ConstExp, lexer.getLineNum());
    constExp->addChild(parseAddExp());
    ofs << "<ConstExp>" << endl;
    return constExp;
}