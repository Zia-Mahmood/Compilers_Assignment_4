#include <stdio.h>

void func1() {
    printf("func1\n");
}

void func2() {
    func1();  // Direct call to func1
}