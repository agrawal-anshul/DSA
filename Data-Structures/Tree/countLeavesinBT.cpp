/**
 * Problem: Count the number of leaf nodes in a binary tree.
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Problem Statement:
 * Given the root of a binary tree, return the number of leaf nodes.
 *
 * Definition:
 * - A leaf node is a node with no left and no right child.
 *
 * Example Tree:
 *         A
 *        / \
 *       B   C
 *      / \   \
 *     D   E   F
 *
 * Leaf Nodes: D, E, F → Count = 3
 *
 * Input: Pointer to root node of binary tree.
 * Output: Integer (total leaf count).
 *
 * Edge Cases:
 * - Empty tree (root = nullptr) → 0 leaves.
 * - Single-node tree → 1 leaf.
 *
 * Algorithm:
 * - Traverse the tree recursively.
 * - If node is null → return 0
 * - If node has no left and right child → return 1 (it's a leaf)
 * - Else return countLeaves(left) + countLeaves(right)
 *
 * Tip:
 * - A node is a leaf if both its left and right child pointers are null.
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * Use a recursive DFS traversal.
 *
 * Time Complexity: O(n) — each node visited once
 * Space Complexity: O(h) — call stack, where h = height of tree
 *
 * Weakness:
 * - Stack overflow on highly unbalanced/deep trees.
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * Iterative approach using BFS or DFS can be used to control stack depth.
 * However, recursive version is optimal and clean for balanced or typical trees.
 *
 * -----------------------------------------------------------------------------
 * 4. Step-by-Step Walk-through:
 * -----------------------------------------------------------------------------
 * Tree:
 *       A
 *     /   \
 *    B     C
 *   / \     \
 *  D   E     F
 *
 * Start from root (A):
 * A → B → D → leaf → count = 1
 *       → E → leaf → count = 2
 *   → C → F → leaf → count = 3
 *
 * Final Count: 3
 *
 * -----------------------------------------------------------------------------
 * 5. C++23 Implementation:
 */

 #include <iostream>
 using namespace std;
 
 struct TreeNode {
     char val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
 };
 
 class Solution {
 public:
     // Recursive DFS to count leaves
     int countLeaves(TreeNode* root) {
         if (root == nullptr) return 0;
         if (root->left == nullptr and root->right == nullptr) return 1;
         return countLeaves(root->left) + countLeaves(root->right);
     }
 };
 
 int main() {
     // Construct the tree:
     //       A
     //     /   \
     //    B     C
     //   / \     \
     //  D   E     F
 
     TreeNode* root = new TreeNode('A');
     root->left = new TreeNode('B');
     root->right = new TreeNode('C');
     root->left->left = new TreeNode('D');
     root->left->right = new TreeNode('E');
     root->right->right = new TreeNode('F');
 
     Solution solver;
     int leafCount = solver.countLeaves(root);
     cout << "Number of leaf nodes: " << leafCount << endl;
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 6. Revision Notes:
  * -----------------------------------------------------------------------------
  * - Leaf node = node with no left and right children
  * - Use recursion: countLeaves(left) + countLeaves(right)
  * - Base case: if root is null → 0; if root is a leaf → 1
  *
  * Complexity:
  * - Time: O(n)
  * - Space: O(h)
  *
  * Tip:
  * - Always check for nullptr first.
  * - Recursion is elegant and expressive for tree-based problems.
  */
 