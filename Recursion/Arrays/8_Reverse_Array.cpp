#include<iostream>
#include <vector>
using namespace std;

// M-1
void recursiveReverse(vector<int>& nums,int l, int r){
   if(l>=r){
      return;
   }
   swap(nums[l++],nums[r--]);
   recursiveReverse(nums,l,r);
}

// M-2
void recursiveReverse1(int i, vector<int>& nums, int n){
   if(i>=n/2){
      return;
   }
   swap(nums[i],nums[n-i-1]);
   recursiveReverse1(i+1,nums,n);
}

int main(){
   int n;
   cin>>n;
   vector<int> nums(n);
   for(int i=0;i<n;i++){
      cin>>nums[i];
   }
   
   // recursiveReverse(nums,0,n-1);
   recursiveReverse1(0,nums,n);

   for(auto it:nums){
      cout<<it<<" ";
   }
}