#include <stdio.h>

int unusedFunction() {
    int x = 10 + 20;  // Might think is Unused
    return x;
}

int main() {
    int a = 1 + 2;  // Used
    printf("%d\n", a);
    return 0;
}