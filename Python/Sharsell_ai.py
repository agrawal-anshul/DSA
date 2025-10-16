
# You’re a locksmith searching for a set of lost keys in a vast library. 
#  Each key is marked with a number, and you know that two keys are considered "compatible" if the difference between their numbers is exactly a target value. 
#  Your task is to find all pairs of keys that are compatible.
#  However, the library is filled with many keys, and you don’t have time to check every possible pair. Luckily, you have a magical device that helps you efficiently identify the compatible keys.

# nums = [1,2,3,4,5, 100,66] 
# diff = 2

# target = currNum + diff

# dict = {
#     1: 0,
#     2: 1,
#     3: 2,
#     100: 5,
#     ....
# }



# My Wrong code:
# ==============
# def findKeys(nums, diff):
#    nums.sort()
#    # print(nums)
#    mp = {}
#    res = []
#    n = len(nums)
#    # print(n)
#    for i in range(n):
#       target = nums[i] + diff
#       if not mp.get(target, None) == None:
#          print(target)
#          res.append((nums[i], target))
#       mp[nums[i]] = target
#       print(mp)
#    return res
            

# if __name__ == "__main__":
#    nums = [1,2,3,4,5]
#    diff = 2
#    res = findKeys(nums, diff)
#    print(f"res:{res}")



# Solution:
# =========
def findKeys(nums, diff):
   nums.sort()
   print(nums)
   mp = {}
   res = []
   for x in nums:
      if (x - diff) in mp:
         res.append((x - diff, x))
      mp[x] = True
   return res
         

if __name__ == "__main__":
   nums = [1,5,4,3,2]
   diff = 2
   res = findKeys(nums, diff)
   print(f"res:{res}")
