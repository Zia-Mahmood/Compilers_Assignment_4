#include <stdint.h>

int test_add() {
    return 5 + 3; // Should fold to 8
}

int test_sub() {
    return 10 - 4; // Should fold to 6
}

int test_mul() {
    return 6 * 7; // Should fold to 42
}

int test_sdiv() {
    return -10 / 2; // Should fold to -5
}

unsigned int test_udiv() {
    return 10u / 2u; // Should fold to 5
}

int test_srem() {
    return 10 % 3; // Should fold to 1
}

unsigned int test_urem() {
    return 10u % 3u; // Should fold to 1
}

int test_shl() {
    return 1 << 3; // Should fold to 8
}

unsigned int test_lshr() {
    return 8u >> 1u; // Should fold to 4
}

int test_ashr() {
    return -8 >> 1; // Should fold to -4
}

int test_and() {
    return 5 & 3; // Should fold to 1
}

int test_or() {
    return 5 | 3; // Should fold to 7
}

int test_xor() {
    return 5 ^ 3; // Should fold to 6
}

int main() {
    return 0;
}