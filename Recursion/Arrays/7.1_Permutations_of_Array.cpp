// https://www.youtube.com/watch?v=f2ic2Rsc9pU (strivers)

#include <iostream>
#include<vector>
using namespace std;

/* Function to print permutations of string 
This function takes three parameters: 
1. String 
2. Starting index of the string 
3. Ending index of the string. */
void permute(vector<int>& nums,int idx,vector<vector<int>>& res){
   if(idx==nums.size()){
      res.push_back(nums);
      return;
   }
   for (int i = idx; i < nums.size(); i++){
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

   //    // Print permutations using explicit iterators
   //    for (vector<vector<int>>::iterator it = res.begin(); it != res.end(); it++) {
   //       for (vector<int>::iterator jt = it->begin(); jt != it->end(); jt++) {
   //           cout << *jt << " ";
   //       }
   //       cout << endl;
   //   }

   // Print permutations
   for (const auto& it : res) {
      for (int num : it) {
         cout << num << " ";
      }
      cout << endl;
   }


   return 0;
}