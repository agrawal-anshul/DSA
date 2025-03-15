// !Different from subarray sum 
// *NOTE*: subarray-sum-equals-k link: https://leetcode.com/problems/subarray-sum-equals-k/


#include <iostream>
#include <vector>
using namespace std;

void recursiveSubsetSum(vector<int>&nums, int k, vector<int>& subset, int index, int& sum, vector<vector<int>>& res){
   if(index == nums.size()){
          return;
      }
      // pick
      subset.push_back(nums[index]);
      sum+=nums[index];
      // If sum matches k, add the subset to the result
      if (sum == k) {
          res.push_back(subset);
      }
      recursiveSubsetSum(nums, k, subset, index+1, sum, res);

      // not-pick
      subset.pop_back();
      sum-=nums[index];
      recursiveSubsetSum(nums, k, subset, index+1, sum, res);
  }

int subsetSum(vector<int>& nums, int k) {
   vector<vector<int>>res;
   int sum = 0;
   int index = 0;
   vector<int>subset;
   recursiveSubsetSum(nums, k, subset, index, sum, res);
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

   int res =  subsetSum(arr,k);
    // Print all subsets
    cout<<res<< endl;
    

    return 0;
}


