// https://leetcode.com/problems/permutations-ii/description/
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
// A subarray is a contiguous non-empty sequence of elements within an array.

// Example 1:
// Input: nums = [1,1,1], k = 2
// Output: 2

// Example 2:
// Input: nums = [1,2,3], k = 3
// Output: 2

#include <iostream>
#include<vector>
using namespace std;

bool isDuplicate(vector<int>& nums,int start, int end){
   for(int i = start; i < end; i++){
      if(nums[i] == nums[end])return true;
   }
   return false;
}

void permute(vector<int>& nums,int idx,vector<vector<int>>& res){
   if(idx == nums.size()){
      res.push_back(nums);
      return;
   }
   for (int i = idx; i < nums.size(); i++){
      // Check for duplicates
      if(isDuplicate(nums, idx, i))continue;
      swap(nums[idx],nums[i]);
      permute(nums,idx+1,res);
      swap(nums[idx],nums[i]);
   }
}

/* Driver program to test above functions */
int main() 
{  
   int n;
   cin>>n;
   
   vector<int>nums(n);
   for(int i=0;i<n;i++){
      cin>>nums[i];
   }
   
   vector<vector<int>>res;
   permute(nums,0,res);

   // Print permutations
   for (const auto& it : res) {
      for (int num : it) {
         cout << num << " ";
      }
      cout << endl;
   }


   return 0;
}

/* Function Call Tree:

permute({1, 2, 2}, idx=0)
 ├── isDuplicate({1, 2, 2}, start=0, end=0) → false
 ├── swap(nums[0], nums[0]) → {1, 2, 2}
 │   ├── permute({1, 2, 2}, idx=1)
 │   │   ├── isDuplicate({1, 2, 2}, start=1, end=1) → false
 │   │   ├── swap(nums[1], nums[1]) → {1, 2, 2}
 │   │   │   ├── permute({1, 2, 2}, idx=2)
 │   │   │   │   ├── isDuplicate({1, 2, 2}, start=2, end=2) → false
 │   │   │   │   ├── swap(nums[2], nums[2]) → {1, 2, 2}
 │   │   │   │   │   ├── permute({1, 2, 2}, idx=3) → **Store {1, 2, 2}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {1, 2, 2}
 │   │   │   ├── Backtrack → swap(nums[1], nums[1]) → {1, 2, 2}
 │   │   ├── isDuplicate({1, 2, 2}, start=1, end=2) → **true, SKIP**
 │   │   ├── Backtrack to idx=1
 │   ├── Backtrack → swap(nums[0], nums[0]) → {1, 2, 2}
 │
 ├── isDuplicate({1, 2, 2}, start=0, end=1) → false
 ├── swap(nums[0], nums[1]) → {2, 1, 2}
 │   ├── permute({2, 1, 2}, idx=1)
 │   │   ├── isDuplicate({2, 1, 2}, start=1, end=1) → false
 │   │   ├── swap(nums[1], nums[1]) → {2, 1, 2}
 │   │   │   ├── permute({2, 1, 2}, idx=2)
 │   │   │   │   ├── isDuplicate({2, 1, 2}, start=2, end=2) → false
 │   │   │   │   ├── swap(nums[2], nums[2]) → {2, 1, 2}
 │   │   │   │   │   ├── permute({2, 1, 2}, idx=3) → **Store {2, 1, 2}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {2, 1, 2}
 │   │   │   ├── Backtrack → swap(nums[1], nums[1]) → {2, 1, 2}
 │   │   ├── isDuplicate({2, 1, 2}, start=1, end=2) → false
 │   │   ├── swap(nums[1], nums[2]) → {2, 2, 1}
 │   │   │   ├── permute({2, 2, 1}, idx=2)
 │   │   │   │   ├── isDuplicate({2, 2, 1}, start=2, end=2) → false
 │   │   │   │   ├── swap(nums[2], nums[2]) → {2, 2, 1}
 │   │   │   │   │   ├── permute({2, 2, 1}, idx=3) → **Store {2, 2, 1}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {2, 2, 1}
 │   │   │   ├── Backtrack → swap(nums[1], nums[2]) → {2, 1, 2}
 │   │   ├── Backtrack → swap(nums[0], nums[1]) → {1, 2, 2}
 │
 ├── isDuplicate({1, 2, 2}, start=0, end=2) → **true, SKIP**
 ├── Backtrack to idx=0

 */