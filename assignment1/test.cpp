#include <cstdio>
int func0() {
    return 2;
}

int func1(int a, int b) {
    return a * b;
}

void voidf() {
    return;
}

const int ui = 8+8*4-2/2;

int main() {
    printf("21373302\n");
    printf("21373302\n");
    printf("21373302\n");
    printf("21373302\n");
    {}
    int i = 0;
    int a[3] = {1, 2 * func1(2, 2), 3};
    printf("int a[3] = {1, 2 * func1(2, 2), 3};\n");
    const int b = 2 * func0() * func1(a[1], 6) + func1(2, a[2]) / a[2] + a[2];
    printf("const int b = 2 * func0() * func1(a[1], 6) + func1(2, a[2]) * a[2] + a[2];\n");
    int c = 2 * func0() * func1(a[1], 2) + func1(2, 4);
    printf("int c = 2 * func0() * func1(a[1], 2) + func1(2, 4);\n");
    int d = (c % 2 >= a[2]);
    printf("d = (c * 2 >= a[2]);\n");
    const int e = a[2];
    printf("const int e = a[2];\n");
    int f = (c * 2 == a[2]);
    printf("int f = (c * 2 == a[2]);\n");
    int z = (2 * a[0]);
    z = 4;
    z = (4 + 4);
    z = +4;
    z = -4;
    return 0;
}