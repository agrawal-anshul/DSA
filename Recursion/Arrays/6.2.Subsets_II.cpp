// https://leetcode.com/problems/subsets-ii/description/
// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

// The solution set must not contain duplicate subsets. Return the solution in any order.
// Example 1:

// Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
// Example 2:

// Input: nums = [0]
// Output: [[],[0]]
 
#include <iostream>
#include <vector>
using namespace std;

void generateSubsets(vector<int>& arr, vector<int>& subset, int index, vector<vector<int>>& result) {
	if(index == arr.size()){
		result.push_back(subset);
		return;
	}
	// include current element
	subset.push_back(arr[index]);
	generateSubsets(arr, subset, index+1, result);

   // Skip duplicate element after the first the occurrence
   while(index + 1 < arr.size() && arr[index + 1] == arr[index]){
      index++;   
  }

	// exclude current element
	subset.pop_back();
	generateSubsets(arr, subset, index+1, result);

}

// Wrapper function to return all subsets
vector<vector<int>> getAllSubsets(vector<int>& arr) {
    vector<vector<int>> result;
    vector<int> subset;

    sort(arr.begin(), arr.end());// Sort to handle duplicates
    
    generateSubsets(arr, subset, 0, result);
    return result; // Return vector of subsets
}


int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

	cout<<endl;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

	cout<<endl;

    vector<vector<int>> subsets = getAllSubsets(arr);
    // Print all subsets
    cout << "Result: " << endl;
    for (auto& subset : subsets) {
        cout << "{ ";
        for (int num : subset) cout << num << " ";
        cout << "}" << endl;
    }

    return 0;
}


