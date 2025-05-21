/**
 * Problem: Find the deepest node in a binary tree.
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Problem Statement:
 * Given a binary tree, return the value of the deepest node. If there are multiple
 * deepest nodes on the same level (left to right), return the rightmost one
 * according to level-order traversal.
 *
 * Tree Example:
 *         A
 *        / \
 *       B   C
 *      / \   \
 *     D   E   F
 *
 * Dry Run (Level Order):
 * Queue: [A] → [B, C] → [D, E, F]
 * Last node visited: F
 *
 * Input: Pointer to the root node
 * Output: Pointer to the deepest node (or its value)
 *
 * Edge Cases:
 * - Empty tree: return nullptr
 * - Single-node tree: root is the deepest
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * DFS with max-depth tracking:
 * - Traverse all nodes while maintaining a depth counter
 * - Track the deepest leaf seen so far
 * - Time: O(n)
 * - Space: O(h) for recursive stack
 *
 * Weaknesses:
 * - Requires managing additional state (max depth + node pointer)
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * Use BFS (Level Order Traversal):
 * - Traverse nodes level by level using a queue
 * - Track the last node dequeued — that will be the deepest
 *
 * Time: O(n) — each node is visited once
 * Space: O(n) — queue can hold at most one full level
 *
 * Comparison Table:
 * | Approach | Time | Space | Notes                          |
 * |----------|------|-------|--------------------------------|
 * | DFS      | O(n) | O(h)  | Manual depth tracking needed   |
 * | BFS      | O(n) | O(n)  | Simple, intuitive, auto-depth  |
 *
 * -----------------------------------------------------------------------------
 * 4. Algorithm and Complexity Analysis:
 * -----------------------------------------------------------------------------
 * Algorithm:
 * 1. Initialize queue with root
 * 2. While queue is not empty:
 *    a. Pop node from front
 *    b. Push its left and right children (if they exist)
 *    c. Keep updating a 'current' pointer to the last node popped
 * 3. Return 'current' as the deepest node
 *
 * Pseudocode:
 *   q.push(root)
 *   while (!q.empty()):
 *       current = q.front()
 *       q.pop()
 *       if (current->left): q.push(current->left)
 *       if (current->right): q.push(current->right)
 *   return current
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *   where n = number of nodes in the tree
 *
 * -----------------------------------------------------------------------------
 * 5. Step-by-Step Walk-through:
 * -----------------------------------------------------------------------------
 * Queue Evolution:
 * [A] → Pop A → Push B, C
 * [B, C] → Pop B → Push D, E
 * [C, D, E] → Pop C → Push F
 * [D, E, F] → Pop D → Pop E → Pop F → last = F
 *
 * Final result: F is the deepest node
 *
 * -----------------------------------------------------------------------------
 * 6. C++23 Implementation:
 */

 #include <iostream>
 #include <queue>
 using namespace std;
 
 struct TreeNode {
     char val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
 };
 
 class Solution {
 public:
     TreeNode* findDeepestNode(TreeNode* root) {
         if (root == nullptr) return nullptr;
 
         queue<TreeNode*> q;
         q.push(root);
         TreeNode* current = nullptr;
 
         while (!q.empty()) {
             current = q.front();
             q.pop();
 
             if (current->left) q.push(current->left);
             if (current->right) q.push(current->right);
         }
 
         return current;
     }
 };
 
 int main() {
     // Sample Tree:
     //         A
     //       /   \
     //      B     C
     //     / \     \
     //    D   E     F
 
     TreeNode* root = new TreeNode('A');
     root->left = new TreeNode('B');
     root->right = new TreeNode('C');
     root->left->left = new TreeNode('D');
     root->left->right = new TreeNode('E');
     root->right->right = new TreeNode('F');
 
     Solution solver;
     TreeNode* result = solver.findDeepestNode(root);
     if (result)
         cout << "Deepest node: " << result->val << endl;
     else
         cout << "Tree is empty." << endl;
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 7. Revision Notes:
  * -----------------------------------------------------------------------------
  * - Deepest = last node visited in level-order (BFS)
  * - Use queue to simulate top-to-bottom, left-to-right traversal
  * - BFS avoids manual depth management
  * - Handles unbalanced trees and all edge cases
  * - Time: O(n), Space: O(n)
  */
 