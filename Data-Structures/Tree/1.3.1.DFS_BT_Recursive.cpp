/**
 * Problem: Implement DFS (Depth First Search) recursive traversal on a binary tree
 * for all three orders: Preorder, Inorder, Postorder.
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Goal:
 * Traverse a binary tree recursively using:
 * - Preorder (Root → Left → Right)
 * - Inorder (Left → Root → Right)
 * - Postorder (Left → Right → Root)
 *
 * Conceptual Tree:
 *         A
 *        / \
 *       B   C
 *      / \   \
 *     D   E   F
 *
 * Expected Traversals:
 * - Preorder:  A B D E C F
 * - Inorder:   D B E A C F
 * - Postorder: D E B F C A
 *
 * Intuition:
 * - DFS means exploring a branch fully before backtracking.
 * - Recursive calls use the system call stack to simulate depth-first traversal.
 * - The order of calls determines the traversal order.
 *
 * Memory Tip:
 * - Pre = Print early (first)
 * - In = Print in-between left and right
 * - Post = Print after children
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * Recursive traversal is the brute force and the optimal method for DFS.
 * Each function simply applies recursion based on the traversal rule.
 *
 * Time: O(n) — every node is visited once
 * Space: O(h) — h is height of tree (due to call stack)
 *
 * Limitations:
 * - Stack overflow on very deep/skewed trees
 * - No explicit control over traversal stack
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * This is already optimal in terms of code clarity and performance.
 * Use iterative versions (with explicit stack) for deep trees to prevent overflow.
 *
 * -----------------------------------------------------------------------------
 * 4. Walk-through:
 * -----------------------------------------------------------------------------
 * Example Tree:
 *         A
 *        / \
 *       B   C
 *      / \   \
 *     D   E   F
 *
 * Preorder:
 * Visit A → Visit B → Visit D → Visit E → Visit C → Visit F
 *
 * Inorder:
 * Go Left from A to B to D → Visit D → Back to B → Visit B → Visit E → Back to A
 * → Visit A → Visit C → Visit F
 *
 * Postorder:
 * Go all the way left, visit leaves, then root
 *
 * -----------------------------------------------------------------------------
 * 5. C++23 Implementation:
 */

 #include <iostream>
 #include <vector>
 using namespace std;
 
 struct TreeNode {
     char val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
 };
 
 class DFSRecursive {
 public:
     vector<char> preorder(TreeNode* root) {
         vector<char> result;
         preorderHelper(root, result);
         return result;
     }
 
     vector<char> inorder(TreeNode* root) {
         vector<char> result;
         inorderHelper(root, result);
         return result;
     }
 
     vector<char> postorder(TreeNode* root) {
         vector<char> result;
         postorderHelper(root, result);
         return result;
     }
 
 private:
     void preorderHelper(TreeNode* node, vector<char>& result) {
         if (node == nullptr) return;
         result.push_back(node->val);
         preorderHelper(node->left, result);
         preorderHelper(node->right, result);
     }
 
     void inorderHelper(TreeNode* node, vector<char>& result) {
         if (node == nullptr) return;
         inorderHelper(node->left, result);
         result.push_back(node->val);
         inorderHelper(node->right, result);
     }
 
     void postorderHelper(TreeNode* node, vector<char>& result) {
         if (node == nullptr) return;
         postorderHelper(node->left, result);
         postorderHelper(node->right, result);
         result.push_back(node->val);
     }
 };
 
 void print(const string& label, const vector<char>& data) {
     cout << label << ": ";
     for (char ch : data) cout << ch << " ";
     cout << endl;
 }
 
 int main() {
     // Build tree:
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
 
     DFSRecursive solver;
     print("Preorder", solver.preorder(root));
     print("Inorder", solver.inorder(root));
     print("Postorder", solver.postorder(root));
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 6. Canvas Revision Notes:
  * -----------------------------------------------------------------------------
  * - Preorder: Root → Left → Right
  * - Inorder:  Left → Root → Right
  * - Postorder: Left → Right → Root
  * - Recursive traversal uses call stack implicitly.
  * - Time = O(n), Space = O(h)
  *
  * Tip: If interview asks "write recursive DFS", always clarify which order.
  */