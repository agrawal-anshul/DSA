// https://leetcode.com/problems/subsets/description/
// Given an integer array nums of unique elements, return all possible subsets (the power set).
// The solution set must not contain duplicate subsets. Return the solution in any order.

// Example 1:
// Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

// Example 2:
// Input: nums = [0]
// Output: [[],[0]]

// Soln: https://www.youtube.com/watch?v=Yg5a2FxU4Fo (Aditya Verma)

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

	// exclude current element
	subset.pop_back();
	generateSubsets(arr, subset, index+1, result);

}

// Wrapper function to return all subsets
vector<vector<int>> getAllSubsets(vector<int>& arr) {
    vector<vector<int>> result;
    vector<int> subset;
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



// FUNCTION CALL TREE for {1,2,3}:

// generateSubsets({}, 0)
// ├── include(1) → generateSubsets({1}, 1)
// │   ├── include(2) → generateSubsets({1,2}, 2)
// │   │   ├── include(3) → generateSubsets({1,2,3}, 3) → prints {1,2,3}
// │   │   ├── exclude(3) → generateSubsets({1,2}, 3) → prints {1,2}
// │   │
// │   ├── exclude(2) → generateSubsets({1}, 2)
// │   │   ├── include(3) → generateSubsets({1,3}, 3) → prints {1,3}
// │   │   ├── exclude(3) → generateSubsets({1}, 3) → prints {1}
// │
// ├── exclude(1) → generateSubsets({}, 1)
// │   ├── include(2) → generateSubsets({2}, 2)
// │   │   ├── include(3) → generateSubsets({2,3}, 3) → prints {2,3}
// │   │   ├── exclude(3) → generateSubsets({2}, 3) → prints {2}
// │   │
// │   ├── exclude(2) → generateSubsets({}, 2)
// │   │   ├── include(3) → generateSubsets({3}, 3) → prints {3}
// │   │   ├── exclude(3) → generateSubsets({}, 3) → prints {}