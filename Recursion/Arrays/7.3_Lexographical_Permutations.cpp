#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ================================================================
// ========================== METHOD-3 =======================
// ==============Generate Lexographical But iterative manner===============


// A manual recursive implementation of next_permutation.
// This function rearranges the string 's' into its next lexicographical permutation.
// Returns true if such a permutation exists, or false if 's' is the highest permutation.
bool myNextPermutation(string &s) {
  int n = s.size();
  // Step 1: Find the largest index k such that s[k] < s[k+1]
  int k = n - 2;
  while (k >= 0 && s[k] >= s[k + 1])
      k--;
  if (k < 0) return false; // s is in descending order; no next permutation exists.

  // Step 2: Find the largest index l greater than k such that s[k] < s[l]
  int l = n - 1;
  while (s[l] <= s[k])
      l--;

  // Step 3: Swap s[k] and s[l]
  swap(s[k], s[l]);

  // Step 4: Reverse the sequence from s[k+1] to the end
  reverse(s.begin() + k + 1, s.end());

  return true;
}

// Returns a vector of strings containing all lexicographical permutations of s.
// The input string is first sorted to ensure lexicographical order.
vector<string> recursiveNextPermutation(string s) {
  vector<string> result;
  sort(s.begin(), s.end()); // Start with the smallest lexicographical permutation.
  result.push_back(s);
  while (myNextPermutation(s))
      result.push_back(s);
  return result;
}



// ================================================================
// ==========================WRONG METHOD-2 =======================
// ==============Doesnt Generate Lexographical order===============

// This function recursively builds permutations using the remaining characters
// and a prefix that accumulates the chosen characters.
void generateLexPermutations(string& remaining, string currentPrefix, vector<string> &result) {
   // Base case: When no characters remain, the current prefix is a complete permutation.
   if (remaining.empty()) {
       result.push_back(currentPrefix);
       return;
   }
   
   // Loop through each character in the remaining string.
   // Because the input is sorted, duplicates will be adjacent.
   for (int i = 0; i < remaining.size(); i++) {
      // Skip duplicate characters to avoid generating the same permutation more than once.
      //  if (i > 0 && remaining[i] == remaining[i - 1])
      //      continue;
       
       // Form a new string without the character at index i.
       // This represents the remaining characters after choosing one.
       string newRemaining = remaining.substr(0, i) + remaining.substr(i + 1);
       
       // Append the chosen character to the prefix.
       string newPrefix = currentPrefix + remaining[i];
       
       // Recursively generate permutations with the new remaining characters.
       generateLexPermutations(newRemaining, newPrefix, result);
   }
}

// This function returns all lexicographically sorted unique permutations of the input string.
vector<string> lexicographicalPermutations(string input) {
   vector<string> result;
   // Sort the input string to start with the smallest lexicographical order.
   sort(input.begin(), input.end());
   generateLexPermutations(input, "", result);
   return result;
}


// ==================================================================
// ==========================WRONG METHOD-1 =========================
// =====================Doesnt Generate Lexographical order==========

bool isDuplicate(string& S, int start, int end){
   for(int i = start; i < end; i++){
       if( S[i] == S[end] )return true;
   }
   return false;
}
void permute(string& S,int idx, vector<string>& res)
{
   if(idx == S.size()){
       res.push_back(S);
       return;
   }
   for(int i=idx;i<S.size();i++){
       if(isDuplicate(S,idx,i))continue;
       swap(S[idx],S[i]);
       permute(S,idx+1,res);
       swap(S[idx],S[i]);
   }
}

vector<string> permutation(string S){
   vector<string> res={};
   sort(S.begin(),S.end());
   permute(S,0,res);
   return res;
}
// ================================================================
// ================================================================
// ================================================================

int main() 
{  
   
   string S;
   cin>>S;
   
   vector<string>res;
   res = recursiveNextPermutation(S);
  //  res = lexicographicalPermutations(S);
   // res = permutation(S);

   // Print permutations
   for (const auto& it : res) {
      cout << it << endl;
   }
   return 0;
}



/*
---------------------------- Explanation & Function Call Tree Notes ----------------------------

For an input string "ABC" (which is already sorted), the recursion unfolds as follows:

Level 0:
  generateLexPermutations("ABC", "", result)
  
    Iterates over indices 0 to 2:
    - i = 0: Choose 'A'
      New prefix: "A"
      New remaining: "BC"
      --> Calls generateLexPermutations("BC", "A", result)
      
    - i = 1: Choose 'B'
      New prefix: "B"
      New remaining: "AC"
      --> Calls generateLexPermutations("AC", "B", result)
      
    - i = 2: Choose 'C'
      New prefix: "C"
      New remaining: "AB"
      --> Calls generateLexPermutations("AB", "C", result)
      
Level 1:
  For generateLexPermutations("BC", "A", result):
    - i = 0: Choose 'B'
      New prefix: "AB"
      New remaining: "C"
      --> Calls generateLexPermutations("C", "AB", result)
      
    - i = 1: Choose 'C'
      New prefix: "AC"
      New remaining: "B"
      --> Calls generateLexPermutations("B", "AC", result)
      
  For generateLexPermutations("AC", "B", result):
    - i = 0: Choose 'A'
      New prefix: "BA"
      New remaining: "C"
      --> Calls generateLexPermutations("C", "BA", result)
      
    - i = 1: Choose 'C'
      New prefix: "BC"
      New remaining: "A"
      --> Calls generateLexPermutations("A", "BC", result)
      
  For generateLexPermutations("AB", "C", result):
    - i = 0: Choose 'A'
      New prefix: "CA"
      New remaining: "B"
      --> Calls generateLexPermutations("B", "CA", result)
      
    - i = 1: Choose 'B'
      New prefix: "CB"
      New remaining: "A"
      --> Calls generateLexPermutations("A", "CB", result)
      
Level 2 (Base Cases):
  Each call with a remaining string of length 1:
    - generateLexPermutations("C", "AB", result) produces "ABC"
    - generateLexPermutations("B", "AC", result) produces "ACB"
    - generateLexPermutations("C", "BA", result) produces "BAC"
    - generateLexPermutations("A", "BC", result) produces "BCA"
    - generateLexPermutations("B", "CA", result) produces "CAB"
    - generateLexPermutations("A", "CB", result) produces "CBA"

Final Result:
  The vector 'result' contains:
    ABC, ACB, BAC, BCA, CAB, CBA
  which is in strict lexicographical order.
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
generateLexPermutations("ABC", "")
├── i = 0: Choose 'A'
│    └── Call: generateLexPermutations("BC", "A")
│         ├── i = 0: Choose 'B'
│         │    └── Call: generateLexPermutations("C", "AB")
│         │         └── i = 0: Choose 'C'
│         │              └── Call: generateLexPermutations("", "ABC")
│         │                   └── Base case: Add "ABC" to result
│         └── i = 1: Choose 'C'
│              └── Call: generateLexPermutations("B", "AC")
│                   └── i = 0: Choose 'B'
│                        └── Call: generateLexPermutations("", "ACB")
│                             └── Base case: Add "ACB" to result
├── i = 1: Choose 'B'
│    └── Call: generateLexPermutations("AC", "B")
│         ├── i = 0: Choose 'A'
│         │    └── Call: generateLexPermutations("C", "BA")
│         │         └── i = 0: Choose 'C'
│         │              └── Call: generateLexPermutations("", "BAC")
│         │                   └── Base case: Add "BAC" to result
│         └── i = 1: Choose 'C'
│              └── Call: generateLexPermutations("A", "BC")
│                   └── i = 0: Choose 'A'
│                        └── Call: generateLexPermutations("", "BCA")
│                             └── Base case: Add "BCA" to result
└── i = 2: Choose 'C'
     └── Call: generateLexPermutations("AB", "C")
          ├── i = 0: Choose 'A'
          │    └── Call: generateLexPermutations("B", "CA")
          │         └── i = 0: Choose 'B'
          │              └── Call: generateLexPermutations("", "CAB")
          │                   └── Base case: Add "CAB" to result
          └── i = 1: Choose 'B'
               └── Call: generateLexPermutations("A", "CB")
                    └── i = 0: Choose 'A'
                         └── Call: generateLexPermutations("", "CBA")
                              └── Base case: Add "CBA" to result

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
*/