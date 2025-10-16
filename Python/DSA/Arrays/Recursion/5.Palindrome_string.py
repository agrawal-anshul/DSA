def is_palindrome(s: str, left: int, right: int) -> bool:
    """
    Recursive check if a string is a palindrome.

    Time Complexity (TC): O(n)
        - At each recursive step, we compare two characters and move inward.
        - At most n/2 recursive calls → O(n)

    Space Complexity (SC): O(n)
        - Due to recursion stack depth (up to n/2 calls)
    """
    # Base case: if pointers cross or meet, it's a palindrome
    if left >= right:
        return True
    # If characters mismatch, it's not a palindrome
    if s[left] != s[right]:
        return False
    # Move towards the center
    return is_palindrome(s, left + 1, right - 1)

if __name__ == "__main__":
   s = "malayalam"
   if is_palindrome(s, 0, len(s) - 1):
      print("Yes")
   else:
      print("No")
