//
// Created by lyh on 2023/11/2.
//

#include "Stmt.h"
void Stmt::setBreak() {
    isBreak = true;
}

void Stmt::setContinue() {
    isContinue = true;
}

void Stmt::setReturn() {
    isReturn = true;
}

void Stmt::setPrintf() {
    isPrintf = true;
}

void Stmt::setGetInt() {
    isGetInt = true;
}