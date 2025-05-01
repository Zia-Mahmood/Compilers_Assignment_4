int main() {
    int arr[2] = {1, 2};
    int *p = arr;
    int x = p[0] + p[0];  // Replace with x = 0 - p[0]
    return x;
}