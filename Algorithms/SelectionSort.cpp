#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i; // Assume the first unsorted element is the smallest
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Update minIndex if a smaller element is found
            }
        }
        // Swap only if the minimum element is different from the current position
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
   int n;
   cin >> n;

   vector<int> arr(n);
   for (int i = 0; i < n; i++) {
       cin >> arr[i];
   }

   selectionSort(arr,n);

   // Print sorted array
   for (auto it : arr) {
       cout << it << " ";
   }
   cout << endl;
   
   return 0;
}
