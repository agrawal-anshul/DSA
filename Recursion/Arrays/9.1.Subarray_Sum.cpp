// !Different from subset sum (refer 6.3)

// !Different from 6.3_Subarray_sum_equals_k.cpp
// *NOTE*: subarray-sum-equals-k link: https://leetcode.com/problems/subarray-sum-equals-k/



#include <iostream>
#include <vector>
using namespace std;

void recursiveSubarraySum(vector<int>&nums, int k, vector<int>& subarray, int index, int sum, vector<vector<int>>& res){
   if(index == nums.size()){
          return;
      }
      // pick
      subarray.push_back(nums[index]);
      sum+=nums[index];
      // If sum matches k, add the subarray to the result
      if (sum == k) {
          res.push_back(subarray);
      }
      recursiveSubarraySum(nums, k, subarray, index+1, sum, res);

      subarray.pop_back();
      
      // *Note* As it is subarray not subset, it has to be continuous, so we dont have option to not include an element as it will not be a subarray and become a subset then.
      // sum-=nums[index];
      // recursiveSubarraySum(nums, k, subarray, index+1, sum, res); 
      
  }

int subarraySum(vector<int>& nums, int k) {
   vector<vector<int>>res;
   int sum = 0;
   vector<int>subarray;

   // recursiveSubarraySum(nums, k, subarray, index, sum, res);
   for(int index = 0; index<nums.size(); index++){
      recursiveSubarraySum(nums, k, subarray, index, sum, res);
   }
   return res.size();
}


int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int k;
    cin>>k;

   int res =  subarraySum(arr,k);
    // Print all subarrays
    cout<<res<< endl;
    

    return 0;
}


