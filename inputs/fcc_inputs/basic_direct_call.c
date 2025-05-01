#include <stdio.h>

void foo() {
    printf("foo called\n");
}

void bar() {
    foo();  // Direct call to foo
}

int main() {
    bar();  // Direct call to bar
    foo();  // Direct call to foo
    return 0;
}