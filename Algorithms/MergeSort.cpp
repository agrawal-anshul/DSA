#include <iostream>
#include <vector>
using namespace std;

// Function to merge two sorted subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    vector<int> temp(right - left + 1);

    // Merge two halves into temp array
    while (i <= mid && j <= right) {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }

    // Copy any remaining elements from left subarray
    while (i <= mid) temp[k++] = arr[i++];
    
    // Copy any remaining elements from right subarray
    while (j <= right) temp[k++] = arr[j++];

    // Copy sorted temp array back into the original array
    for (int i = left; i <=right; i++) {
        arr[i] = temp[i-left];
    }
}

// Function to perform Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;  // Base case: single element

    int mid = left + (right - left) / 2;
    
    mergeSort(arr, left, mid);     // Sort left half
    mergeSort(arr, mid + 1, right); // Sort right half
    merge(arr, left, mid, right);   // Merge the sorted halves
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, 0, n - 1);

    // Print sorted array
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
