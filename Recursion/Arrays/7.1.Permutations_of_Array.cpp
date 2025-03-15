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




/*

permute({1, 2, 3}, idx=0)
 ├── swap(nums[0], nums[0]) → {1, 2, 3}
 │   ├── permute({1, 2, 3}, idx=1)
 │   │   ├── swap(nums[1], nums[1]) → {1, 2, 3}
 │   │   │   ├── permute({1, 2, 3}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {1, 2, 3}
 │   │   │   │   │   ├── permute({1, 2, 3}, idx=3) → **Store {1, 2, 3}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {1, 2, 3}
 │   │   │   ├── Backtrack → swap(nums[1], nums[1]) → {1, 2, 3}
 │   │   ├── swap(nums[1], nums[2]) → {1, 3, 2}
 │   │   │   ├── permute({1, 3, 2}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {1, 3, 2}
 │   │   │   │   │   ├── permute({1, 3, 2}, idx=3) → **Store {1, 3, 2}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {1, 3, 2}
 │   │   │   ├── Backtrack → swap(nums[1], nums[2]) → {1, 2, 3}
 │   ├── Backtrack → swap(nums[0], nums[0]) → {1, 2, 3}
 │
 ├── swap(nums[0], nums[1]) → {2, 1, 3}
 │   ├── permute({2, 1, 3}, idx=1)
 │   │   ├── swap(nums[1], nums[1]) → {2, 1, 3}
 │   │   │   ├── permute({2, 1, 3}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {2, 1, 3}
 │   │   │   │   │   ├── permute({2, 1, 3}, idx=3) → **Store {2, 1, 3}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {2, 1, 3}
 │   │   │   ├── Backtrack → swap(nums[1], nums[1]) → {2, 1, 3}
 │   │   ├── swap(nums[1], nums[2]) → {2, 3, 1}
 │   │   │   ├── permute({2, 3, 1}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {2, 3, 1}
 │   │   │   │   │   ├── permute({2, 3, 1}, idx=3) → **Store {2, 3, 1}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {2, 3, 1}
 │   │   │   ├── Backtrack → swap(nums[1], nums[2]) → {2, 1, 3}
 │   ├── Backtrack → swap(nums[0], nums[1]) → {1, 2, 3}
 │
 ├── swap(nums[0], nums[2]) → {3, 2, 1}
 │   ├── permute({3, 2, 1}, idx=1)
 │   │   ├── swap(nums[1], nums[1]) → {3, 2, 1}
 │   │   │   ├── permute({3, 2, 1}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {3, 2, 1}
 │   │   │   │   │   ├── permute({3, 2, 1}, idx=3) → **Store {3, 2, 1}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {3, 2, 1}
 │   │   │   ├── Backtrack → swap(nums[1], nums[1]) → {3, 2, 1}
 │   │   ├── swap(nums[1], nums[2]) → {3, 1, 2}
 │   │   │   ├── permute({3, 1, 2}, idx=2)
 │   │   │   │   ├── swap(nums[2], nums[2]) → {3, 1, 2}
 │   │   │   │   │   ├── permute({3, 1, 2}, idx=3) → **Store {3, 1, 2}**
 │   │   │   │   ├── Backtrack → swap(nums[2], nums[2]) → {3, 1, 2}
 │   │   │   ├── Backtrack → swap(nums[1], nums[2]) → {3, 2, 1}
 │   ├── Backtrack → swap(nums[0], nums[2]) → {1, 2, 3}

*/