#include <stdio.h>

void sideEffect() {
    printf("Side effect\n");
}

int main() {
    int a = 1 + 2;  // Unused
    sideEffect();   // Has side effect
    return 0;
}