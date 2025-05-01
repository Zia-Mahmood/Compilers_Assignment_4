#include <stdio.h>
#include "external.c"

extern void external_func();  // Declaration of external function
extern void func1();

void local_func() {
    printf("local_func\n");
}

int main() {
    external_func();  // Call to external function
    func1();
    local_func();     // Direct call to local_func
    return 0;
}