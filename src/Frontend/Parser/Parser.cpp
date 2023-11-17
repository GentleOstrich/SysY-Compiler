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
std::unique_ptr<CompUnit> Parser::parseCompUnit() {
    auto compUnit = std::make_unique<CompUnit>(NodeType::CompUnit, lexer.getLineNum());
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

std::unique_ptr<Decl> Parser::parseDecl() {
    auto decl = std::make_unique<Decl>(NodeType::Decl, lexer.getLineNum());
    if (tkType == LexType::CONSTTK) {
        decl->addChild(parseConstDecl());
    } else if (tkType == LexType::INTTK) {
        decl->addChild(parseVarDecl());
    }
    return decl;
}

std::unique_ptr<ConstDecl> Parser::parseConstDecl() {
    auto constDecl = std::make_unique<ConstDecl>(NodeType::ConstDecl, lexer.getLineNum());
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
    ofs << "<ConstDecl>" << std::endl;
    return constDecl;
}

std::unique_ptr<BType> Parser::parseBType() {
    auto bType = std::make_unique<BType>(NodeType::BType, lexer.getLineNum());
    if (tkType == LexType::INTTK) {
        bType->type = 0;
        printTk;
        readTk;
    }
    return bType;
}

std::unique_ptr<ConstDef> Parser::parseConstDef() {
    auto constDef = std::make_unique<ConstDef>(NodeType::ConstDef, lexer.getLineNum());
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
    ofs << "<ConstDef>" << std::endl;
    return constDef;
}

std::unique_ptr<ConstInitVal> Parser::parseConstInitVal() {
    auto constInitVal = std::make_unique<ConstInitVal>(NodeType::ConstInitVal, lexer.getLineNum());
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

std::unique_ptr<VarDecl> Parser::parseVarDecl() {
    auto varDecl = std::make_unique<VarDecl>(NodeType::VarDecl, lexer.getLineNum());
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
    ofs << "<VarDecl>" << std::endl;
    return varDecl;
}

std::unique_ptr<VarDef> Parser::parseVarDef() {
    auto varDef = std::make_unique<VarDef>(NodeType::VarDef, lexer.getLineNum());
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
    ofs << "<VarDef>" << std::endl;
    return varDef;
}

std::unique_ptr<InitVal> Parser::parseInitVal() {
    auto initVal = std::make_unique<InitVal>(NodeType::InitVal, lexer.getLineNum());
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

std::unique_ptr<FuncDef> Parser::parseFuncDef() {
    auto funcDef = std::make_unique<FuncDef>(NodeType::FuncDef, lexer.getLineNum());
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
                    printError(funcDef->getLineNum(), "j");
#endif
                }
            }
            funcDef->addChild(parseBlock());
        }
    }
    ofs << "<FuncDef>" << std::endl;
    return funcDef;
}

std::unique_ptr<MainFuncDef> Parser::parseMainFuncDef() {
    auto mainFuncDef = std::make_unique<MainFuncDef>(NodeType::MainFuncDef, lexer.getLineNum());
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
    ofs << "<MainFuncDef>" << std::endl;
    return mainFuncDef;
}

std::unique_ptr<FuncType> Parser::parseFuncType() {
    auto funcType = std::make_unique<FuncType>(NodeType::FuncType, lexer.getLineNum());
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

std::unique_ptr<FuncFParams> Parser::parseFuncFParams() {
    auto funcFParams = std::make_unique<FuncFParams>(NodeType::FuncFParams, lexer.getLineNum());
    funcFParams->addChild(parseFuncFParam());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcFParams->addChild(parseFuncFParam());
    }
    ofs << "<FuncFParams>" << std::endl;
    return funcFParams;
}

std::unique_ptr<FuncFParam> Parser::parseFuncFParam() {
    auto funcFParam = std::make_unique<FuncFParam>(NodeType::FuncFParam, lexer.getLineNum());
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
    ofs << "<FuncFParam>" << std::endl;
    return funcFParam;
}

std::unique_ptr<Block> Parser::parseBlock() {
    auto block = std::make_unique<Block>(NodeType::Block, lexer.getLineNum());
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

std::unique_ptr<BlockItem> Parser::parseBlockItem() {
    auto blockItem = std::make_unique<BlockItem>(NodeType::BlockItem, lexer.getLineNum());
    if (tkType == LexType::CONSTTK || tkType == LexType::INTTK) {
        blockItem->addChild(parseDecl());
    } else {
        blockItem->addChild(parseStmt());
    }
    return blockItem;
}

std::unique_ptr<Stmt> Parser::parseStmt() {
    auto stmt = std::make_unique<Stmt>(NodeType::Stmt, lexer.getLineNum());
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
    ofs << "<Stmt>" << std::endl;
    return stmt;
}

std::unique_ptr<ForStmt> Parser::parseForStmt() {
    auto forStmt = std::make_unique<ForStmt>(NodeType::ForStmt, lexer.getLineNum());
    forStmt->addChild(parseLVal());
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        forStmt->addChild(parseExp());
    }
    ofs << "<ForStmt>" << std::endl;
    return forStmt;
}

std::unique_ptr<Exp> Parser::parseExp() {
    auto exp = std::make_unique<Exp>(NodeType::Exp, lexer.getLineNum());
    exp->addChild(parseAddExp());
    ofs << "<Exp>" << std::endl;
    return exp;
}

std::unique_ptr<Cond> Parser::parseCond() {
    auto cond = std::make_unique<Cond>(NodeType::Cond, lexer.getLineNum());
    cond->addChild(parseLOrExp());
    ofs << "<Cond>" << std::endl;
    return cond;
}

std::unique_ptr<LVal> Parser::parseLVal() {
    auto lVal = std::make_unique<LVal>(NodeType::LVal, lexer.getLineNum());
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
                printError(lVal->getLineNum(), "k");
#endif
            }
        }
    }
    /////
    ofs << "<LVal>" << std::endl;
    return lVal;
}

std::unique_ptr<PrimaryExp> Parser::parsePrimaryExp() {
    auto primaryExp = std::make_unique<PrimaryExp>(NodeType::PrimaryExp, lexer.getLineNum());
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

std::unique_ptr<Number> Parser::parseNumber() {
    auto number = std::make_unique<Number>(NodeType::Number, lexer.getLineNum());
    if (tkType == LexType::INTCON) {
        // TODO
        number->val = lexer.getNumber();
        printTk;
        readTk;
    }
    ofs << "<Number>" << std::endl;
    return number;
}

std::unique_ptr<UnaryExp> Parser::parseUnaryExp() {
    auto unaryExp = std::make_unique<UnaryExp>(NodeType::UnaryExp, lexer.getLineNum());
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
                    printError(unaryExp->getLineNum(), "j");
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

std::unique_ptr<UnaryOp> Parser::parseUnaryOp() {
    auto unaryOp = std::make_unique<UnaryOp>(NodeType::UnaryOp, lexer.getLineNum());
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

std::unique_ptr<FuncRParams> Parser::parseFuncRParams() {
    auto funcRParams = std::make_unique<FuncRParams>(NodeType::FuncRParams, lexer.getLineNum());
    funcRParams->addChild(parseExp());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcRParams->addChild(parseExp());
    }
    ofs << "<FuncRParams>" << std::endl;
    return funcRParams;
}

std::unique_ptr<MulExp> Parser::parseMulExp() {
    auto mulExp = std::make_unique<MulExp>(NodeType::MulExp, lexer.getLineNum());
    mulExp->addChild(parseUnaryExp());
    while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
        auto temp = std::make_unique<MulExp>(NodeType::MulExp, lexer.getLineNum());
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
        temp->addChild(parseUnaryExp());
        mulExp.swap(temp);
    }
    ofs << "<MulExp>" << std::endl;
    return mulExp;
}

std::unique_ptr<AddExp> Parser::parseAddExp() {
    auto addExp = std::make_unique<AddExp>(NodeType::AddExp, lexer.getLineNum());
    addExp->addChild(parseMulExp());
    while (tkType == LexType::PLUS || tkType == LexType::MINU) {
        auto temp = std::make_unique<AddExp>(NodeType::AddExp, lexer.getLineNum());
        if (tkType == LexType::PLUS) {
            temp->op = 0;
        } else if (tkType == LexType::MINU) {
            temp->op = 1;
        }
        ofs << "<AddExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(addExp));
        temp->addChild(parseMulExp());
        addExp.swap(temp);
    }
    ofs << "<AddExp>" << std::endl;
    return addExp;
}

std::unique_ptr<RelExp> Parser::parseRelExp() {
    auto relExp = std::make_unique<RelExp>(NodeType::RelExp, lexer.getLineNum());
    relExp->addChild(parseAddExp());
    while (tkType == LexType::GRE || tkType == LexType::GEQ ||
           tkType == LexType::LSS || tkType == LexType::LEQ) {
        auto temp = std::make_unique<RelExp>(NodeType::RelExp, lexer.getLineNum());
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
        temp->addChild(parseAddExp());
        relExp .swap(temp);
    }
    ofs << "<RelExp>" << std::endl;
    return relExp;
}

std::unique_ptr<EqExp> Parser::parseEqExp() {
    auto eqExp = std::make_unique<EqExp>(NodeType::EqExp, lexer.getLineNum());
    eqExp->addChild(parseRelExp());
    while (tkType == LexType::EQL || tkType == LexType::NEQ) {
        auto temp = std::make_unique<EqExp>(NodeType::EqExp, lexer.getLineNum());
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
        temp->addChild(parseRelExp());
        eqExp.swap(temp);
    }
    ofs << "<EqExp>" << std::endl;
    return eqExp;
}

std::unique_ptr<LAndExp> Parser::parseLAndExp() {
    auto lAndExp = std::make_unique<LAndExp>(NodeType::LAndExp, lexer.getLineNum());
    lAndExp->addChild(parseEqExp());
    while (tkType == LexType::AND) {
        auto temp = std::make_unique<LAndExp>(NodeType::LAndExp, lexer.getLineNum());
        ofs << "<LAndExp>" << std::endl;
        printTk;
        readTk;
        //auto rightEqExp = std::make_unique<EqExp>(NodeType::EqExp, lexer.getLineNum());
        temp->addChild(std::move(lAndExp));
        temp->addChild(parseEqExp());
        lAndExp.swap(temp);
    }
    ofs << "<LAndExp>" << std::endl;
    return lAndExp;
}

std::unique_ptr<LOrExp> Parser::parseLOrExp() {
    auto lOrExp = std::make_unique<LOrExp>(NodeType::LOrExp, lexer.getLineNum());
    lOrExp->addChild(parseLAndExp());
    while (tkType == LexType::OR) {
        auto temp = std::make_unique<LOrExp>(NodeType::LOrExp, lexer.getLineNum());
        ofs << "<LOrExp>" << std::endl;
        printTk;
        readTk;
        temp->addChild(std::move(lOrExp));
        temp->addChild(parseLAndExp());
        lOrExp.swap(temp);
    }
    ofs << "<LOrExp>" << std::endl;
    return lOrExp;
}

std::unique_ptr<ConstExp> Parser::parseConstExp() {
    auto constExp = std::make_unique<ConstExp>(NodeType::ConstExp, lexer.getLineNum());
    constExp->addChild(parseAddExp());
    ofs << "<ConstExp>" << std::endl;
    return constExp;
}