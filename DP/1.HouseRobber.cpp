// 198. House Robber - Complete Solution with Deep Intuition and C++23 Code

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. UNDERSTANDING AND VISUALIZATION
/*
   PROBLEM: You are given a list of non-negative integers representing the amount of money at each house. 
   You cannot rob two adjacent houses. Return the maximum amount you can rob without triggering the alarm.

   INPUT: vector<int> nums = {2,7,9,3,1}
   OUTPUT: 12 (Rob house 1 (7) + house 3 (3) + house 4 (1) = 7+3+1 = 11 OR house 0 (2) + house 2 (9) + house 4 (1) = 12)

   KEY INSIGHT:
   - At each house, you have 2 choices:
       * Rob this house → you can't rob the previous one
       * Skip this house → you take the max money up to the previous house

   This leads to a classic DP problem: 
     dp[i] = max(dp[i-1], dp[i-2] + nums[i])
*/

// 2. BRUTE FORCE APPROACH
// Try all subsets of houses such that no two are adjacent (exponential time)
int rob_brute_force(vector<int>& nums, int i = 0) {
    if (i >= nums.size()) return 0;
    return max(rob_brute_force(nums, i + 1), nums[i] + rob_brute_force(nums, i + 2));
}
// Time Complexity: O(2^n), Space: O(n) due to recursion stack

// 1.  Recursive DP without memoization (top-down)
int rob_recursive(vector<int>& nums, int ind) {
    if(ind == 0) return 0;
    if(ind < 0)return 0;
    int pick = nums[ind] + rob_recursive(nums, ind -2);
    int notpick = 0 + rob_recursive(nums, ind - 1);
    return max(pick, notpick);
}

// 2. Memoization (top-down DP)
// Time Complexity: O(n), Space: O(n) for dp array + O(n) for recursion stack
int rob_memoization(vector<int>& nums, int ind, vector<int>& dp) {
    if(ind == 0) return 0;
    if(ind < 0) return 0;
    if(dp[ind] != -1) return dp[ind];
    int pick = nums[ind] + rob_memoization(nums, ind - 2, dp);
    int notpick = 0 + rob_memoization(nums, ind - 1, dp);
    return dp[ind] = max(pick, notpick);
}

// 3. TABULATION APPROACH - Bottom-up DP
// Time Complexity: O(n), Space: O(n) for dp array
int rob_tabulation(vector<int>&nums){
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    vector<int>dp(n,0);

    dp[0] = nums[0];
    dp[1] = max(nums[1], nums[0]);

    for(int i = 2; i<n ; i++){
        int pick = nums[i] + dp[i-2];
        int notpick = 0 + dp[i-1];
        dp[i] = max(pick , notpick);
    }
    return dp[n-1];
}

// 4. TABULATION APPROACH - Bottom-up DP (Space Optimization)
// Time Complexity: O(n), SC: O(1) (only two variables used instead of full dp array)
int rob_space_optimized(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);

    int prev2 = nums[0];        // dp[i-2]
    int prev1 = max(nums[0], nums[1]); // dp[i-1]

    for (int i = 2; i < n; ++i) {
        int curr = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


// 4. ALGORITHM AND COMPLEXITY ANALYSIS
/*
    Step-by-step algorithm:
    1. Handle base cases: size 0, 1, or 2
    2. Initialize prev2 = nums[0], prev1 = max(nums[0], nums[1])
    3. For i from 2 to n-1:
        curr = max(prev1, prev2 + nums[i])
        Shift prev2 and prev1 forward
    4. Return prev1

    Time Complexity: O(n)
    Space Complexity: O(1)
    where n = number of houses
*/

// 5. STEP-BY-STEP WALK-THROUGH
/*
   Example: nums = {2,7,9,3,1}

   i = 0: prev2 = 2
   i = 1: prev1 = max(2, 7) = 7
   i = 2: curr = max(7, 2+9=11) = 11
   i = 3: curr = max(11, 7+3=10) = 11
   i = 4: curr = max(11, 11+1=12) = 12

   Final result = 12
*/

// 6. C++23 IMPLEMENTATION
int main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << "Maximum loot: " << rob_space_optimized(nums) << endl;

    // Brute force test (small input)
    vector<int> test = {1, 2, 3};
    cout << "Brute Force Result (for {1,2,3}): " << rob_space_optimized(test) << endl;
    return 0;
}

/*
7. KEY OBSERVATIONS AND MEMORY AIDS:
- This is a linear DP problem (no trees, graphs, etc.)
- Memorize the recurrence: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
- Think of prev1 = last max, prev2 = max if we skip previous
- In-place trick: you can use two vars (prev1 and prev2) instead of full dp[]
- Related: House Robber II (circular), DP on Trees
*/
