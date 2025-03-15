// https://leetcode.com/problems/combination-sum-ii/
// Method 1: Recursive

#include <iostream>
#include <vector>
using namespace std;

// skipDuplicates uses a loop to advance the index past all duplicates
int skipDuplicates(const vector<int>& candidates, int idx) {
      // Advance while the next candidate exists and is equal to the current one.
      while (idx + 1 < candidates.size() && candidates[idx + 1] == candidates[idx]) {
         idx++;
      }
      // Return the index after the duplicates.
      return idx + 1;
}

void combinationSum2Helper(const vector<int>& candidates, int idx, int target,
                           vector<int>& selection, vector<vector<int>>& res) {
      // Base cases.
      if (target == 0) {
         res.push_back(selection);
         return;
      }
      if (idx >= candidates.size() || target < 0) {
         return;
      }
      
      // Option 1: "Take" the candidate at idx.
      selection.push_back(candidates[idx]);
      combinationSum2Helper(candidates, idx + 1, target - candidates[idx], selection, res);

      // Not Take and Skip duplicates
      selection.pop_back(); //Backtrack
      int nextIdx = skipDuplicates(candidates, idx);
      combinationSum2Helper(candidates, nextIdx, target, selection, res);
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
