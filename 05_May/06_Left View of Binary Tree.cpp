/*
 * GfG Link: https://www.geeksforgeeks.org/problems/left-view-of-binary-tree/1
 *
 * Left View of Binary Tree
 *
 * Difficulty: Easy Accuracy: 33.74% Submissions: 551K+ Points: 2 Average Time: 20m
 *
 * You are given the root of a binary tree. Your task is to return the left view of the binary tree. The left view of a binary tree is the set of nodes visible when the tree is viewed from the left side.
 * If the tree is empty, return an empty list.
 *
 * Examples :
 *
 * Input: root[] = [1, 2, 3, 4, 5, N, N]
 * Output: [1, 2, 4]
 * Explanation: From the left side of the tree, only the nodes 1, 2, and 4 are visible.
 *
 * Input: root[] = [1, 2, 3, N, N, 4, N, N, 5, N, N]
 * Output: [1, 2, 4, 5]
 * Explanation: From the left side of the tree, the nodes 1, 2, 4, and 5 are visible.
 *
 * Input: root[] = [N]
 * Output: []
 *
 * Constraints:
 * 0 <= number of nodes <= 10^6
 * 0 <= node -> data <= 10^5
 */

/************************************************************ C++ ************************************************/

// Intuition 1:
// Imagine you're standing on the left side of the tree and looking at it.
// At every depth level, the first node you see is part of the left view.
// By performing a DFS traversal and always visiting the left subtree first,
// we ensure that the first node visited at each level is the leftmost node.
// We record this node the first time we reach a new level (i.e., when currentLevel > maxLevel).

/* A binary tree node
 *
 * struct Node
 * {
 *  int data;
 *  struct Node* left;
 *  struct Node* right;
 *
 *  Node(int x){
 *      data = x;
 *      left = right = NULL;
 *  }
 * };
 */

// Approach 1 (DFS): Recursively traverse the tree using DFS, tracking the first node seen at each depth level by always visiting the left subtree first.
// Time Complexity: O(n), where n is the number of nodes in the tree, since each node is visited once.
// Space Complexity: O(n), due to recursion stack in the worst case (skewed tree) and space used by the result vector.
class Solution {
public:
    // Helper function to perform DFS and track left view nodes
    void DFS(Node* root, int currentLevel, int& maxLevel, vector<int>& result) {
        if (!root) {
            return;          // Base case: if current node is NULL, return
        }
        // If visiting this level for the first time, add node's data to result
        if (currentLevel > maxLevel) {
            result.push_back(root->data);   // This is the leftmost node at this level
            maxLevel = currentLevel;        // Update maxLevel seen so far
        }

        // Recurse for left subtree first to ensure left view priority
        DFS(root->left, currentLevel + 1, maxLevel, result);

        // Then recurse for right subtree
        DFS(root->right, currentLevel + 1, maxLevel, result);
    }
    // Main function to get left view of binary tree
    vector<int> leftView(Node* root) {
        vector<int> result;             // Vector to store the left view
        int         maxLevel = -1;      // Tracks the maximum level visited so far

        DFS(root, 0, maxLevel, result); // Start DFS from root at level 0
        return result;                  // Return the final left view
    }
};

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 * Tree Structure:
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 * Step-by-step DFS:
 * - Start at root (1), currentLevel = 0, maxLevel = -1 → Add 1 to result → maxLevel = 0
 * - Go left to node (2), currentLevel = 1 > maxLevel = 0 → Add 2 to result → maxLevel = 1
 * - Go left to node (4), currentLevel = 2 > maxLevel = 1 → Add 4 to result → maxLevel = 2
 * - Node (4) has no children → Backtrack
 * - Check right child of (2) → node (5), currentLevel = 2 = maxLevel → Not added
 * - Go back to node (1), visit right child (3), currentLevel = 1 = maxLevel → Not added
 * - Final result = [1, 2, 4]
 *
 */

// Intuition 2:
// The left view includes the first node from each level in a binary tree.
// Using level order traversal (BFS), we can easily identify the first node at each level (i.e., the first node dequeued at that level).
// We maintain a queue for BFS and store the first node of every level into the result.

/* A binary tree node
 *
 * struct Node
 * {
 *  int data;
 *  struct Node* left;
 *  struct Node* right;
 *
 *  Node(int x){
 *      data = x;
 *      left = right = NULL;
 *  }
 * };
 */

// Approach 2 (BFS): Use BFS to process the tree level by level, and at each level, add the first node to the result vector.
// Time Complexity: O(n), where n is the number of nodes. Each node is visited once.
// Space Complexity: O(n), for the queue used in level order traversal and the result vector.
class Solution {
public:
    vector<int> leftView(Node* root) {
        vector<int> result;   // Stores the left view nodes

        if (root == nullptr) {
            return result;                    // Handle empty tree
        }
        // Queue for level order traversal
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            // Number of nodes at current level
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();   // Get the front node
                q.pop();

                // If it's the first node of the current level, add to result
                if (i == 0) {
                    result.push_back(curr->data);
                }

                // Enqueue left child if exists
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }

                // Enqueue right child if exists
                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }
        }

        return result;   // Return the final left view
    }
};

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 * Tree Structure:
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 * BFS Steps:
 * - Level 0: Queue = [1], i = 0 → Add 1 → Enqueue 2 and 3
 * - Level 1: Queue = [2, 3], i = 0 → Add 2 → Enqueue 4 and 5
 * - Level 2: Queue = [4, 5], i = 0 → Add 4 → No more children to enqueue
 * Final Result: [1, 2, 4]
 *
 */

/************************************************************ JAVA ************************************************/

// Intuition 1:
// Think of viewing the binary tree from the left side.
// At every level, the first node encountered from the left is visible.
// By using DFS and visiting the left subtree before the right, we ensure that the leftmost node is processed first at each level.
// We keep track of the maximum level visited so far, and only add a node to the result if we are visiting a new level.

/* A Binary Tree node
 *
 * class Node
 * {
 *  int data;
 *  Node left, right;
 *
 *  Node(int item)
 *  {
 *      data = item;
 *      left = right = null;
 *  }
 * }*/

// Approach 1 (DFS): Perform a DFS traversal, always visiting the left subtree before the right. For each level, record the first node encountered.
// Time Complexity: O(n), where n is the number of nodes in the binary tree. Each node is visited once.
// Space Complexity: O(n), due to the recursion stack in worst-case and the list used to store the left view.
class Solution {
    // Helper method for DFS
    void DFS(Node node, int level, int[] maxLevel, ArrayList<Integer> result) {
        if (node == null) {
            return;               // Base case
        }
        // If this level is visited for the first time
        if (level > maxLevel[0]) {
            result.add(node.data);    // Add current node to result
            maxLevel[0] = level;      // Update max level reached
        }

        // Visit left subtree first to ensure left view
        DFS(node.left, level + 1, maxLevel, result);
        // Visit right subtree
        DFS(node.right, level + 1, maxLevel, result);
    }
    // Main function to return list containing elements of left view
    ArrayList<Integer> leftView(Node root) {
        ArrayList<Integer> result = new ArrayList<>();
        int[] maxLevel = new int[1];    // Using array to pass maxLevel by reference

        maxLevel[0] = -1;               // Initialize to -1 so root at level 0 gets included
        DFS(root, 0, maxLevel, result); // Start DFS from root at level 0
        return result;                  // Return the final result
    }
}

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 * Tree Structure:
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 * DFS Trace:
 * - Start at root (1), level 0 > maxLevel -1 → Add 1 → maxLevel = 0
 * - Go left to node (2), level 1 > maxLevel 0 → Add 2 → maxLevel = 1
 * - Go left to node (4), level 2 > maxLevel 1 → Add 4 → maxLevel = 2
 * - Node (4) has no children → return
 * - Visit right of (2) → node (5), level 2 == maxLevel → Not added
 * - Backtrack to root and visit right (3), level 1 == maxLevel → Not added
 * - Final left view: [1, 2, 4]
 *
 */

// Intuition 2:
// The left view of a binary tree consists of the first node at each level when viewed from the left.
// Using level order traversal (BFS), we can easily capture the first node at every level.

/* A Binary Tree node
 *
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  Node(int item) {
 *      data = item;
 *      left = right = null;
 *  }
 * }
 */

// Approach 2 (BFS): Perform level order traversal using a queue and capture the first node of each level.
// Time Complexity: O(n), where n is the total number of nodes in the tree.
// Space Complexity: O(n), for the queue used in level-order traversal and the result list.
class Solution {
    // Function to return list containing elements of left view of binary tree.
    ArrayList<Integer> leftView(Node root) {
        ArrayList<Integer> result = new ArrayList<>();

        if (root == null) {
            return result;               // Handle empty tree
        }
        Queue<Node> queue = new LinkedList<>();
        queue.offer(root); // Start BFS with root

        while (!queue.isEmpty()) {
            int levelSize = queue.size(); // Number of nodes at current level

            for (int i = 0; i < levelSize; i++) {
                Node curr = queue.poll(); // Dequeue current node

                // Add the first node of the current level to the result
                if (i == 0) {
                    result.add(curr.data);
                }

                // Enqueue left child
                if (curr.left != null) {
                    queue.offer(curr.left);
                }

                // Enqueue right child
                if (curr.right != null) {
                    queue.offer(curr.right);
                }
            }
        }

        return result; // Return the left view
    }
}

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 * Tree Structure:
 *         1
 *        / \
 *       2   3
 *      / \
 *     4   5
 *
 * BFS Steps:
 * - Level 0: Queue = [1], i = 0 → Add 1 → Enqueue 2, 3
 * - Level 1: Queue = [2, 3], i = 0 → Add 2 → Enqueue 4, 5
 * - Level 2: Queue = [4, 5], i = 0 → Add 4 → No children to enqueue
 * Final Result: [1, 2, 4]
 *
 */
