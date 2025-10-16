def print_1_to_n(n):
   if n<1:
      return
   print_1_to_n(n-1)
   print(n)

   
def print_n_to_1(n):
   if n<1:
      return
   print(n)
   print_n_to_1(n-1)


if __name__ == '__main__':
   n = int(input("Enter a number:"))
   print("Printing 1 to n")
   print_1_to_n(n)
   print("Printing n to 1")
   print_n_to_1(n)


# TC: O(n)
# SC: O(n)