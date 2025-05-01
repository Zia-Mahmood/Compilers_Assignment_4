#include <stdio.h>

void recursive(int n) {
    if (n > 0) {
        recursive(n - 1);  // Recursive call
    }
}

int main() {
    recursive(3);  // Direct call to recursive
    return 0;
}