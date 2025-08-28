/*
Tree Traversals in C++

This program defines a binary tree structure and provides various traversal methods —
both recursive and iterative — for Pre-order, In-order, Post-order, and Level-order.

Intuition:
- Recursive traversals follow a natural tree structure and are concise.
- Iterative versions simulate the call stack with explicit stacks/queues.
- Level-order traversal (BFS) explores tree breadth-wise.
- Recursive level-order can also be done via height computation.

Easy tip: Prefer recursive versions for simplicity; iterative for avoiding stack overflow.
*/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// --- Tree Node Definition ---
struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// ----------------------------
// --- Recursive Traversals ---
// ----------------------------

// Pre-order: Root → Left → Right
void preOrder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// In-order: Left → Root → Right
void inOrder(TreeNode* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// Post-order: Left → Right → Root
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

// Height of tree — used for recursive level-order traversal
int height(TreeNode* node) {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}

// Recursive Level-order: Level by level using height
void printLevel(TreeNode* root, int level) {
    if (root == nullptr) return;
    if (level == 1) {
        cout << root->val << " ";
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelOrderRecursive(TreeNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; ++i) {
        printLevel(root, i);
    }
}

// ---------------------------
// --- Iterative Traversals ---
// ---------------------------

// Pre-order (Root → Left → Right) using stack
void preOrderIterative(TreeNode* root) {
    if (root == nullptr) return;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();

        cout << node->val << " ";

        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }
}

// In-order (Left → Root → Right) using stack
void inOrderIterative(TreeNode* root) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (!stk.empty() or curr != nullptr) {
        if (curr) {
            // Keep going left, one node per iteration
            stk.push(curr);
            curr = curr->left;
        } else {
            if (stk.empty()) break;

            // Backtrack and visit the node
            curr = stk.top(); 
            stk.pop();
            cout << curr->val << " ";

            // Then move right
            curr = curr->right;
        }
    }
}

// Post-order (Left → Right → Root) using two stacks
/*
   Intuition:
   • Reverse the logic of pre-order.
   • Pre-order: Root → Left → Right
   • Post-order: Left → Right → Root
   • Trick:
   • Do Root → Right → Left and reverse the output.
*/
void postOrderIterative(TreeNode* root) {
    if (root == nullptr) return;

    stack<TreeNode*> stk1, stk2;
    stk1.push(root);

    while (!stk1.empty()) {
        TreeNode* node = stk1.top();
        stk1.pop();
        stk2.push(node);           // Store post-order reverse

        if (node->left) stk1.push(node->left);
        if (node->right) stk1.push(node->right);
    }

    while (!stk2.empty()) {
        cout << stk2.top()->val << " ";
        stk2.pop();
    }
}

// Post-order (Left → Right → Root) using one stack
void postOrderIterativeOneStack(TreeNode* root) {
    if (root == nullptr) return;

    stack<TreeNode*> stk;
    TreeNode* curr = root;
    TreeNode* lastVisited = nullptr;

    while (!stk.empty() or curr != nullptr) {
        if (curr) {
            // Go as left as possible
            stk.push(curr);
            curr = curr->left;
        } else {
            TreeNode* peekNode = stk.top();

            // If right child exists and hasn't been processed yet
            if (peekNode->right and lastVisited != peekNode->right) {
                curr = peekNode->right;
            } else {
                // Right child is already processed OR doesn't exist
                cout << peekNode->val << " ";
                lastVisited = peekNode;
                stk.pop();
            }
        }
    }
}

// LEVEL ORDER TRAVERSAL
// LEVEL ORDER TRAVERSAL
// LEVEL ORDER TRAVERSAL


// 1. Level-order (BFS): Uses queue to print level by level
void levelOrder(TreeNode* root) {
    if (root == nullptr) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

// 2. Level-order using nullptr as level marker
vector<vector<int>> levelOrder(TreeNode* root, vector<vector<int>> res) {
    if (root == nullptr) return res;

    queue<TreeNode*> q;
    q.push(root);
    q.push(nullptr); // Level marker

    vector<int> level;

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr == nullptr) {
            // Finished one level
            res.push_back(level);
            level.clear();

            // Only add another nullptr if there's more nodes to process
            if (!q.empty()) {
                q.push(nullptr);
            }
        } else {
            level.push_back(curr->val);

            // Enqueue non-null children
            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }
    }

    return res;
}

// 3. Level order without nullptr marker
vector<vector<int>> levelOrder(TreeNode* root, vector<vector<int>> res) {
    if (root == nullptr) return res;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level
        vector<int> level;

        // Process all nodes in the current level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* curr = q.front();
            q.pop();

            level.push_back(curr->val);

            // Enqueue non-null children
            if (curr->left != nullptr) q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }

        // Add current level to result
        res.push_back(level);
    }

    return res;
}



// ------------------------
// --- Driver Code --------
// ------------------------
int main() {
    /*
         A
        / \
       B   C
      / \   \\
     D   E   F
    */

    TreeNode* root = new TreeNode('A');
    root->left = new TreeNode('B');
    root->right = new TreeNode('C');
    root->left->left = new TreeNode('D');
    root->left->right = new TreeNode('E');
    root->right->right = new TreeNode('F');

    cout << "Pre-order (Recursive): ";
    preOrder(root); cout << "\n";

    cout << "In-order (Recursive): ";
    inOrder(root); cout << "\n";

    cout << "Post-order (Recursive): ";
    postOrder(root); cout << "\n";

    cout << "Level-order (Iterative): ";
    levelOrder(root); cout << "\n";

    cout << "Level-order (Recursive): ";
    levelOrderRecursive(root);cout << "\n";

    cout << "In-order (Iterative): ";
    inOrderIterative(root); cout << "\n";

    cout << "Pre-order (Iterative): ";
    preOrderIterative(root); cout << "\n";

    cout << "Post-order (Iterative 2-stack): ";
    postOrderIterative(root); cout << "\n";

    cout << "Post-order (Iterative 1-stack): ";
    postOrderIterativeOneStack(root); cout << "\n";

    return 0;
}
