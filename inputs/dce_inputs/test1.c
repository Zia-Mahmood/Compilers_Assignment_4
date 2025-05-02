#include <stdio.h>

int main() {
    int a = 1 + 2;  // Used
    int b = 3 * 4;  // Unused
    int c = a - 5;  // Used
    printf("%d\n", c);
    return 0;
}