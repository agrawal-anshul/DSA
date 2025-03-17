#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr, int n) {
   for (int i = 0; i < n; i++) {
       int j = i ; //  key = arr[i] or arr[j] (as j=i)
       // Shift elements that are greater than key
       while (j > 0 && arr[j-1] > arr[j]) {
           swap(arr[j-1],arr[j]);
           j--;
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

   insertionSort(arr,n);

   // Print sorted array
   for (auto it : arr) {
       cout << it << " ";
   }
   cout << endl;
   
   return 0;
}
