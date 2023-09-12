//
// Created by lyh on 9/12/2023.
//
#include <cstdio>

void function0(int a) {
    printf("normal FuncFParam:%d\n", a);
}

void function1(int a[2]) {
    printf("part of 2 FuncFParam:");
    for (int i = 0; i < 3; i = i + 1) {
        printf("a[%d]=%d,", i, a[i]);
    }
    printf("\n");
}

void function2(int a[][2]) {
    printf("2 Dim FuncFParam:");
    for (int i = 0; i < 2; i = i + 1) {
        for (int j = 0; j < 2; ++j) {
            printf("a[0][%d]=%d,", j, a[i][j]);
        }
    }
    printf("\n");
}


int main() {
    printf("21373302\n");
    const int Const = 2;
    const int oneDimConstArray[3] = {1, 2, 3};
    printf("1 Dim ConstDef:a[0]=%d,a[1]=%d,a[2]=%d,%d\n", oneDimConstArray[0], oneDimConstArray[1], oneDimConstArray[2],
           oneDimConstArray);
    const int towDimConstArray[2][2] = {1, 2, 3, 4};
    printf("2 Dim ConstDef:a[0][0]=%d,a[0][1]=%d,a[1][0]=%d,a[1][1]=%d,%d\n", towDimConstArray[0][0],
           towDimConstArray[0][1],
           towDimConstArray[1][0], towDimConstArray[1][1], towDimConstArray);
    int Var = 2 * Const;
    int oneDimVarArray[3] = {2 * Const, 2 * Const + 1, 2 * Const + 3};
    printf("1 Dim VarDef:a[0]=%d,a[1]=%d,a[2]=%d,%d\n", oneDimVarArray[0], oneDimVarArray[1], oneDimVarArray[2],
           oneDimVarArray);
    int twoDimVarArray[2][2] = {2 * Const, 2 * Const + 1, 2 * Const + 2, 2 * Const + 3};
    printf("2 Dim VarDef:a[0][0]=%d,a[0][1]=%d,a[1][0],a[1][1]=%d,%d\n", twoDimVarArray[0][0], twoDimVarArray[0][1],
           twoDimVarArray[1][0], twoDimVarArray[1][1], twoDimVarArray);
    function1(twoDimVarArray[0]);
    printf("part of 2 Dim FuncFParam:%d\n", oneDimVarArray);
    function2(twoDimVarArray);
    printf("2 Dim FuncFParam:%d\n", twoDimVarArray);
    ++Var;
    ++oneDimVarArray[Var];
    printf("++oneDimVarArray[%d] 1 Dim LVal:%d\n", Var, oneDimVarArray[Var]);
    ++twoDimVarArray[Var][Var];
    printf("++twoDimVarArray[%d][%d] 2 Dim LVal:%d\n", Var, Var, twoDimVarArray[Var][Var]);
    return 0;
}

