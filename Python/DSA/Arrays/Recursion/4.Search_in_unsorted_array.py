def recursive_search(arr: list[int], left: int, right: int, x: int) -> int:
    """
    Recursive search for x in arr by checking both ends.

    Time Complexity (TC): O(n)
        - At each step, one element from either end is checked.
    Space Complexity (SC): O(n) due to recursion stack
        - Depth of recursion can go up to n/2 calls.
    """
    if left > right:
        return -1
    if arr[left] == x:
        return left
    if arr[right] == x:
        return right
    return recursive_search(arr, left + 1, right - 1, x)


if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5]
    x = 3
    idx = recursive_search(arr, 0, len(arr) - 1, x)
    if idx != -1:
        print(f"Element found at index: {idx}")
    else:
        print("Element not found")
