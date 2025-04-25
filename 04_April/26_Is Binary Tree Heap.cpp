/*
 * Is Binary Tree Heap
 *
 * Difficulty: Medium Accuracy: 34.41% Submissions: 115K+ Points: 4
 *
 * You are given a binary tree, and the task is to determine whether it satisfies the properties of a max-heap.
 * A binary tree is considered a max-heap if it satisfies the following conditions:
 * Completeness: Every level of the tree, except possibly the last, is completely filled, and all nodes are as far left as possible.
 * Max-Heap Property: The value of each node is greater than or equal to the values of its children.
 *
 * Examples:
 *
 * Input: root[] = [97, 46, 37, 12, 3, 7, 31, 6, 9]
 * Output: true
 * Explanation: The tree is complete and satisfies the max-heap property.
 * Input: root[] = [97, 46, 37, 12, 3, 7, 31, N, 2, 4]
 * Output: false
 * Explanation: The tree is not complete and does not follow the Max-Heap Property, hence it is not a max-heap.
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^3
 * 1 ≤ node->data ≤ 10^3
 */

/************************************************************ C++ ************************************************/

/*
 *
 * Intuition:
 *
 * To determine if a binary tree is a max-heap, we must ensure two conditions:
 *
 * 1. **Complete Binary Tree (CBT)**:
 *    - All levels of the tree must be fully filled except possibly the last level.
 *    - Nodes at the last level must be as far left as possible.
 *    - We can simulate array indexing and validate that no node has an index >= total node count.
 *
 * 2. **Max-Heap Property**:
 *    - Every parent node must have a value greater than or equal to its children.
 *    - This ensures the largest value is always at the top, and the structure follows heap rules.
 *
 * 🔍 Example:
 * Input Tree (Array Form): [10, 9, 8, 7, 6, 5, 4]
 * Corresponding Tree Structure:
 *         10
 *        /  \
 *      9     8
 *     / \   / \
 *    7   6 5   4
 *
 * ✔ Check Completeness:
 *    - Number of nodes = 7
 *    - Indexes assigned while traversing:
 *      10 at index 0
 *      9 at index 1, 8 at index 2
 *      7 at index 3, 6 at index 4, 5 at index 5, 4 at index 6
 *    - All indices < 7 → Complete ✅
 *
 * ✔ Check Max-Heap Property:
 *    - 10 ≥ 9 and 8 ✅
 *    - 9 ≥ 7 and 6 ✅
 *    - 8 ≥ 5 and 4 ✅
 *    - All leaf nodes are valid
 *    - All nodes follow max-heap condition ✅
 *
 * ✅ Therefore, the tree is a max-heap.
 *
 * ❌ If even one node has a value less than its child OR
 * ❌ If any index exceeds node count during traversal,
 * ➡ the tree is not a max-heap.
 *
 */

// Approach: Check if the binary tree is complete using index-based validation and then verify if it follows the max-heap property recursively.
// Time Complexity: O(n) — Every node is visited once for completeness and once for heap check.
// Space Complexity: O(h) — Due to recursion stack where h is the height of the tree (O(log n) for balanced tree, O(n) worst case).

// Structure of node
/*class Node {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int val) {
 *      data = val;
 *      left = right = NULL;
 *  }
 * };*/

class Solution {
public:
    // This function counts the total number of nodes in the tree
    int countNodes(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        // Count current node + nodes in left + nodes in right
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    // This function checks whether the tree is complete using the concept of index in array representation
    bool isCompleteUtil(Node* root, int index, int numberOfNodes) {
        if (root == nullptr) {
            return true;
        }

        // If index is greater than or equal to number of nodes, it violates the complete tree condition
        if (index >= numberOfNodes) {
            return false;
        }

        // Recursively check for left and right subtree with calculated indices
        return isCompleteUtil(root->left, 2 * index + 1, numberOfNodes) &&
               isCompleteUtil(root->right, 2 * index + 2, numberOfNodes);
    }
    // This function checks whether the binary tree satisfies the max-heap property
    bool isHeapUtil(Node* root) {
        // If it's a leaf node, it's a valid heap
        if (root->left == nullptr && root->right == nullptr) {
            return true;
        }

        // If the node has only left child (must happen only in the last level of a complete tree)
        if (root->right == nullptr) {
            // Return true only if parent node is greater than left child
            return root->data >= root->left->data;
        } else {
            // If the node has both children, check current node with both children and recurse
            if (root->data >= root->left->data && root->data >= root->right->data) {
                return isHeapUtil(root->left) && isHeapUtil(root->right);
            } else {
                return false;
            }
        }
    }
    // Main function to determine if binary tree is a heap
    bool isHeap(Node* root) {
        // Count total number of nodes
        int nodeCount = countNodes(root);
        int index     = 0;

        // Check both completeness and heap property
        if (isCompleteUtil(root, index, nodeCount) && isHeapUtil(root)) {
            return true;
        }
        return false;
    }
};

/*
 *
 * Dry Run
 *
 * Input Tree: [10, 9, 8, 7, 6, 5, 4]
 * Structure:
 *         10
 *        /  \
 *      9     8
 *     / \   / \
 *    7   6 5   4
 *
 * Step 1: countNodes(root) = 7
 * Step 2: isCompleteUtil(root, 0, 7)
 *         - index 0 < 7 → go left (index 1), right (index 2)
 *         - index 1 < 7 → go left (3), right (4)
 *         - index 2 < 7 → go left (5), right (6)
 *         - indices 3,4,5,6 are all valid and leaf/null → returns true
 *         → Tree is complete ✅
 *
 * Step 3: isHeapUtil(root)
 *         - root = 10; left = 9, right = 8 → 10 ≥ 9 and 10 ≥ 8 ✅
 *         - node = 9; left = 7, right = 6 → 9 ≥ 7 and 9 ≥ 6 ✅
 *         - node = 8; left = 5, right = 4 → 8 ≥ 5 and 8 ≥ 4 ✅
 *         → All nodes satisfy heap property ✅
 *
 * Final Output: true
 *
 */

/************************************************************ JAVA ************************************************/

/*
 *
 * Intuition:
 *
 * To check if a binary tree is a Max-Heap, we validate two key properties:
 *
 * 1. Complete Binary Tree (CBT):
 *    - All levels fully filled except maybe the last.
 *    - Nodes in the last level are as left as possible.
 *    - We simulate array index rules and ensure index < total node count.
 *
 * 2. Max-Heap Property:
 *    - Every parent node should be ≥ its children.
 *    - This keeps the maximum element at the root and satisfies heap conditions.
 *
 * 🔍 Example:
 * Input Tree: [10, 9, 8, 7, 6, 5, 4]
 * Structure:
 *         10
 *        /  \
 *      9     8
 *     / \   / \
 *    7   6 5   4
 *
 * ✅ Check Completeness:
 * - Indexes while traversing:
 *   10 → 0, 9 → 1, 8 → 2, 7 → 3, 6 → 4, 5 → 5, 4 → 6
 * - All indices < totalNodes(7) → Complete ✅
 *
 * ✅ Check Heap Property:
 * - 10 ≥ 9, 10 ≥ 8 → true
 * - 9 ≥ 7, 9 ≥ 6 → true
 * - 8 ≥ 5, 8 ≥ 4 → true
 * - All nodes valid
 *
 * Hence, it's a valid Max-Heap.
 *
 * ❌ If even one node is smaller than its child
 * ❌ Or index ≥ total nodes during traversal
 * → Tree is not a Max-Heap.
 *
 */

// Approach: Check if binary tree is complete using index-based logic and verify max-heap property using recursion.
// Time Complexity: O(n) — each node is visited once for counting, completeness check, and heap validation.
// Space Complexity: O(h) — due to recursion stack where h is the height of the tree.

// Node defined as
/*
 * class Node {
 *  int data;
 *  Node left, right;
 *  Node(int d) {
 *      data = d;
 *      left = right = null;
 *  }
 * }
 */

class Solution {
    // Function to count total number of nodes
    int countNodes(Node root) {
        if (root == null) {
            return 0;
        }
        return 1 + countNodes(root.left) + countNodes(root.right);
    }
    // Function to check if the binary tree is complete
    boolean isComplete(Node root, int index, int nodeCount) {
        if (root == null) {
            return true;
        }

        // If index assigned is more than total nodes → not complete
        if (index >= nodeCount) {
            return false;
        }

        // Recursively check for left and right subtree
        return isComplete(root.left, 2 * index + 1, nodeCount) &&
               isComplete(root.right, 2 * index + 2, nodeCount);
    }
    // Function to verify max-heap property
    boolean isHeapProperty(Node root) {
        // If leaf node → valid heap
        if (root.left == null && root.right == null) {
            return true;
        }

        // Node has only left child (possible only in last level)
        if (root.right == null) {
            return root.data >= root.left.data;
        }

        // Node has both children
        if (root.data >= root.left.data && root.data >= root.right.data) {
            return isHeapProperty(root.left) && isHeapProperty(root.right);
        } else {
            return false;
        }
    }
    // Main function to check if tree is a heap
    boolean isHeap(Node tree) {
        int totalNodes = countNodes(tree);

        return isComplete(tree, 0, totalNodes) && isHeapProperty(tree);
    }
}

/*
 *
 * Dry Run
 *
 * Input: [10, 9, 8, 7, 6, 5, 4]
 * Tree:
 *         10
 *        /  \
 *      9     8
 *     / \   / \
 *    7   6 5   4
 *
 * Step 1: countNodes → 7
 * Step 2: isComplete with index:
 *   - index 0 → node 10
 *   - index 1 → node 9
 *   - index 2 → node 8
 *   - index 3,4,5,6 → all valid leaf nodes
 *   → isComplete returns true ✅
 *
 * Step 3: isHeapProperty
 *   - 10 ≥ 9 and 8 → true
 *   - 9 ≥ 7 and 6 → true
 *   - 8 ≥ 5 and 4 → true
 *   → isHeapProperty returns true ✅
 *
 * Final Output: true
 *
 */
