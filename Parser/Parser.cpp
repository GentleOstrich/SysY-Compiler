//
// Created by yh on 2023/9/25.
//
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include "../ErrorCheck/ErrorCheck.h"

#define tkType token.first
#define tkWord token.second
#define readTk token = (lexer.next() == 0) ? lexer.getToken() : make_pair(LexType::NONE, "")
#define printTk ofs << LexType2String(tkType) << " " << tkWord << endl
#define preRead lexer.nnext()
#define prePreRead lexer.nnnext()
#define printError(lineNum, type, info) e_ofs << lineNum << " " << type /*<< " " << info*/ << endl
#define ntLineNum lexer.getLastLineNum()

using namespace std;
extern Lexer lexer;
extern ifstream ifs;
extern ofstream ofs;
extern ofstream e_ofs;
extern ErrorCheck errorCheck;

extern vector<Symbol> symbols;
extern stack<int> symbolTable;

extern int symbolId;


Token token = make_pair(LexType::NONE, "");

// 正常返回 0 错误返回 -1
int Parser::parseCompUnit() {
    symbolTable.push(0);
    readTk;
    while (tkType != LexType::NONE) {
        if (tkType == LexType::CONSTTK) {
            int Decl = parseDecl();
            if (Decl == -1) {
                return -1;
            }
        } else if (tkType == LexType::INTTK) {
            if (preRead == LexType::MAINTK) {
                int MainFuncDef = parseMainFuncDef();
                if (MainFuncDef == -1) {
                    return -1;
                }
            } else if (preRead == LexType::IDENFR) {
                if (prePreRead == LexType::LPARENT) {
                    int FuncDef = parseFuncDef();
                    if (FuncDef == -1) {
                        return -1;
                    }
                } else {
                    int Decl = parseDecl();
                    if (Decl == -1) {
                        return -1;
                    }
                }
            } else {
                return -1;
            }
        } else if (tkType == LexType::VOIDTK) {
            int FuncDef = parseFuncDef();
            if (FuncDef == -1) {
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
        if (ConstDecl == -1) {
            return -1;
        } else {
            return 0;
        }
    } else if (tkType == LexType::INTTK) {
        int VarDecl = parseVarDecl();
        if (VarDecl == -1) {
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
            if (ConstDef == -1) {
                return -1;
            } else {
                while (tkType == LexType::COMMA) {
                    printTk;
                    readTk;
                    int ConstDef = parseConstDef();
                    if (ConstDef == -1) {
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
            printError(ntLineNum, "i", "缺少分号");
            return 0;
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
        int tempSymbolId = symbolId;
        if (!errorCheck.bCheck(tkWord, false)) {
            Symbol symbol(0, tkWord, true, nullptr);
            symbols.insert(symbols.begin() + symbolId, symbol);
            ++symbolId;
        }
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int ConstExp = parseConstExp();
            if (ConstExp == -1) {
                return -1;
            } else {
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    printError(ntLineNum, "k", "缺少右中括号");
                }
                symbols[tempSymbolId].type += 1;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            int ConstInitVal = parseConstInitVal();
            if (ConstInitVal == -1) {
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
        if (ConstInitVal == -1) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int ConstInitVal = parseConstInitVal();
                if (ConstInitVal == -1) {
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
        if (ConstExp == -1) {
            return -1;
        } else {
            ofs << "<ConstInitVal>" << endl;
            return 0;
        }
    }
}

int Parser::parseVarDecl() {
    int BType = parseBType();
    if (BType == -1) {
        return -1;
    } else {
        int VarDef = parseVarDef();
        if (VarDef == -1) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int VarDef = parseVarDef();
                if (VarDef == -1) {
                    return -1;
                }
            }
            if (tkType == LexType::SEMICN) {
                printTk;
                 
                ofs << "<VarDecl>" << endl;
                readTk;
                return 0;
            } else {
                 
                printError(ntLineNum, "i", "缺少分号");
                return 0;
            }
        }
    }
}

int Parser::parseVarDef() {
    if (tkType == LexType::IDENFR) {
        int tempSymbolId = symbolId;
        if (!errorCheck.bCheck(tkWord, false)) {
            Symbol symbol(0, tkWord, false, nullptr);
            symbols.insert(symbols.begin() + symbolId, symbol);
            ++symbolId;
        }
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int ConstExp = parseConstExp();
            if (ConstExp == -1) {
                return -1;
            } else {
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    printError(lexer.getLineNum(), "k", "缺少右中括号");
                }
                symbols[tempSymbolId].type += 1;
            }
        }
        if (tkType == LexType::ASSIGN) {
            printTk;
            readTk;
            int InitVal = parseInitVal();
            if (InitVal == -1) {
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
        if (InitVal == -1) {
            return -1;
        } else {
            while (tkType == LexType::COMMA) {
                printTk;
                readTk;
                int InitVal = parseInitVal();
                if (InitVal == -1) {
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
        if (Exp == -1) {
            return -1;
        } else {
            ofs << "<InitVal>" << endl;
            return 0;
        }
    }
}

int Parser::parseFuncDef() {
    int FuncType = parseFuncType();
    if (FuncType == -1) {
        return -1;
    } else {
        if (tkType == LexType::IDENFR) {
            int tempSymbolId = symbolId;
            if (!errorCheck.bCheck(tkWord, true)) {
                Symbol symbol(-1, tkWord, false, new Func(FuncType, 0));
                symbols.insert(symbols.begin() + symbolId, symbol);
                ++symbolId;
            }
            printTk;
            readTk;
            if (tkType == LexType::LPARENT) {
                symbolTable.push(symbolId);
                printTk;
                readTk;
                if (tkType == LexType::RPARENT) {
                    printTk;
                    readTk;
                } else {
                    if (tkType == LexType::LBRACE) {
                        printError(ntLineNum, "j", "缺少右小括号");
                    } else {
                        int FuncFParams = parseFuncFParams(tempSymbolId);
                        if (FuncFParams == -1) {
                            return FuncFParams;
                        } else {
                            if (tkType == LexType::RPARENT) {
                                printTk;
                                readTk;
                            } else {
                                printError(ntLineNum, "j", "缺少右小括号");
                            }
                            symbols[tempSymbolId].func->paramNum = FuncFParams;
                        }
                    }
                }
                int Block = parseBlock(FuncType);

                symbolId = symbolTable.top();
                symbolTable.pop();

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
                    symbolTable.push(symbolId);
                    int Block = parseBlock(1);
                    if (Block == -1) {
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
        return 1;
    } else if (tkType == LexType::VOIDTK) {
        printTk;
         
        ofs << "<FuncType>" << endl;
        readTk;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseFuncFParams(int tempSymbolId) {
    int FuncFParam = parseFuncFParam();
    if (FuncFParam == -1) {
        return -1;
    }
    int cnt = 1;
    symbols[tempSymbolId].func->paramTypeList.push_back(FuncFParam);
    while (tkType == LexType::COMMA) {
        printTk;
        readTk;
        int FuncFParam = parseFuncFParam();
        if (FuncFParam == -1) {
            return -1;
        } else {
            symbols[tempSymbolId].func->paramTypeList.push_back(FuncFParam);
            cnt++;
        }
    }
    ofs << "<FuncFParams>" << endl;
    return cnt;
}

int Parser::parseFuncFParam() {
    if (tkType == LexType::INTTK) {
        printTk;
        readTk;
        if (tkType == LexType::IDENFR) {
            if (!errorCheck.bCheck(tkWord, false)) {
                Symbol symbol(0, tkWord, false, nullptr);
                symbols.insert(symbols.begin() + symbolId, symbol);
                ++symbolId;
            }
            int type = 0;
            printTk;
            readTk;
            if (tkType == LexType::LBRACK) {
                printTk;
                readTk;
                if (tkType == LexType::RBRACK) {
                    printTk;
                    readTk;
                } else {
                    printError(ntLineNum, "k", "缺少右中括号");
                }
                type++;
                while (tkType == LexType::LBRACK) {
                    printTk;
                    readTk;
                    int ConstExp = parseConstExp();
                    if (ConstExp == -1) {
                        return -1;
                    } else {
                        if (tkType == LexType::RBRACK) {
                            printTk;
                            readTk;
                        } else {
                            printError(ntLineNum, "k", "缺少右中括号");
                        }
                        type++;
                    }
                }
                ofs << "<FuncFParam>" << endl;
                return type;
            } else {
                ofs << "<FuncFParam>" << endl;
                return type;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Parser::parseBlock(int FuncType) {
    if (tkType == LexType::LBRACE) {
        printTk;
        readTk;
        // 3 没有返回值
        int BlockItem = 3;
        int flag = (FuncType == 1) ? 1 : 0; // 1 need return value
        while (tkType != LexType::RBRACE) {
            BlockItem = parseBlockItem(FuncType);
            if (BlockItem == -1) {
                return -1;
            } else if (BlockItem == 2 && flag == 1) {
                flag = 0;
            }
        }
        if (tkType == LexType::RBRACE) {
            if (flag == 1) {
                printError(lexer.getLineNum(), "g", "有返回值的函数缺少return语句");
            }
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

int Parser::parseBlockItem(int FuncType) {
    int Decl = parseDecl();
    if (Decl == 0) {
        return 0;
    } else {
        int Stmt = parseStmt(FuncType, 0);
        if (Stmt == -1) {
            return -1;
        } else {
            return Stmt;
        }
    }
}

int Parser::parseStmt(int FuncType, int isFor) {
    if (tkType == LexType::IFTK) {
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            int Cond = parseCond();
            if (Cond == -1) {
                return -1;
            } else {
                if (tkType != LexType::RPARENT) {
                    printError(ntLineNum, "j", "缺少右小括号");
                } else {
                    printTk;
                    readTk;
                }
                int Stmt = parseStmt(FuncType, 0);
                if (Stmt == -1) {
                    return -1;
                } else {
                    if (tkType == LexType::ELSETK) {
                        printTk;
                        readTk;
                        int Stmt = parseStmt(FuncType, 0);
                        if (Stmt == -1) {
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

                    if (tkType != LexType::RPARENT) {
                        printError(ntLineNum, "j", "缺少右小括号");
                    } else {
                        printTk;
                        readTk;
                    }
                    int Stmt = parseStmt(FuncType, 1);
                    if (Stmt == -1) {
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
    } else if (tkType == LexType::BREAKTK) {
        if (isFor == 0) {
            printError(lexer.getLineNum(), "m", "在非循环块中使用break和continue语句");
        }
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
             
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            printError(ntLineNum, "i", "缺少分号");
             
            return 0;
        }
    } else if (tkType == LexType::CONTINUETK) {
        if (isFor == 0) {
            printError(lexer.getLineNum(), "m", "在非循环块中使用break和continue语句");
        }
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
             
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            printError(ntLineNum, "i", "缺少分号");
             
            return 0;
        }
    } else if (tkType == LexType::RETURNTK) {
        int tempLineNum = lexer.getLineNum();
        printTk;
        readTk;
        if (tkType == LexType::SEMICN) {
            printTk;
             
            ofs << "<Stmt>" << endl;
            readTk;
            return 0;
        } else {
            int Exp = parseExp();
            if (Exp == -1) {
                return -1;
            } else {
                if (FuncType == 0) {
                    printError(tempLineNum, "f", "无返回值的函数存在不匹配的return语句 ");
                }
                if (tkType == LexType::SEMICN) {
                    printTk;
                     
                    ofs << "<Stmt>" << endl;
                    readTk;
                    return 2; // return 有返回值
                } else {
                    printError(ntLineNum, "i", "缺少分号");
                     
                    return 2; // return 有返回值
                }
            }
        }
    } else if (tkType == LexType::PRINTFTK) {
        int tempLineNum = lexer.getLineNum();
        printTk;
        readTk;
        if (tkType == LexType::LPARENT) {
            printTk;
            readTk;
            if (tkType == LexType::STRCON) {
                int cnt = 0, i = 0;
                string tempWord = tkWord;
                while (i < tempWord.length()) {
                    if (tempWord[i] == '%' && tempWord[i + 1] == 'd') {
                        cnt += 1;
                        i += 2;
                    } else {
                        ++i;
                    }
                }
                printTk;
                readTk;
                while (tkType == LexType::COMMA) {
                    printTk;
                    readTk;
                    int Exp = parseExp();
                    if (Exp == -1) {
                        return -1;
                    }
                    cnt--;
                }
                if (cnt == -1) {
                    printError(tempLineNum, "l", "printf中格式字符与表达式个数不匹配");
                }
                if (tkType != LexType::RPARENT) {
                    printError(ntLineNum, "j", "缺少右小括号");
                } else {
                    printTk;
                    readTk;
                }
                if (tkType != LexType::SEMICN) {
                    printError(ntLineNum, "i", "缺少分号");
                } else {
                    printTk;
                    readTk;
                }
                 
                ofs << "<Stmt>" << endl;
                return 0;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    } else if (tkType == LexType::LBRACE) {
        symbolTable.push(symbolId);
        int Block = parseBlock(-1);
        if (Block == -1) {
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
                int LVal = parseLVal(1);
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
                                if (tkType != LexType::RPARENT) {
                                    printError(ntLineNum, "j", "缺少右小括号");
                                } else {
                                    printTk;
                                    readTk;
                                }
                                if (tkType != LexType::SEMICN) {
                                    printError(ntLineNum, "i", "缺少分号");
                                } else {
                                    printTk;
                                    readTk;
                                }
                                ofs << "<Stmt>" << endl;
                                return 0;
                            } else {
                                return -1;
                            }
                        } else {
                            int Exp = parseExp();
                            if (Exp == -1) {
                                return -1;
                            } else {
                                if (tkType == LexType::SEMICN) {
                                    printTk;
                                     
                                    ofs << "<Stmt>" << endl;
                                    readTk;
                                    return 0;
                                } else {
                                    printError(ntLineNum, "i", "缺少分号");
                                     
                                    return 0;
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
                if (Exp == -1) {
                    return -1;
                } else {
                    if (tkType == LexType::SEMICN) {
                        printTk;
                         
                        ofs << "<Stmt>" << endl;
                        readTk;
                        return Exp;
                    } else {
                        printError(ntLineNum, "i", "缺少分号");
                         
                        return Exp;
                    }
                }
            }

        }
    }
    return 0;
}

int Parser::parseForStmt() {
    int LVal = parseLVal(1);
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
    if (AddExp == -1) {
        return -1;
    } else {
        ofs << "<Exp>" << endl;
        return AddExp;
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

int Parser::parseLVal(int change) {
    int n = 0;
    if (tkType == LexType::IDENFR) {
        errorCheck.cCheck(tkWord, false);
        if (change) {
            errorCheck.hCheck(tkWord);
        }
        string tempName = tkWord;
        printTk;
        readTk;
        while (tkType == LexType::LBRACK) {
            printTk;
            readTk;
            int Exp = parseExp();
            if (Exp == -1) {
                return -1;
            }
            if (tkType == LexType::RBRACK) {
                printTk;
                readTk;
            } else {
                printError(ntLineNum, "k", "缺少右中括号");
            }
            n++;
        }
        ofs << "<LVal>" << endl;
        int type = errorCheck.getType(tempName);
        if (type == -1) {
            type = 0;
        }
        return (type - n >= 0) ? (type - n) : -1;
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
                return Exp;
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
            int LVal = parseLVal(0);
            if (LVal == -1) {
                return -1;
            } else {
                ofs << "<PrimaryExp>" << endl;
                return LVal;
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
            errorCheck.cCheck(tkWord, true);
            string funcName = tkWord;
            printTk;
            readTk;
            int funcRet = errorCheck.getFuncRet(funcName);
            printTk;
            readTk;
            if (tkType == LexType::RPARENT) {
                if (errorCheck.dCheck(funcName, 0) == -1) {
                    cout << "---no this func" << endl;
                }
                printTk;
                ofs << "<UnaryExp>" << endl;
                readTk;
                return funcRet;
            } else {
                int FuncRParams = parseFuncRParams(funcName);
                if (FuncRParams == -1) {
                    FuncRParams = 0;
                }
                if (errorCheck.dCheck(funcName, FuncRParams) == -1) {
                    cout << "---no this func" << endl;
                }
                if (tkType != LexType::RPARENT) {
                    printError(ntLineNum, "j", "缺少右小括号");
                } else {
                    printTk;
                    readTk;
                }
                ofs << "<UnaryExp>" << endl;
                return funcRet;
            }
        } else {
            int PrimaryExp = parsePrimaryExp();
            if (PrimaryExp == -1) {
                return -1;
            } else {
                ofs << "<UnaryExp>" << endl;
                return PrimaryExp;
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

int Parser::parseFuncRParams(string funcName) {
    vector<int> paramList = errorCheck.getParamList(funcName);
    int Exp = parseExp(); // 要返回exp的类型
    if (Exp == -1) {
        return -1;
    } else {
        int cnt = 1;
        if (cnt > paramList.size() || paramList[cnt-1] != Exp) {
            printError(lexer.getLineNum(), "e", "函数参数类型不匹配");
        }
        while (tkType == LexType::COMMA) {
            printTk;
            readTk;
            int Exp = parseExp();
            if (Exp == -1) {
                return -1;
            }
            if (cnt >= paramList.size() || paramList[cnt] != Exp) {
                printError(lexer.getLineNum(), "e", "函数参数类型不匹配");
            }
            cnt++;
        }
        ofs << "<FuncRParams>" << endl;
        return cnt;
    }
}

int Parser::parseMulExp() {
    int UnaryExp = parseUnaryExp();
    if (UnaryExp == -1) {
        return -1;
    } else {
        while (tkType == LexType::MULT || tkType == LexType::DIV || tkType == LexType::MOD) {
            ofs << "<MulExp>" << endl;
            printTk;
            readTk;
            int UnaryExp = parseUnaryExp();
            if (UnaryExp == -1) {
                return -1;
            }
        }
        ofs << "<MulExp>" << endl;
        return UnaryExp;
    }
}

int Parser::parseAddExp() {
    int MulExp = parseMulExp();
    if (MulExp == -1) {
        return -1;
    } else {
        while (tkType == LexType::PLUS || tkType == LexType::MINU) {
            ofs << "<AddExp>" << endl;
            printTk;
            readTk;
            int MulExp = parseMulExp();
            if (MulExp == -1) {
                return -1;
            }
        }
        ofs << "<AddExp>" << endl;
        return MulExp;
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
            if (AddExp == -1) {
                return -1;
            }
        }
        ofs << "<RelExp>" << endl;
        return 0;
    } else {
        return -1;
    }
}

int Parser::parseEqExp() {
    int RelExp = parseRelExp();
    if (RelExp == 0) {
        while (tkType == LexType::EQL || tkType == LexType::NEQ) {
            ofs << "<EqExp>" << endl;
            printTk;
            readTk;
            int RelExp = parseRelExp();
            if (RelExp == -1) {
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
            if (EqExp == -1) {
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
            if (LAndExp == -1) {
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

