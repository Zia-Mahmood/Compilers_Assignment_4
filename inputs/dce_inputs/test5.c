#include <stdio.h>

int main() {
    int a = 1 + 2;  // Used
    if (a > 0) {
        int b = 3 * 4;  // Unused
    } else {
        int c = 5 - 6;  // Unused
    }
    printf("%d\n", a);
    return 0;
}