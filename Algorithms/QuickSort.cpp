#include <iostream>
using namespace std;


// int partition(vector<int>& arr, int low, int high) {
//    int pivot = arr[high];          // Pivot is the last element of the subarray.
//    int i = low - 1;                // i is initialized just before the first element.
   
//    for (int j = low; j < high; j++) {
//        if (arr[j] <= pivot) {      // If current element is <= pivot...
//            i++;                   // ...move i to the next position...
//            swap(arr[i], arr[j]);  // ...and swap arr[i] with arr[j].
//        }
//    }
   
//    swap(arr[i + 1], arr[high]);     // Finally, place the pivot after the last smaller element.
//    return i + 1;                  // Return the pivot's final index.
// }


int partition(vector<int>&arr, int low, int high){
   int pivot = arr[high];
   int i=low,j=high-1;
   while(i<=j){
      while(i<=high-1 && arr[i]<=pivot){
         i++;
      }
      while(j>=low && arr[j]>pivot){
         j--;
      }
      if(i<j)swap(arr[i],arr[j]);
   }
   swap(arr[high],arr[i]);
   return i;
}

void qs(vector<int>& arr, int low, int high){
   if(low<high){
      int pivotIndex = partition(arr,low,high);
      qs(arr, low, pivotIndex-1);
      qs(arr, pivotIndex+1, high);
   }
}

void quickSort(vector<int>&arr,int n){
   qs(arr,0, n-1);
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quickSort(arr, n);

    // Print sorted array
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
