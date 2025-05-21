/*
Problem: Random Pick with Weight

1. Understanding and Visualization:
-----------------------------------
We are given an array of positive integers representing weights. Our task is to randomly
select an index such that the probability of selecting any index is proportional to
its weight.

Intuition:
- Think of weights as lengths on a number line.
- Convert the weight array into a prefix sum array.
- Choose a random number in [1, total weight] and find the corresponding interval.

Example:
Input: w = [1, 3, 2]
Prefix Sum: [1, 4, 6]
Random Target: 5 → falls in segment [4, 6) → Index 2

Constraints:
- 1 <= w.length <= 10^4
- 1 <= w[i] <= 10^5
- pickIndex() called at most 10^4 times

2. Brute Force:
----------------
Generate a new array of size equal to total sum of weights, where each index appears
`w[i]` times. Then return a random element from this array.

Time: O(sum(w)), Space: O(sum(w)) → infeasible for large weights.

3. Optimization:
----------------
Use prefix sum + binary search.
Build prefix sum in constructor: O(n)
Use binary search during pickIndex: O(log n)

Comparison:
| Method         | Time (pickIndex) | Space      |
|----------------|------------------|------------|
| Brute Force    | O(1)             | O(sum(w))  |
| Prefix + Search| O(log n)         | O(n)       |

4. Algorithm and Complexity:
-----------------------------
- Build prefix sum array of size n.
- On pickIndex, generate a random number in [1, total weight].
- Binary search to find index with prefix[i] >= target.

Time: Constructor O(n), pickIndex O(log n)
Space: O(n)

5. Walkthrough:
----------------
w = [1, 3, 2] → prefix = [1, 4, 6]
Random number: 2 → prefix[1] = 4 >= 2 → return 1
Random number: 5 → prefix[2] = 6 >= 5 → return 2

6. C++23 Implementation:
--------------------------
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Solution {
    vector<int> prefix;
    int total;

    // Helper: binary search for first index such that prefix[i] >= target
    int findIndex(int target) {
        int left = 0;
        int right = (int)prefix.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (prefix[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

public:
    // Constructor: build prefix sum
    Solution(vector<int>& w) {
        int n = (int)w.size();
        prefix.resize(n);
        prefix[0] = w[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + w[i];
        }
        total = prefix[n - 1];
        srand((unsigned)time(nullptr));
    }

    // Randomly pick index based on weight
    int pickIndex() {
        int target = (rand() % total) + 1;
        return findIndex(target);
    }
};

int main() {
    vector<int> weights = {1, 3, 2};
    Solution solution(weights);

    // Sample multiple picks to observe distribution
    vector<int> count(3, 0);
    for (int i = 0; i < 10000; i++) {
        int picked = solution.pickIndex();
        count[picked]++;
    }

    cout << "Index pick frequencies after 10000 trials:\n";
    for (int i = 0; i < 3; i++) {
        cout << "Index " << i << ": " << count[i] << "\n";
    }

    return 0;
}

/*
7. Test Cases:
---------------
Base:
Input: w = [1, 3]
Prefix = [1, 4]
Targets: 1 → 0, 2-4 → 1

Edge:
Input: w = [100000, 1]
Prefix = [100000, 100001]
Target 1–100000 → index 0, 100001 → index 1

Input: w = [1]
Always return index 0
*/
