from typing import List

# ============================================================
# M-1: Include/Exclude + skip duplicates BEFORE the exclude
#      (advance index over equal neighbors before excluding)
# ============================================================

def generate_subsets(nums: List[int],
                     subset: List[int],
                     idx: int,
                     out: List[List[int]]) -> None:
    """
    Backtracking with include/exclude.
    After exploring the INCLUDE branch for nums[idx], we advance idx over any
    equal neighbors before exploring the EXCLUDE branch to avoid duplicate subsets.

    Time Complexity (TC): O(n * 2^n)
      - There are 2^n subsets; copying a subset into out can take up to O(n).
    Space Complexity (SC): O(n) auxiliary (recursion stack + current subset)
      - Output itself is O(n * 2^n), which is unavoidable.
    """
    if idx == len(nums):
        out.append(subset[:])  # snapshot
        return

    # -------- INCLUDE current element --------
    subset.append(nums[idx])
    generate_subsets(nums, subset, idx + 1, out)

    # -------- SKIP DUPLICATES BEFORE EXCLUDE --------
    # Move j forward past all duplicates of nums[idx]
    j = idx
    while j + 1 < len(nums) and nums[j + 1] == nums[j]:
        j += 1

    # -------- EXCLUDE the entire duplicate block --------
    subset.pop()
    generate_subsets(nums, subset, j + 1, out)


def subsets_with_dup(nums: List[int]) -> List[List[int]]:
    """Wrapper: sort then backtrack (Method 1)."""
    nums.sort()
    out: List[List[int]] = []
    generate_subsets(nums, [], 0, out)
    return out


"""
┌──────────────────────────────────────────────────────────────┐
│  Call tree — Method 1 (Include/Exclude + Skip dups before EX) │
└──────────────────────────────────────────────────────────────┘
Example: nums = [1, 2, 2, 3]

idx generate_subsets(idx=0), subset = []
│
├── INCLUDE nums[0]=1 → subset=[1]
│   └─ generate_subsets(idx=1)
│       │
│       ├── INCLUDE nums[1]=2 → subset=[1,2]
│       │   └─ generate_subsets(idx=2)
│       │       │
│       │       ├── INCLUDE nums[2]=2 → subset=[1,2,2]
│       │       │   └─ generate_subsets(idx=3)
│       │       │       ├── INCLUDE nums[3]=3 → subset=[1,2,2,3] → dfs(4): add [1,2,2,3]
│       │       │       └── EXCLUDE 3 → dfs(4): add [1,2,2]
│       │       │
│       │       └── SKIP dups before EX (j=2) → dfs(3)
│       │           ├── INCLUDE 3 → subset=[1,2,3] → dfs(4): add [1,2,3]
│       │           └── EXCLUDE 3 → dfs(4): add [1,2]
│       │
│       └── Backtrack subset=[1]; SKIP dups (j=2) → dfs(3)
│           ├── INCLUDE 3 → subset=[1,3] → dfs(4): add [1,3]
│           └── EXCLUDE 3 → dfs(4): add [1]
│
└── Backtrack subset=[]; SKIP dups (j=0) → dfs(1)
    │
    ├── INCLUDE nums[1]=2 → subset=[2]
    │   └─ generate_subsets(idx=2)
    │       │
    │       ├── INCLUDE nums[2]=2 → subset=[2,2]
    │       │   └─ generate_subsets(idx=3)
    │       │       ├── INCLUDE nums[3]=3 → subset=[2,2,3] → dfs(4): add [2,2,3]
    │       │       └── EXCLUDE 3 → dfs(4): add [2,2]
    │       │
    │       └── SKIP dups before EX (j=2) → dfs(3)
    │           ├── INCLUDE 3 → subset=[2,3] → dfs(4): add [2,3]
    │           └── EXCLUDE 3 → dfs(4): add [2]
    │
    └── Backtrack subset=[]; SKIP dups (j=2) → dfs(3)
        ├── INCLUDE 3 → subset=[3] → dfs(4): add [3]
        └── EXCLUDE 3 → dfs(4): add []

Collected (order may vary): [[], [1], [1,2], [1,2,2], [1,2,2,3], [1,2,3], [1,3], [2], [2,2], [2,2,3], [2,3], [3]]
"""


# ============================================================
# M-2: Canonical for-loop backtracking (skip dup at same depth)
#      if i > idx and nums[i] == nums[i-1]: continue
# ============================================================

def generate_subsets2(nums: List[int],
                      subset: List[int],
                      idx: int,
                      out: List[List[int]]) -> None:
    """Standard for-loop backtracking; skip duplicates at the same depth."""
    out.append(subset[:])
    for i in range(idx, len(nums)):
        # Skip duplicates at THIS recursion depth
        if i > idx and nums[i] == nums[i - 1]:
            continue
        subset.append(nums[i])
        generate_subsets2(nums, subset, i + 1, out)
        subset.pop()


def subsets_with_dup_backtrack(nums: List[int]) -> List[List[int]]:
    """Wrapper: sort then backtrack (Method 2)."""
    nums.sort()
    out: List[List[int]] = []
    generate_subsets2(nums, [], 0, out)
    return out


"""
┌──────────────────────────────────────────────────────┐
│  Call tree — Method 2 (For-loop; skip dup at depth)  │
└──────────────────────────────────────────────────────┘
Example: nums = [1, 2, 2, 3]

generate_subsets2(idx=0), subset=[] → add []
│
├── i=0 choose 1 → subset=[1]
│   └─ generate_subsets2(idx=1) → add [1]
│       │
│       ├── i=1 choose 2 → subset=[1,2]
│       │   └─ generate_subsets2(idx=2) → add [1,2]
│       │       │
│       │       ├── i=2 choose 2 → subset=[1,2,2]
│       │       │   └─ generate_subsets2(idx=3) → add [1,2,2]
│       │       │       ├── i=3 choose 3 → subset=[1,2,2,3] → dfs(4): add [1,2,2,3]
│       │       │       └── end loop
│       │       └── i=3 choose 3 → subset=[1,2,3] → dfs(4): add [1,2,3]
│       │
│       └── i=2 skipped (nums[2]==nums[1] and i>idx)
│       └── i=3 choose 3 → subset=[1,3] → dfs(4): add [1,3]
│
├── i=1 choose 2 → subset=[2]
│   └─ generate_subsets2(idx=2) → add [2]
│       │
│       ├── i=2 choose 2 → subset=[2,2]
│       │   └─ generate_subsets2(idx=3) → add [2,2]
│       │       ├── i=3 choose 3 → subset=[2,2,3] → dfs(4): add [2,2,3]
│       │       └── end loop
│       │
│       └── i=3 choose 3 → subset=[2,3] → dfs(4): add [2,3]
│
└── i=2 skipped (nums[2]==nums[1] and i>idx)
└── i=3 choose 3 → subset=[3] → dfs(4): add [3]

Collected (order may vary): [[], [1], [1,2], [1,2,2], [1,2,2,3], [1,2,3], [1,3], [2], [2,2], [2,2,3], [2,3], [3]]
"""


# ===================
# Example usage
# ===================
if __name__ == "__main__":
    nums = [1, 2, 2, 3]

    print("M-1 (include/exclude, skip dups before exclude):")
    ans1 = subsets_with_dup(nums)
    for s in ans1:
        print("{", " ".join(map(str, s)), "}")

    print("\nM-2 (for-loop backtracking, skip dup at depth):")
    ans2 = subsets_with_dup_backtrack(nums)
    for s in ans2:
        print("{", " ".join(map(str, s)), "}")
