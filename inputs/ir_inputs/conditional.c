int main() {
    int a = 5;
    int x;
    if (a > 0) {
        x = a + a;  // Replace with x = 0 - a
    } else {
        x = a + 1;  // Should not be replaced
    }
    return x;
}