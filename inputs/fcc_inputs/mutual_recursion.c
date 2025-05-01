#include <stdio.h>

void funcA(int n);
void funcB(int n);

void funcA(int n) {
    if (n > 0) {
        funcB(n - 1);  // Direct call to funcB
    }
}

void funcB(int n) {
    if (n > 0) {
        funcA(n - 1);  // Direct call to funcA
    }
}

int main() {
    funcA(3);  // Direct call to funcA
    return 0;
}