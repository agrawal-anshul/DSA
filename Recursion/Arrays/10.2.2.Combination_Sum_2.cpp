// https://leetcode.com/problems/combination-sum-ii/
// Method-2: Iteration + Recursion


#include <iostream>
#include <vector>
using namespace std;

void combinationSum2Helper(vector<int>& candidates, int idx, int target, vector<int>& selection,vector<vector<int>>& res){
      if (target < 0) {
         return;
      }
      if(target == 0){
         res.push_back(selection);
         return;
      }

      // handle duplicates
      for(int i=idx;i<candidates.size();i++){
         if(i > idx && candidates[i-1] == candidates[i]){
            continue;
         }
         if (candidates[i] > target)break;
      
         // take
         selection.push_back(candidates[i]);
         combinationSum2Helper(candidates,i+1,target-candidates[i],selection,res);
         // not-take
         selection.pop_back();
      }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
      sort(candidates.begin(),candidates.end());
      vector<vector<int>>res;
      vector<int>selection;
      combinationSum2Helper(candidates,0,target,selection,res);
      return res;
}


int main(){
   int n,target;
   cin>>n;
   cin>>target;
   vector<int> nums(n);
   for(int i=0;i<n;i++){
      cin>>nums[i];
   }

   vector<vector<int>>res;
   res = combinationSum2(nums,target);
   
   for(auto it:res){
      for(auto it2:it){
         cout<<it2<<" ";
      }
      cout<<endl;
   }
}

/*
I/P-1:
======
7
8
10 1 2 7 6 1 5

O/P:
====
1 1 6 
1 2 5 
1 7 
2 6 

I/P-2:
======
5
5
2 5 2 1 2

O/P:
====
1 2 2
5
*/ 
