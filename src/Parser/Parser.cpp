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
    auto* compUnit = new CompUnit();
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
    if (compUnit->children.empty()) {
        delete(compUnit);
        return nullptr;
    } else {
        ofs << "<CompUnit>" << endl;
        return compUnit;
    }
}

Decl* Parser::parseDecl() {
    Decl *decl = new Decl();
    if (tkType == LexType::CONSTTK) {
        decl->addChild(parseConstDecl());
    } else if (tkType == LexType::INTTK) {
        decl->addChild(parseVarDecl());
    }
    if (decl->children.empty()) {
        delete(decl);
        return nullptr;
    } else {
        return decl;
    }
}

ConstDecl* Parser::parseConstDecl() {
    auto* constDecl = new ConstDecl();
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
            readTk;
        }
    }
    if (constDecl->children.empty()) {
        delete(constDecl);
        return nullptr;
    } else {
        ofs << "<ConstDecl>" << endl;
        return constDecl;
    }
}

BType* Parser::parseBType() {
    auto* bType = new BType();
    if (tkType == LexType::INTTK) {
        auto* inttk = new Node(lexer.getToken());
        bType->addChild(inttk);
        printTk;
        readTk;
    }
    if (bType->children.empty()) {
        delete(bType);
        return nullptr;
    } else {
        return bType;
    }
}

ConstDef* Parser::parseConstDef() {
    auto* constDef = new ConstDef();
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
            constDef->setValid();
            printTk;
            readTk;
            constDef->addChild(parseConstInitVal());
            ofs << "<ConstDef>" << endl;
            return constDef;
        }
    }
    if (!constDef->isValid) {
        delete(constDef);
        return nullptr;
    } else {
        ofs << "<ConstDef>" << endl;
        return constDef;
    }
}

ConstInitVal* Parser::parseConstInitVal() {
    auto* constInitVal = new ConstInitVal();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            constInitVal->setValid();
            printTk;
            readTk;
        }
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
    } else {
        constInitVal->addChild(parseConstExp());
    }
    if (constInitVal->children.empty() && !constInitVal->isValid) {
        delete( constInitVal);
        return nullptr;
    } else {
        ofs << "<ConstInitVal>" << endl;
        return constInitVal;
    }
    panic("ConstInitVal");
}

VarDecl* Parser::parseVarDecl() {
    auto* varDecl = new VarDecl();
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
    }
    if (varDecl->children.empty()) {
        delete(varDecl);
        return nullptr;
    } else {
        ofs << "<VarDecl>" << endl;
        return varDecl;
    }
}

VarDef* Parser::parseVarDef() {
    auto* varDef = new VarDef();
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
        }
    }
    if (varDef->children.empty()) {
        delete(varDef);
        return nullptr;
    } else {
        ofs << "<VarDef>" << endl;
        return varDef;
    }
}

InitVal* Parser::parseInitVal() {
    auto* initVal = new InitVal();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        if (tkType == LexType::RBRACE) {
            printTk;
            readTk;
            initVal->setValid();
        }
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
    } else {
        initVal->addChild(parseExp());
    }
    if (!initVal->isValid && initVal->children.empty()) {
        delete(initVal);
        return nullptr;
    } else {
        ofs << "<InitVal>" << endl;
        return initVal;
    }
}

FuncDef* Parser::parseFuncDef() {
    auto* funcDef = new FuncDef();
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
        } 
    }
    if (funcDef->children.empty()) {
        delete(funcDef);
        return nullptr;
    } else {
        ofs << "<FuncDef>" << endl;
        return funcDef;
    }
}

MainFuncDef* Parser::parseMainFuncDef() {
    auto* mainFuncDef = new MainFuncDef();
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
                }
            }
        }
    }
    if (mainFuncDef->children.empty()) {
        delete(mainFuncDef);
        return nullptr;
    } else {
        ofs << "<MainFuncDef>" << endl;
        return mainFuncDef;
    }
}

FuncType* Parser::parseFuncType() {
    auto* funcType = new FuncType();
    if (tkType == LexType::INTTK) {
        auto* tktype = new Node(lexer.getToken());
        funcType->addChild(tktype);
        printTk;
        readTk;
    } else if (tkType == LexType::VOIDTK) {
        auto* tktype = new Node(lexer.getToken());
        funcType->addChild(tktype);
        printTk;
        readTk;
    }
    if (funcType->children.empty()) {
        delete(funcType);
        return nullptr;
    } else {
        ofs << "<FuncType>" << endl;
        return funcType;
    }
}

FuncFParams* Parser::parseFuncFParams() {
    auto* funcFParams = new FuncFParams();
    funcFParams->addChild(parseFuncFParam());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcFParams->addChild(parseFuncFParam());
    }
    if (funcFParams->children.empty()) {
        delete(funcFParams);
        return nullptr;
    } else {
        ofs << "<FuncFParams>" << endl;
        return funcFParams;
    }
}

FuncFParam* Parser::parseFuncFParam() {
    auto* funcFParam = new FuncFParam();
    funcFParam->addChild(parseBType());
    if (tkType == LexType::IDENFR) {
        auto* ident = new Node(lexer.getToken());
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
        }
    }
    if (funcFParam->children.empty()) {
        delete(funcFParam);
        return nullptr;
    } else {
        ofs << "<FuncFParam>" << endl;
        return funcFParam;
    }
}

Block* Parser::parseBlock() {
    auto* block = new Block();
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        while (tkType != LexType::RBRACE) {
            block->addChild(parseBlockItem());
        }
        if (tkType == LexType::RBRACE) {
            block->setValid();
            printTk;
            readTk;
        }
    }
    if (!block->isValid) {
        delete(block);
        return nullptr;
    } else {
        ofs << "<Block>" << endl;
        return block;
    }
}

BlockItem* Parser::parseBlockItem() {
    auto* blockItem = new BlockItem();
    if (tkType == LexType::CONSTTK || tkType == LexType::INTTK) {
        blockItem->addChild(parseDecl());
    } else{
        blockItem->addChild(parseStmt());
    }
    if (blockItem->children.empty()) {
        delete(blockItem);
        return nullptr;
    } else {
        return blockItem;
    }
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
                    }
                    stmt->addChild(parseStmt());
                }
            }
        }
    } else if (tkType == LexType::BREAKTK) {
        auto* breaktk = new Node(lexer.getToken());
        stmt->addChild(breaktk);
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        }
    } else if (tkType == LexType::CONTINUETK) {
        auto* continuetk = new Node(lexer.getToken());
        stmt->addChild(continuetk);
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
            readTk;
        }
    } else if (tkType == LexType::RETURNTK) {
        auto* returntk = new Node(lexer.getToken());
        stmt->addChild(returntk);
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
            }
        }
    } else if (tkType == LexType::PRINTFTK) {
        auto* printftk = new Node(lexer.getToken());
        stmt->addChild(printftk);
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::STRCON) {
                auto* str = new Node(lexer.getToken());
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
                        readTk;
                    }
                }
            }
        }
    } else if (tkType == LexType::LBRACE) {
        stmt->addChild(parseBlock());
    } else {
        if (tkType == LexType::SEMICN) {
            auto* semicn = new Node(lexer.getToken());
            stmt->addChild(semicn);
            printTk;
            readTk;
        } else {
            if (lexer.hasAUntilB('=', ';')) {
                stmt->addChild(parseLVal());
                if (tkType == LexType::ASSIGN) {
                    printTk;
                    readTk;
                    if (tkType == LexType::GETINTTK) {
                        auto* getinttk = new Node(lexer.getToken());
                        stmt->addChild(getinttk);
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
                                    readTk;
                                }
                            }
                        }
                    } else {
                        stmt->addChild(parseExp());
                        if (tkType == LexType::SEMICN) {
                            printTk;
                            readTk;
                        }
                    }
                }
            } else {
                stmt->addChild(parseExp());
                if (tkType == LexType::SEMICN) {
                    printTk;
                    readTk;
                }
            }
        }
    }
    if (stmt->children.empty()) {
        delete(stmt);
        return nullptr;
    } else {
        ofs << "<Stmt>" << endl;
        return stmt;
    }
}

ForStmt* Parser::parseForStmt() {
    auto* forStmt = new ForStmt();
    forStmt->addChild(parseLVal());
    if (tkType == LexType::ASSIGN) {
        printTk;
        readTk;
        forStmt->addChild(parseExp());
    }
    if (forStmt->children.empty()) {
        delete(forStmt);
        return nullptr;
    } else {
        ofs << "<ForStmt>" << endl;
        return forStmt;
    }
}

Exp* Parser::parseExp() {
    auto* exp = new Exp();
    exp->addChild(parseAddExp());
    if (exp->children.empty()) {
        delete(exp);
        return nullptr;
    } else {
        ofs << "<Exp>" << endl;
        return exp;
    }
}

Cond* Parser::parseCond() {
    auto* cond = new Cond();
    cond->addChild(parseLOrExp());
    if (cond->children.empty()) {
        delete(cond);
        return nullptr;
    } else {
        ofs << "<Cond>" << endl;
        return cond;
    }
}

LVal* Parser::parseLVal() {
    auto* lVal = new LVal();
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
    }
    if (lVal->children.empty()) {
        delete(lVal);
        return nullptr;
    } else {
        ofs << "<LVal>" << endl;
        return lVal;
    }
}

PrimaryExp* Parser::parsePrimaryExp() {
    auto* primaryExp = new PrimaryExp();
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
    if (primaryExp->children.empty()) {
        delete(primaryExp);
        return nullptr;
    } else {
        ofs << "<PrimaryExp>" << endl;
        return primaryExp;
    }
}

Number* Parser::parseNumber() {
    auto* number = new Number();
    if (tkType == LexType::INTCON) {
        printTk;
        readTk;
        ofs << "<Number>" << endl;
        return number;
    } else {
        delete(number);
        return nullptr;
    }
}

UnaryExp* Parser::parseUnaryExp() {
    auto* unaryExp = new UnaryExp();
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        unaryExp->addChild(parseUnaryOp());
        unaryExp->addChild(parseUnaryExp());
    } else {
        if (tkType == LexType::IDENFR && preRead == LexType::LPARENT) {
            Node* ident = new Node(lexer.getToken());
            unaryExp->addChild(ident);
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
                }
            }
        } else {
            unaryExp->addChild(parsePrimaryExp());
        }
    }
    if (unaryExp->children.empty()) {
        delete(unaryExp);
        return nullptr;
    } else {
        ofs << "<UnaryExp>" << endl;
        return unaryExp;
    }
}

UnaryOp* Parser::parseUnaryOp() {
    auto* unaryOp = new UnaryOp();
    if (tkType == LexType::PLUS || tkType == LexType::MINU || tkType == LexType::NOT) {
        printTk;
        readTk;
        ofs << "<UnaryOp>" << endl;
        return unaryOp;
    } else {
        delete(unaryOp);
        return nullptr;
    }
}

FuncRParams* Parser::parseFuncRParams() {
    auto* funcRParams = new FuncRParams();
    funcRParams->addChild(parseExp());
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        funcRParams->addChild(parseExp());
    }
    if (funcRParams->children.empty()) {
        delete(funcRParams);
        return nullptr;
    } else {
        ofs << "<FuncRParams>" << endl;
        return funcRParams;
    }
}

MulExp* Parser::parseMulExp() {
    auto* mulExp = new MulExp();
    mulExp->addChild(parseUnaryExp());
    while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
        ofs << "<MulExp>" << endl;
        printTk;
        readTk;
        mulExp->addChild(parseUnaryExp());
    }
    if (mulExp->children.empty()) {
        delete(mulExp);
        return nullptr;
    } else {
        ofs << "<MulExp>" << endl;
        return mulExp;
    }
}

AddExp* Parser::parseAddExp() {
    auto* addExp = new AddExp();
    addExp->addChild(parseMulExp());
    while (tkType == LexType::PLUS || tkType == LexType::MINU) {
        ofs << "<AddExp>" << endl;
        printTk;
        readTk;
        addExp->addChild(parseMulExp());
    }
    if (addExp->children.empty()) {
        delete(addExp);
        return nullptr;
    } else {
        ofs << "<AddExp>" << endl;
        return addExp;
    }
}

RelExp* Parser::parseRelExp() {
    auto* relExp = new RelExp();
    relExp->addChild(parseAddExp());
    while (tkType == LexType::GRE || tkType == LexType::GEQ || tkType == LexType::LSS || tkType == LexType::LEQ) {
        ofs << "<RelExp>" << endl;
        printTk;
        readTk;
        relExp->addChild(parseAddExp());
    }
    if (relExp->children.empty()) {
        delete(relExp);
        return nullptr;
    } else {
        ofs << "<RelExp>" << endl;
        return relExp;
    }
}

EqExp* Parser::parseEqExp() {
    auto* eqExp = new EqExp();
    eqExp->addChild(parseRelExp());
    while (tkType == LexType::EQL || tkType == LexType::NEQ) {
        ofs << "<EqExp>" << endl;
        printTk;
        readTk;
        eqExp->addChild(parseRelExp());
    }
    if (eqExp->children.empty()) {
        delete(eqExp);
        return nullptr;
    } else {
        ofs << "<EqExp>" << endl;
        return eqExp;
    }
}

LAndExp* Parser::parseLAndExp() {
    auto* lAndExp = new LAndExp();
    lAndExp->addChild(parseEqExp());
    while (tkType == LexType::AND) {
        ofs << "<LAndExp>" << endl;
        printTk;
        readTk;
        lAndExp->addChild(parseEqExp());
    }
    if (lAndExp->children.empty()) {
        delete(lAndExp);
        return nullptr;
    } else {
        ofs << "<LAndExp>" << endl;
        return lAndExp;
    }
}

LOrExp* Parser::parseLOrExp() {
    auto* lOrExp = new LOrExp();
    lOrExp->addChild(parseLAndExp());
    while (tkType == LexType::OR) {
        ofs << "<LOrExp>" << endl;
        printTk;
        readTk;
        lOrExp->addChild(parseLAndExp());
    }
    if (lOrExp->children.empty()) {
        delete(lOrExp);
        return nullptr;
    } else {
        ofs << "<LOrExp>" << endl;
        return lOrExp;
    }
}

ConstExp* Parser::parseConstExp() {
    auto* constExp = new ConstExp();
    constExp->addChild(parseAddExp());
    if (constExp->children.empty()) {
        delete (constExp);
        return nullptr;
    } else {
        ofs << "<ConstExp>" << endl;
        return constExp;
    }
}