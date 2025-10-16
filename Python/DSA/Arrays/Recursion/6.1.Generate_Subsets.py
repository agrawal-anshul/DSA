from typing import List

def subsetsBacktracking(nums: List[int], curr_subset: List[int], idx: int, res: List[List[int]], n: int):
    if idx == n:
        # ! res.append(curr_subset) gives unexpected result.
        # ! NOTE: Always append a copy of curr_subset (curr_subset[:]) so results don’t mutate later. 
        res.append(curr_subset[:]) 
        return
    
    # pick 
    curr_subset.append(nums[idx])
    subsetsBacktracking(nums, curr_subset, idx + 1, res, n)
    
    # not-pick
    curr_subset.pop()
    subsetsBacktracking(nums, curr_subset, idx + 1, res, n)

def subsets(nums: List[int]) -> List[List[int]]:
    """
    Generate all subsets (power set) of a list of unique integers.

    Approach:
      - Use backtracking. At each index i, choose to either include nums[i]
        or skip it, exploring both branches.
      - Collect the current path at every step as a valid subset.

    Time Complexity (TC):
      - At each index, we make 2 choices → include or exclude → total 2^n subsets.
      - For each subset, we copy the current path using curr_subset[:] which takes O(n) time.
      - Final TC = O(n * 2^n)

    Space Complexity (SC):
      - Recursion depth can go up to n → O(n) stack usage.
      - Output itself holds 2^n subsets with up to n elements → O(n * 2^n), unavoidable.
      - Auxiliary space = O(n), total space including output = O(n * 2^n).
    """
    res: List[List[int]] = []
    n = len(nums)
    subsetsBacktracking(nums, [], 0, res, n)
    return res


# Example usage
if __name__ == "__main__":
    print(subsets([1, 2, 3]))






