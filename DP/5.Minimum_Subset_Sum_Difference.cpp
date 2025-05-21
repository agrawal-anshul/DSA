/*
Problem: Minimum Subset Sum Difference
----------------------------------------

Given an array `nums` of `n` positive integers, partition it into two subsets such that the
difference of their sums is minimized.

Goal:
- Find the **minimum possible absolute difference** between the sums of the two subsets.

Example:
---------
Input: nums = [1, 6, 11, 5]
Output: 1
Explanation: Subsets {1, 5, 6} and {11} have sums 12 and 11 → |12 - 11| = 1

Subproblem Definition:
------------------------
Let totalSum = sum of all elements in the array.
Let dp[i][s] = true if it's possible to make a subset with sum 's' using first 'i' elements.
We try to find the subset sum s1 such that abs(totalSum - 2 * s1) is minimized.

Approach 1: Plain Recursion
-----------------------------
- Try including or excluding each element.
- Recurse over all subsets, compute the difference between total and subset sum.

Approach 2: Memoization
-------------------------
- Same as recursion, but memoize overlapping subproblems.

Approach 3: Bottom-Up DP
--------------------------
- Use 2D table dp[n+1][sum+1] where dp[i][j] tells whether a subset with sum 'j'
  is possible using first 'i' elements.

Approach 4: Space Optimization
-------------------------------
- Compress 2D dp to 1D since we only need the previous row at any step.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

class MinSubsetSumDiffDP {
public:
    // 1. Plain Recursion
    int solveRecursive(int i, int sum1, int total, const vector<int>& nums) {
        if (i == (int)nums.size()) {
            int sum2 = total - sum1;
            return abs(sum1 - sum2);
        }
        int include = solveRecursive(i + 1, sum1 + nums[i], total, nums);
        int exclude = solveRecursive(i + 1, sum1, total, nums);
        return min(include, exclude);
    }

    // 2. Top-Down Memoization
    int solveMemo(int i, int sum1, int total, const vector<int>& nums,
                  vector<vector<int>>& memo) {
        if (i == (int)nums.size()) {
            int sum2 = total - sum1;
            return abs(sum1 - sum2);
        }
        if (memo[i][sum1] != -1) return memo[i][sum1];

        int include = solveMemo(i + 1, sum1 + nums[i], total, nums, memo);
        int exclude = solveMemo(i + 1, sum1, total, nums, memo);

        return memo[i][sum1] = min(include, exclude);
    }

    // 3. Bottom-Up DP
    int solveBottomUp(const vector<int>& nums) {
        int total = 0;
        for (int num : nums) total += num;
        int n = (int)nums.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(total + 1, false));
        dp[0][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= total; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i - 1]) {
                    dp[i][j] = dp[i][j] or dp[i - 1][j - nums[i - 1]];
                }
            }
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (dp[n][s1]) {
                int s2 = total - s1;
                minDiff = min(minDiff, abs(s1 - s2));
            }
        }
        return minDiff;
    }

    // 4. Space Optimized DP
    int solveSpaceOptimized(const vector<int>& nums) {
        int total = 0;
        for (int num : nums) total += num;
        int n = (int)nums.size();

        vector<bool> prev(total + 1, false);
        prev[0] = true;

        for (int i = 0; i < n; i++) {
            vector<bool> curr = prev;
            for (int j = nums[i]; j <= total; j++) {
                curr[j] = prev[j] or prev[j - nums[i]];
            }
            prev = curr;
        }

        int minDiff = INT_MAX;
        for (int s1 = 0; s1 <= total / 2; s1++) {
            if (prev[s1]) {
                int s2 = total - s1;
                minDiff = min(minDiff, abs(s1 - s2));
            }
        }
        return minDiff;
    }
};

int main() {
    MinSubsetSumDiffDP solver;
    vector<int> nums = {1, 6, 11, 5};
    int total = 0;
    for (int x : nums) total += x;

    vector<vector<int>> memo(nums.size(), vector<int>(total + 1, -1));

    cout << "Recursive: " << solver.solveRecursive(0, 0, total, nums) << endl;
    cout << "Memoized: " << solver.solveMemo(0, 0, total, nums, memo) << endl;
    cout << "Bottom-Up: " << solver.solveBottomUp(nums) << endl;
    cout << "Space Optimized: " << solver.solveSpaceOptimized(nums) << endl;
    return 0;
}

/*
Dry Run for nums = [1, 6, 11, 5]
-------------------------------
Total sum = 23
Check subset sums from 0 to 11:
Valid subsets: 11 and 12 → diff = |12 - 11| = 1

Summary Table:
-------------------------------
| Approach         | Time       | Space         |
|------------------|------------|---------------|
| Recursive        | O(2^n)     | O(n)          |
| Memoized         | O(n * sum) | O(n * sum)    |
| Bottom-Up DP     | O(n * sum) | O(n * sum)    |
| Space Optimized  | O(n * sum) | O(sum)        |
*/
