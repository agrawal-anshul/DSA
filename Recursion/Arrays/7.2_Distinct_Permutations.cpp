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