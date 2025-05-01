int main() {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += i + i;  // Replace with sum += 0 - i
    }
    return sum;
}