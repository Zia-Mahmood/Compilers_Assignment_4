int main() {
    int a = 5;
    int b = 10;
    int x = a + a;  // Replace with x = 0 - a
    int y = a + b;  // Should not be replaced
    return x + y;
}