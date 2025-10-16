def factorial(n):
   if n<=1:
      return 1
   return n * factorial(n-1)
   
def tail_recursive_factorial(n, accumulator = 1):
   if n<=1:
      return accumulator
   return tail_recursive_factorial(n - 1, n * accumulator)


if __name__ == '__main__':
   n = int(input("Enter a number:"))
   print(f"Factorial of {n}: {factorial(n)}")
   print(f"Tail recursive factorial of {n}: {tail_recursive_factorial(n)}")

# TC: O(n)
# SC: O(n) Auxiliary Space