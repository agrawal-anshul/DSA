//  Maximize the number of segments of length x, y and z
// https://www.geeksforgeeks.org/maximize-the-number-of-segments-of-length-p-q-and-r/

/*
Problem: Maximize the Number of Segments of Length x, y, z
------------------------------------------------------------

1. Understanding and Visualization
----------------------------------
- You are given an integer 'n' representing the length of a rod.
- You can cut the rod into segments of length `x`, `y`, or `z`.
- The goal is to make the **maximum number of such cuts** so that the total length equals `n`.

Example:
---------
n = 7, x = 5, y = 2, z = 2
- You can cut: 2 + 2 + 2 + 1 ❌ (invalid, 1 is not allowed)
- You can cut: 5 + 2 ✅ → 2 segments
=> Output = 2

Input:
- Integer n (total length)
- Integers x, y, z (allowed segment lengths)

Output:
- Maximum number of segments with given lengths summing to `n` 

Edge Cases:
- n < min(x, y, z) ⇒ output = 0
- n = 0 ⇒ output = 0

2. Brute Force Approach (Recursion)
-------------------------------------
- Try every possible cut using x, y, z.
- Recurse until length becomes 0 or negative.

Time Complexity: Exponential O(3^n)
Space Complexity: O(n) (recursion stack)

3. Optimization with Bottom-Up DP
----------------------------------
- Use a dp[] array where dp[i] stores the maximum number of segments to get length i.
- dp[i] = maximum number of cuts possible for a rod of length i
- dp[0] = 0 (base case: 0 segments to make length 0)

Recurrence:
------------
For all i from 1 to n:
- If i >= x ⇒ dp[i] = max(dp[i], dp[i - x] + 1)
- If i >= y ⇒ dp[i] = max(dp[i], dp[i - y] + 1)
- If i >= z ⇒ dp[i] = max(dp[i], dp[i - z] + 1)

Final Answer: dp[n] if not -1, else 0

4. Algorithm and Complexity Analysis
--------------------------------------
- Initialize dp[0] = 0, and the rest to -1 (unreachable states)
- Loop from 1 to n and update dp[i] using valid cuts

Time: O(n)
Space: O(n)

5. C++23 Implementation
-------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxSegmentsDP {
public:
    int maximizeSegments(int n, int x, int y, int z) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0;  // No cuts needed to get length 0

        // Check if the current length is at least x
        // If so, check if the previous result
        // (dp[i - x]) is valid (not -1)
        // Update dp[i] by considering this cut.
        for (int i = 1; i <= n; i++) {
            if (i >= x and dp[i - x] != -1) {
                dp[i] = max(dp[i], dp[i - x] + 1);
            }
            if (i >= y and dp[i - y] != -1) {
                dp[i] = max(dp[i], dp[i - y] + 1);
            }
            if (i >= z and dp[i - z] != -1) {
                dp[i] = max(dp[i], dp[i - z] + 1);
            }
        }

        return max(0, dp[n]);
    }
};

int main() {
    MaxSegmentsDP solver;
    int n = 7, x = 5, y = 2, z = 2;
    cout << "Maximum number of segments: " << solver.maximizeSegments(n, x, y, z) << endl;
    return 0;
}

/*
6. Step-by-Step DP Table Build
-------------------------------
Inputs: n = 7, x = 5, y = 2, z = 2

We initialize:
dp[0] = 0
All others: dp[1..7] = -1

We fill dp[1] to dp[7] as follows:

Step i = 1:
- i < 2, i < 5 → no cuts possible
=> dp[1] remains -1

Step i = 2:
- i >= y → dp[2] = max(-1, dp[0] + 1) = 1
- i >= z → same update → still 1
=> dp[2] = 1

Step i = 3:
- i - 2 = 1 → dp[1] = -1, skip
=> dp[3] = -1

Step i = 4:
- i - 2 = 2 → dp[2] = 1
→ dp[4] = max(-1, dp[2] + 1) = 2
=> dp[4] = 2

Step i = 5:
- i - x = 0 → dp[0] = 0 → dp[5] = max(-1, 0 + 1) = 1
- i - y = 3 → dp[3] = -1 → skip
=> dp[5] = 1

Step i = 6:
- i - y = 4 → dp[4] = 2 → dp[6] = 2 + 1 = 3
=> dp[6] = 3

Step i = 7:
- i - y = 5 → dp[5] = 1 → dp[7] = max(-1, 1 + 1) = 2
=> dp[7] = 2

Final DP Table:
Index i:     0   1   2   3   4   5   6   7
Value dp[i]: 0  -1   1  -1   2   1   3   2

Answer: dp[7] = 2 ✅
*/
