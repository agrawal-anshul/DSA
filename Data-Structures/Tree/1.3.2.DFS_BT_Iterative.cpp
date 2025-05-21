/**
 * Problem: Perform iterative DFS traversal on a binary tree (Preorder, Inorder, Postorder).
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Problem Statement:
 * Given a binary tree, traverse it in Preorder, Inorder, and Postorder **using iterative methods only**.
 *
 * Example Tree:
 *          A
 *        /   \
 *       B     C
 *      / \     \
 *     D   E     F
 *
 * Expected Traversals:
 * Preorder:  A B D E C F
 * Inorder:   D B E A C F
 * Postorder: D E B F C A
 *
 * Key Observations:
 * - Preorder: Visit root first, then left subtree, then right subtree.
 * - Inorder: Visit left subtree, then root, then right subtree.
 * - Postorder: Visit left subtree, then right subtree, then root.
 *
 * Intuition:
 * - DFS is inherently stack-based (recursion uses call stack internally).
 * - We use an explicit stack to simulate recursion.
 *
 * Preorder (Root → Left → Right):
 * - Use one stack. Push right child first, then left child.
 *
 * Inorder (Left → Root → Right):
 * - Traverse left fully, then visit root, then right.
 * - Use a stack to remember nodes as we traverse.
 *
 * Postorder (Left → Right → Root):
 * Option 1: Use **two stacks**:
 *   - First stack: modified preorder (Root → Right → Left)
 *   - Second stack: reverse of first gives postorder
 * Option 2: Use **one stack** and a pointer to track last visited node.
 *
 * Memory Trick:
 * - Pre = Root early
 * - In = Root in-between
 * - Post = Root last
 * - Postorder with 2 stacks = Reverse of modified preorder
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * Use recursion for all three traversals.
 * Time: O(n), Space: O(h) — where h = height of tree.
 * Weaknesses:
 * - Stack overflow for deep trees
 * - No explicit control over traversal
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * Use stacks to simulate recursion:
 * - Preorder: one stack
 * - Inorder: one stack with current pointer
 * - Postorder: either one or two stacks
 * Time: O(n)
 * Space: O(n)
 *
 * -----------------------------------------------------------------------------
 * 4. Walk-through: Postorder with 2 stacks
 * -----------------------------------------------------------------------------
 * First stack simulates preorder in reverse: Root → Right → Left
 * Second stack stores nodes in final postorder order
 * Example:
 * Stack1: A → C → F → B → E → D
 * Stack2: D → E → B → F → C → A
 *
 * -----------------------------------------------------------------------------
 * 5. C++23 Implementation:
 */

 #include <iostream>
 #include <vector>
 #include <stack>
 using namespace std;
 
 struct TreeNode {
     char val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
 };
 
 class DFSIterative {
 public:
     vector<char> preorder(TreeNode* root) {
         vector<char> result;
         if (root == nullptr) return result;
 
         stack<TreeNode*> stk;
         stk.push(root);
 
         while (!stk.empty()) {
             TreeNode* node = stk.top(); stk.pop();
             result.push_back(node->val);
 
             if (node->right) stk.push(node->right);
             if (node->left) stk.push(node->left);
         }
         return result;
     }
 
     vector<char> inorder(TreeNode* root) {
         vector<char> result;
         stack<TreeNode*> stk;
         TreeNode* curr = root;
 
         while (curr or !stk.empty()) {
             while (curr) {
                 stk.push(curr);
                 curr = curr->left;
             }
             curr = stk.top(); stk.pop();
             result.push_back(curr->val);
             curr = curr->right;
         }
         return result;
     }
 
     vector<char> postorderTwoStacks(TreeNode* root) {
         vector<char> result;
         if (root == nullptr) return result;
 
         stack<TreeNode*> stk1, stk2;
         stk1.push(root);
 
         while (!stk1.empty()) {
             TreeNode* node = stk1.top(); stk1.pop();
             stk2.push(node);
 
             if (node->left) stk1.push(node->left);
             if (node->right) stk1.push(node->right);
         }
 
         while (!stk2.empty()) {
             result.push_back(stk2.top()->val);
             stk2.pop();
         }
         return result;
     }
 
     vector<char> postorderSingleStack(TreeNode* root) {
         vector<char> result;
         stack<TreeNode*> stk;
         TreeNode* curr = root;
         TreeNode* lastVisited = nullptr;
 
         while (curr or !stk.empty()) {
             if (curr) {
                 stk.push(curr);
                 curr = curr->left;
             } else {
                 TreeNode* node = stk.top();
                 if (node->right and lastVisited != node->right) {
                     curr = node->right;
                 } else {
                     result.push_back(node->val);
                     lastVisited = node;
                     stk.pop();
                 }
             }
         }
         return result;
     }
 };
 
 void print(const string& label, const vector<char>& res) {
     cout << label << ": ";
     for (char c : res) cout << c << " ";
     cout << endl;
 }
 
 int main() {
     // Build tree:       A
     //                 /   \
     //                B     C
     //               / \     \
     //              D   E     F
 
     TreeNode* root = new TreeNode('A');
     root->left = new TreeNode('B');
     root->right = new TreeNode('C');
     root->left->left = new TreeNode('D');
     root->left->right = new TreeNode('E');
     root->right->right = new TreeNode('F');
 
     DFSIterative solver;
     print("Preorder", solver.preorder(root));
     print("Inorder", solver.inorder(root));
     print("Postorder (2 stacks)", solver.postorderTwoStacks(root));
     print("Postorder (1 stack)", solver.postorderSingleStack(root));
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 6. Canvas Revision Notes:
  * -----------------------------------------------------------------------------
  * - Preorder: push right then left
  * - Inorder: simulate recursion using stack and pointer
  * - Postorder:
  *     - 2-stack is easiest: reversed modified preorder
  *     - 1-stack is interview favorite: track last visited node
  * - Time: O(n) for all
  * - Space: O(n) worst case
  *
  * Remember:
  * - Postorder(2-stack) = reverse of Root → Right → Left
  */
 