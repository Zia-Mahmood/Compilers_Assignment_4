#include <stdio.h>

int main() {
    int a = 1 + 2;  // Used
    int b = a * 3;  // Used
    int c = b - 4;  // Unused
    int d = a / 2;  // Used
    printf("%d %d\n", a, d);
    return 0;
}