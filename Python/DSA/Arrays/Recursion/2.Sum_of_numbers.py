def sum_recursive(n, sum):
   if n<1:
      return 0
   return  n + sum_recursive(n-1, sum)

def sum_tail_recursive(n, acc=0):
    if n < 1:
        return acc
    return sum_tail_recursive(n - 1, acc + n)

if __name__ == '__main__':
   n = int(input("Enter a number:"))
   print(f"Sum of first n numbers:{sum_recursive(n,0)}")
   print(f"Sum (tail recursive):{sum_tail_recursive(n)}")

# TC: O(n)
# SC: O(n) Auxiliary Space