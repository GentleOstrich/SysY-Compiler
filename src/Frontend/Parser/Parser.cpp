//
// Created by yh on 2023/9/25.
//
#include "Parser.h"

#define tkType token.lexType
#define tkWord token.word
#define readTk    \
    lexer.next(); \
    token.setToken(lexer.getToken())
#define printTk ofs << LexType2String(tkType) << " " << tkWord << std::endl
#define preRead lexer.nnext()
#define prePreRead lexer.nnnext()

// #define ERROR_CHECK

#ifdef ERROR_CHECK

struct Error
{
    int line;
    char c;
};
extern Error errors[1000];
extern int e;

#define printError(lineNum, type) errors[e++] = {lineNum, type[0]}

#endif

extern Lexer lexer;
extern std::ifstream ifs;
extern std::ofstream ofs;
Token token;

// 正常返回 0 错误返回 -1
CompUnit *Parser::parseCompUnit() {
    auto compUnit = new CompUnit(NodeType::CompUnit, lexer.getLineNum());
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
    ofs << "<CompUnit>" << std::endl;
    return compUnit;
}

Decl *Parser::parseDecl() {
    auto decl = new Decl(NodeType::Decl, lexer.getLineNum());
    if (tkType == LexType::CONSTTK) {
        decl->addChild(parseConstDecl());
    } else if (tkType == LexType::INTTK) {
        decl->addChild(parseVarDecl());
    }
    return decl;
}

ConstDecl *Parser::parseConstDecl() {
    auto constDecl = new ConstDecl(NodeType::ConstDecl, lexer.getLineNum());
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
            printError(constDecl ->getLineNum(), "i");
#endif
        }
    }
    ofs << "<ConstDecl>" << std::endl;
    return constDecl;
}

BType *Parser::parseBType() {
    auto bType = new BType(NodeType::BType, lexer.getLineNum());
    if (tkType == LexType::INTTK) {
        bType->type = 0;
        printTk;
        readTk;
    }
    return bType;
}

ConstDef *Parser::parseConstDef() {
    auto constDef = new ConstDef(NodeType::ConstDef, lexer.getLineNum());
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
                printError(constDef ->getLineNum(), "k");
#endif
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            constDef->addChild(parseConstInitVal());
        }
    }
    ofs << "<ConstDef>" << std::endl;
    return constDef;
}

ConstInitVal *Parser::parseConstInitVal() {
    auto constInitVal = new ConstInitVal(NodeType::ConstInitVal, lexer.getLineNum());
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
    ofs << "<ConstInitVal>" << std::endl;
    return constInitVal;
}

VarDecl *Parser::parseVarDecl() {
    auto varDecl = new VarDecl(NodeType::VarDecl, lexer.getLineNum());
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
        printError(varDecl ->getLineNum(), "i");
#endif
    }
    ofs << "<VarDecl>" << std::endl;
    return varDecl;
}

VarDef *Parser::parseVarDef() {
    auto varDef = new VarDef(NodeType::VarDef, lexer.getLineNum());
    if (tkType == LexType::IDENFR) {
        varDef->word = tkWord;
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
                printError(varDef ->getLineNum(), "k");
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
    ofs << "<VarDef>" << std::endl;
    return varDef;
}

InitVal *Parser::parseInitVal() {
    auto initVal = new InitVal(NodeType::InitVal, lexer.getLineNum());
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
    ofs << "<InitVal>" << std::endl;
    return initVal;
}

FuncDef *Parser::parseFuncDef() {
    auto funcDef = new FuncDef(NodeType::FuncDef, lexer.getLineNum());
    funcDef->addChild(parseFuncType());
    if (tkType == LexType::IDENFR) {
        funcDef->word = tkWord;
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
                    printError(funcDef ->getLineNum(), "j");
#endif
                }
            }
            funcDef->addChild(parseBlock());
        }
    }
    ofs << "<FuncDef>" << std::endl;
    return funcDef;
}

MainFuncDef *Parser::parseMainFuncDef() {
    auto mainFuncDef = new MainFuncDef(NodeType::MainFuncDef, lexer.getLineNum());
    mainFuncDef->word = "main";
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
                    printError(mainFuncDef ->getLineNum(), "j");
#endif
                }
                mainFuncDef->addChild(parseBlock());
            }
        }
    }
    ofs << "<MainFuncDef>" << std::endl;
    return mainFuncDef;
}

FuncType *Parser::parseFuncType() {
    auto funcType = new FuncType(NodeType::FuncType, lexer.getLineNum());
    if (tkType == LexType::INTTK) {
        funcType->type = 0;
        printTk;
        readTk;
    } else if (tkType == LexType::VOIDTK) {
        funcType->type = 1;
        printTk;
        readTk;
    }
    ofs << "<FuncType>" << std::endl;
    return funcType;
}

FuncFParams *Parser::parseFuncFParams() {
    auto funcFParams = new FuncFParams(NodeType::FuncFParams, lexer.getLineNum());
    funcFParams->addChild(parseFuncFParam());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcFParams->addChild(parseFuncFParam());
    }
    ofs << "<FuncFParams>" << std::endl;
    return funcFParams;
}

FuncFParam *Parser::parseFuncFParam() {
    auto funcFParam = new FuncFParam(NodeType::FuncFParam, lexer.getLineNum());
    funcFParam->addChild(parseBType());
    if (tkType == LexType::IDENFR) {
        funcFParam->word = tkWord;
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
                printError(funcFParam ->getLineNum(), "k");
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
                    printError(funcFParam ->getLineNum(), "k");
#endif
                }
            }
        }
    }
    ofs << "<FuncFParam>" << std::endl;
    return funcFParam;
}

Block *Parser::parseBlock() {
    auto block = new Block(NodeType::Block, lexer.getLineNum());
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
    ofs << "<Block>" << std::endl;
    return block;
}

BlockItem *Parser::parseBlockItem() {
    auto blockItem = new BlockItem(NodeType::BlockItem, lexer.getLineNum());
    if (tkType == LexType::CONSTTK || tkType == LexType::INTTK) {
        blockItem->addChild(parseDecl());
    } else {
        blockItem->addChild(parseStmt());
    }
    return blockItem;
}

Stmt *Parser::parseStmt() {
    auto stmt = new Stmt(NodeType::Stmt, lexer.getLineNum());
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
            } else {
#ifdef ERROR_CHECK
                printError(stmt ->getLineNum(), "j");
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
            printError(stmt ->getLineNum(), "i");
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
            printError(stmt ->getLineNum(), "i");
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
                printError(stmt ->getLineNum(), "i");
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
                stmt->str = tkWord;
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
                    printError(stmt ->getLineNum(), "j");
#endif
                }
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                } else {
#ifdef ERROR_CHECK
                    printError(stmt ->getLineNum(), "i");
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
                            printError(stmt ->getLineNum(), "j");
#endif
                        }
                        if (tkType == LexType::SEMICN) {
                            printTk;
                            readTk;
                        } else {
#ifdef ERROR_CHECK
                            printError(stmt ->getLineNum(), "i");
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
                        printError(stmt ->getLineNum(), "i");
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
                printError(stmt ->getLineNum(), "i");
#endif
            }
        }
    }
    ofs << "<Stmt>" << std::endl;
    return stmt;
}

ForStmt *Parser::parseForStmt() {
    auto forStmt = new ForStmt(NodeType::ForStmt, lexer.getLineNum());
    forStmt->addChild(parseLVal());
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        forStmt->addChild(parseExp());
    }
    ofs << "<ForStmt>" << std::endl;
    return forStmt;
}

Exp *Parser::parseExp() {
    auto exp = new Exp(NodeType::Exp, lexer.getLineNum());
    exp->addChild(parseAddExp());
    ofs << "<Exp>" << std::endl;
    return exp;
}

Cond *Parser::parseCond() {
    auto cond = new Cond(NodeType::Cond, lexer.getLineNum());
    cond->addChild(parseLOrExp());
    ofs << "<Cond>" << std::endl;
    return cond;
}

LVal *Parser::parseLVal() {
    auto lVal = new LVal(NodeType::LVal, lexer.getLineNum());
    if (tkType == LexType::IDENFR) {
        lVal->word = tkWord;
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
                printError(lVal ->getLineNum(), "k");
#endif
            }
        }
    }
    /////
    ofs << "<LVal>" << std::endl;
    return lVal;
}

PrimaryExp *Parser::parsePrimaryExp() {
    auto primaryExp = new PrimaryExp(NodeType::PrimaryExp, lexer.getLineNum());
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
    ofs << "<PrimaryExp>" << std::endl;
    return primaryExp;
}

Number *Parser::parseNumber() {
    auto number = new Number(NodeType::Number, lexer.getLineNum());
    if (tkType == LexType::INTCON) {
        // TODO
        number->val = lexer.getNumber();
        printTk;
        readTk;
    }
    ofs << "<Number>" << std::endl;
    return number;
}

UnaryExp *Parser::parseUnaryExp() {
    auto unaryExp = new UnaryExp(NodeType::UnaryExp, lexer.getLineNum());
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        unaryExp->addChild(parseUnaryOp());
        unaryExp->addChild(parseUnaryExp());
    } else {
        if (tkType == LexType::IDENFR && preRead == LexType::LPARENT) {
            unaryExp->word = tkWord;
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
                    printError(unaryExp ->getLineNum(), "j");
#endif
                }
            }
        } else {
            unaryExp->addChild(parsePrimaryExp());
        }
    }
    ofs << "<UnaryExp>" << std::endl;
    return unaryExp;
}

UnaryOp *Parser::parseUnaryOp() {
    auto unaryOp = new UnaryOp(NodeType::UnaryOp, lexer.getLineNum());
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
    ofs << "<UnaryOp>" << std::endl;
    return unaryOp;
}

FuncRParams *Parser::parseFuncRParams() {
    auto funcRParams = new FuncRParams(NodeType::FuncRParams, lexer.getLineNum());
    funcRParams->addChild(parseExp());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcRParams->addChild(parseExp());
    }
    ofs << "<FuncRParams>" << std::endl;
    return funcRParams;
}

MulExp *Parser::parseMulExp() {
    auto mulExp = new MulExp(NodeType::MulExp, lexer.getLineNum());
    mulExp->addChild(parseUnaryExp());
    while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
        auto temp = new MulExp(NodeType::MulExp, lexer.getLineNum());
        if (tkType == LexType::MULT) {
            temp->op = 0;
        } else if (tkType == LexType::DIV) {
            temp->op = 1;
        } else if (tkType == LexType::MOD) {
            temp->op = 2;
        }
        ofs << "<MulExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(mulExp));
        temp->op = mulExp->getOp();
        temp->addChild(parseUnaryExp());
        mulExp = temp;
    }
    ofs << "<MulExp>" << std::endl;
    return mulExp;
}

AddExp *Parser::parseAddExp() {
    auto addExp = new AddExp(NodeType::AddExp, lexer.getLineNum());
    addExp->addChild(parseMulExp());
    while (tkType == LexType::PLUS || tkType == LexType::MINU) {
        auto temp = new AddExp(NodeType::AddExp, lexer.getLineNum());
        if (tkType == LexType::PLUS) {
            temp->op = 0;
        } else if (tkType == LexType::MINU) {
            temp->op = 1;
        }
        ofs << "<AddExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(addExp));
        temp->op = addExp->getOp();
        temp->addChild(parseMulExp());
        addExp = temp;
    }
    ofs << "<AddExp>" << std::endl;
    return addExp;
}

RelExp *Parser::parseRelExp() {
    auto relExp = new RelExp(NodeType::RelExp, lexer.getLineNum());
    relExp->addChild(parseAddExp());
    while (tkType == LexType::GRE || tkType == LexType::GEQ ||
           tkType == LexType::LSS || tkType == LexType::LEQ) {
        auto temp = new RelExp(NodeType::RelExp, lexer.getLineNum());
        switch (tkType) {
            case LexType::GRE:
                relExp->op = 0;
                break;
            case LexType::GEQ:
                relExp->op = 1;
                break;
            case LexType::LSS:
                relExp->op = 2;
                break;
            case LexType::LEQ:
                relExp->op = 3;
                break;
            default:
                break;
        }
        ofs << "<RelExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(relExp));
        temp->op = relExp->getOp();
        temp->addChild(parseAddExp());
        relExp = temp;
    }
    ofs << "<RelExp>" << std::endl;
    return relExp;
}

EqExp *Parser::parseEqExp() {
    auto eqExp = new EqExp(NodeType::EqExp, lexer.getLineNum());
    eqExp->addChild(parseRelExp());
    while (tkType == LexType::EQL || tkType == LexType::NEQ) {
        auto temp = new EqExp(NodeType::EqExp, lexer.getLineNum());
        switch (tkType) {
            case LexType::EQL:
                eqExp->op = 0;
                break;
            case LexType::NEQ:
                eqExp->op = 1;
                break;
            default:
                break;
        }
        ofs << "<EqExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(eqExp));
        temp->op = eqExp->getOp();
        temp->addChild(parseRelExp());
        eqExp = temp;
    }
    ofs << "<EqExp>" << std::endl;
    return eqExp;
}

LAndExp *Parser::parseLAndExp() {
    auto lAndExp = new LAndExp(NodeType::LAndExp, lexer.getLineNum());
    lAndExp->addChild(parseEqExp());
    while (tkType == LexType::AND) {
        auto temp = new LAndExp(NodeType::LAndExp, lexer.getLineNum());
        ofs << "<LAndExp>" << std::endl;
        printTk;
        readTk;
        // auto rightEqExp = std::make_unique<EqExp *(NodeType::EqExp, lexer.getLineNum());
        temp->addChild(std::move(lAndExp));
        temp->addChild(parseEqExp());
        lAndExp = temp;
    }
    ofs << "<LAndExp>" << std::endl;
    return lAndExp;
}

LOrExp *Parser::parseLOrExp() {
    auto lOrExp = new LOrExp(NodeType::LOrExp, lexer.getLineNum());
    lOrExp->addChild(parseLAndExp());
    while (tkType == LexType::OR) {
        auto temp = new LOrExp(NodeType::LOrExp, lexer.getLineNum());
        ofs << "<LOrExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(lOrExp));
        temp->addChild(parseLAndExp());
        lOrExp = temp;
    }
    ofs << "<LOrExp>" << std::endl;
    return lOrExp;
}

ConstExp *Parser::parseConstExp() {
    auto constExp = new ConstExp(NodeType::ConstExp, lexer.getLineNum());
    constExp->addChild(parseAddExp());
    ofs << "<ConstExp>" << std::endl;
    return constExp;
}