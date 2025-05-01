#include <stdio.h>

void foo() {
    printf("foo\n");
}

void bar() {
    printf("bar\n");
}

int main() {
    void (*func_ptr)() = foo;
    func_ptr();  // Indirect call to foo
    func_ptr = bar;
    func_ptr();  // Indirect call to bar
    foo();       // Direct call to foo
    return 0;
}