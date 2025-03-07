// Given a string, the task is to write a recursive function to check if the given string is palindrome or not.

// Examples:

// Input : string = "malayalam"
// Output : Yes
// Reverse of malayalam is also
// malayalam.

// Input : string = "max"
// Output : No
// Reverse of max is not max.

#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& str, int left, int right) {
    if (left >= right) return true; // Base Case: If pointers cross, it's a palindrome
    if (tolower(str[left]) != tolower(str[right]) ) return false; // Mismatch found, not a palindrome
    return isPalindrome(str, left + 1, right - 1); // Recursive call
}

int main() {
    string str;
    cin >> str; // Input string

    if (isPalindrome(str, 0, str.length() - 1)) {
        cout << "Palindrome" << endl;
    } else {
        cout << "Not a Palindrome" << endl;
    }

    return 0;
}

// Sample I/P & O/P:
// racecar
// Palindrome

// hello
// Not a Palindrome
