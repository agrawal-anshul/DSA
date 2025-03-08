// Given an unsorted array of N elements and an element X. The task is to write a recursive function to check whether the element X is present in the given array or not.
// Example:
// array[] = {1, 2, 3, 4, 5}
// X = 3.

#include <iostream>
#include <vector>
using namespace std;

bool recursiveSearch(vector<int> &arr, int l, int r, int x) { 
   if (r < l) return false; 
   if (arr[l] == x) return true; 
   if (arr[r] == x) return true; 
   return recursiveSearch(arr, l + 1, r - 1, x); 
} 

int main() {
   int n, X;
   cin >> n;

   vector<int> arr(n);
   for (int i = 0; i < n; i++) {
      cin >> arr[i];
   }
   cin >> X;

   if (recursiveSearch(arr, 0, n - 1, X)) {
       cout << "Element found" << endl;
   } else {
       cout << "Element not found" << endl;
   }

   return 0;
}


// Sample I/P:
// 5
// 1 2 3 4 5
// 30
