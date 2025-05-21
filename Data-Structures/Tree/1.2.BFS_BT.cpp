/**
 * Problem: Perform BFS (Level Order) traversal on a binary tree using different approaches.
 * Language: C++23
 *
 * -----------------------------------------------------------------------------
 * 1. Understanding and Visualization:
 * -----------------------------------------------------------------------------
 * Problem Statement:
 * Given a binary tree, perform BFS traversal using:
 * - Standard level order (left to right)
 * - Level-wise grouping (vector<vector<char>>)
 * - Zigzag level order traversal
 *
 * Example Tree:
 *           A
 *         /   \
 *        B     C
 *       / \     \
 *      D   E     F
 *
 * Standard BFS: A B C D E F
 * Level-wise: [[A], [B, C], [D, E, F]]
 * Zigzag: [[A], [C, B], [D, E, F]]
 *
 * Key Concepts:
 * - BFS uses a queue to process nodes level by level.
 * - For level-wise, we track number of nodes per level.
 * - For zigzag, alternate insertion direction using flag.
 *
 * Memory Aid:
 * - Queue = FIFO → perfect for "level by level"
 * - Use null marker or size-based boundary for levels
 * - Zigzag = Flip flag every level (left-right ↔ right-left)
 *
 * -----------------------------------------------------------------------------
 * 2. Brute Force Approach:
 * -----------------------------------------------------------------------------
 * Standard BFS using queue (no levels tracked).
 * Time: O(n)
 * Space: O(n)
 *
 * Weakness: Can’t access values level-wise or zigzag order.
 *
 * -----------------------------------------------------------------------------
 * 3. Optimization:
 * -----------------------------------------------------------------------------
 * - Track level size at each iteration for level-wise grouping
 * - Use deque for zigzag to insert from front or back
 * Time: O(n), Space: O(n)
 *
 * -----------------------------------------------------------------------------
 * 4. Walk-through: Zigzag
 * -----------------------------------------------------------------------------
 * Use a queue and a boolean flag. Traverse each level:
 * - If flag is true, insert left to right
 * - Else, insert right to left
 * Flip flag after each level.
 *
 * -----------------------------------------------------------------------------
 * 5. C++23 Implementation:
 */

 #include <iostream>
 #include <vector>
 #include <queue>
 #include <deque>
 using namespace std;
 
 struct TreeNode {
     char val;
     TreeNode* left;
     TreeNode* right;
     TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
 };
 
 class BFSVariants {
 public:
     vector<char> simpleBFS(TreeNode* root) {
         vector<char> result;
         if (root == nullptr) return result;
 
         queue<TreeNode*> q;
         q.push(root);
 
         while (!q.empty()) {
             TreeNode* node = q.front(); q.pop();
             result.push_back(node->val);
             if (node->left) q.push(node->left);
             if (node->right) q.push(node->right);
         }
         return result;
     }
 
     vector<vector<char>> levelOrder(TreeNode* root) {
         vector<vector<char>> result;
         if (root == nullptr) return result;
 
         queue<TreeNode*> q;
         q.push(root);
 
         while (!q.empty()) {
             int size = q.size();
             vector<char> level;
             for (int i = 0; i < size; ++i) {
                 TreeNode* node = q.front(); q.pop();
                 level.push_back(node->val);
                 if (node->left) q.push(node->left);
                 if (node->right) q.push(node->right);
             }
             result.push_back(level);
         }
         return result;
     }
 
     vector<vector<char>> zigzagLevelOrder(TreeNode* root) {
         vector<vector<char>> result;
         if (root == nullptr) return result;
 
         queue<TreeNode*> q;
         q.push(root);
         bool leftToRight = true;
 
         while (!q.empty()) {
             int size = q.size();
             deque<char> level;
 
             for (int i = 0; i < size; ++i) {
                 TreeNode* node = q.front(); q.pop();
                 if (leftToRight) level.push_back(node->val);
                 else level.push_front(node->val);
 
                 if (node->left) q.push(node->left);
                 if (node->right) q.push(node->right);
             }
             result.push_back(vector<char>(level.begin(), level.end()));
             leftToRight = !leftToRight;
         }
         return result;
     }
 };
 
 void print(const string& label, const vector<char>& data) {
     cout << label << ": ";
     for (char val : data) cout << val << " ";
     cout << endl;
 }
 
 void printLevels(const string& label, const vector<vector<char>>& levels) {
     cout << label << ":\n";
     for (const auto& level : levels) {
         for (char val : level) cout << val << " ";
         cout << endl;
     }
 }
 
 int main() {
     TreeNode* root = new TreeNode('A');
     root->left = new TreeNode('B');
     root->right = new TreeNode('C');
     root->left->left = new TreeNode('D');
     root->left->right = new TreeNode('E');
     root->right->right = new TreeNode('F');
 
     BFSVariants solver;
 
     print("Simple BFS", solver.simpleBFS(root));
     printLevels("Level Order BFS", solver.levelOrder(root));
     printLevels("Zigzag Level Order BFS", solver.zigzagLevelOrder(root));
 
     return 0;
 }
 
 /**
  * -----------------------------------------------------------------------------
  * 6. Canvas Revision Notes:
  * -----------------------------------------------------------------------------
  * - Use queue for level order traversal
  * - Use size-tracking for level-wise grouping
  * - Use deque and toggle direction for zigzag
  * - Time: O(n), Space: O(n) for all methods
  * - Zigzag = reversed logic every level → push_front vs push_back
  */
 