#include <iostream>
using namespace std;

long long factorialHelper(int n, long long accumulator) {
    if (n == 0 || n == 1) return accumulator; // Base Case
    return factorialHelper(n - 1, n * accumulator); // Tail Recursive Call
}

long long factorial(int n) {
    return factorialHelper(n, 1); // Start with accumulator = 1
}

int main() {
    int n;
    cin >> n;
    cout << "Factorial: " << factorial(n) << endl;
    return 0;
}
