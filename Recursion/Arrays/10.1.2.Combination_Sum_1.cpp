// https://leetcode.com/problems/combination-sum/
// Method-2:Iteration + Recursion

#include <iostream>
#include <vector>
using namespace std;

void combinationSumHelper(vector<int>& candidates, int idx, int target, vector<int>& selection,vector<vector<int>>& res){
       if (target < 0) {
           return;
       }
       if(target == 0){
           res.push_back(selection);
           return;
       }
   
       for(int i=idx;i<candidates.size();i++){
           if (candidates[i] > target)break;
           selection.push_back(candidates[i]);
           combinationSumHelper(candidates,i,target-candidates[i],selection,res);
           selection.pop_back();
       }
   }
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      sort(candidates.begin(),candidates.end());
      vector<vector<int>>res;
      vector<int>selection;
      combinationSumHelper(candidates,0,target,selection,res);
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
   res = combinationSum(nums,target);
   
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
4
7
2 3 6 7

O/P:
====
2 2 3 
7 

I/P-2:
======
3
8
2 3 5

O/P:
====
2 2 2 2 
2 3 3 
3 5 

*/ 
