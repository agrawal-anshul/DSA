/**
 * Problem: Find the deepest node in a binary tree.
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Problem:
 * Given the root of a binary tree, find the **deepest node** — the last node on
 * the last level when traversing the tree level by level (left to right).
 *
 * Example Tree:
 *         A
 *        / \
 *       B   C
 *      / \   \
 *     D   E   F
 *
 * Output: F (it is the last node at the bottom level)
 *
 * Input: Pointer to root of tree
 * Output: Pointer to deepest node
 *
 * Edge Cases:
 * - Empty tree → return nullptr
 * - Single node tree → root is the deepest
 *
 * Core Insight:
 * - Use **level-order traversal (BFS)**. The **last node dequeued** from the queue
 *   will be the deepest node in the tree.
 *
 * Intuition:
 * - BFS explores all nodes level by level. The last node it visits must be
 *   the bottommost rightmost one, due to left-to-right traversal order.
 * - No need to track depth manually.
 *
 * Trick to Remember:
 * - Deepest = last node seen in BFS traversal
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * Use DFS to track depth:
 * - Traverse all nodes using recursion
 * - Maintain current depth, and update a pointer if a deeper node is found
 *
 * Time: O(n)
 * Space: O(h) due to recursion
 * Weakness: requires depth management and manual state tracking
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * Use BFS (queue):
 * - Traverse each level
 * - Keep a pointer to the last dequeued node — this will be the deepest node
 *
 * Time: O(n) — every node is visited once
 * Space: O(n) — at most one level of nodes in the queue
 *
 * Comparison:
 * | Approach | Time | Space | Notes                        |
 * |----------|------|-------|------------------------------|
 * | DFS      | O(n) | O(h)  | Needs depth tracking         |
 * | BFS      | O(n) | O(n)  | Cleaner and simpler tracking |
 *
 * -----------------------------------------------------------------------------
 * 4. Algorithm and Complexity Analysis:
 * -----------------------------------------------------------------------------
 * Algorithm:
 * - Initialize queue with root
 * - While queue is not empty:
 *     - Dequeue a node, call it current
 *     - Enqueue left child if it exists
 *     - Enqueue right child if it exists
 * - Return last dequeued node (current)
 *
 * Time Complexity: O(n), where n = number of nodes
 * Space Complexity: O(n), worst-case queue size (last level fully populated)
 *
 * -----------------------------------------------------------------------------
 * 5. Step-by-Step Walk-through:
 * -----------------------------------------------------------------------------
 * Tree: A → B,C → D,E,F
 * Queue evolves as:
 * [A] → [B,C] → [C,D,E] → [D,E,F] → [E,F] → [F] → []
 * Last node dequeued = F → deepest node
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
     // Build tree:
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
     if (result) cout << "Deepest node: " << result->val << endl;
     else cout << "Tree is empty." << endl;
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 7. Revision Notes:
  * -----------------------------------------------------------------------------
  * - Use level-order traversal (BFS)
  * - Track the last node visited — that is the deepest
  * - Time: O(n), Space: O(n)
  * - No need to track depth manually
  * - Works for skewed and balanced trees alike
  */
 