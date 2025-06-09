/*
 * GfG Link: https://www.geeksforgeeks.org/problems/check-whether-bst-contains-dead-end/1
 *
 * BST with Dead End
 *
 * Difficulty: Medium Accuracy: 35.99% Submissions: 85K+ Points: 4
 *
 * You are given a Binary Search Tree (BST) containing unique positive integers greater than 0.
 * Your task is to determine whether the BST contains a dead end.
 * Note: A dead end is a leaf node in the BST such that no new node can be inserted in the BST at or below this node while maintaining the BST property and the constraint that all node values must be > 0.
 *
 * Examples:
 * Input: root[] = [8, 5, 9, 2, 7, N, N, 1]
 * Output: true
 * Explanation: Node 1 is a Dead End in the given BST.
 *
 * Input: root[] = [8, 7, 10, 2, N, 9, 13]
 * Output: true
 * Explanation: Node 9 is a Dead End in the given BST.
 *
 * Constraints:
 * 1 <= number of nodes <= 3000
 * 1 <= node->data <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Perform DFS traversal and keep track of the min and max bounds where a node can be placed. At each leaf, if (max - min == 2) and root->data is exactly in the middle, it's a dead end (i.e., root->data - min == 1 and max - root->data == 1).
// Time Complexity: O(N), where N is the number of nodes in the BST. Each node is visited once.
// Space Complexity: O(H), where H is the height of the BST (O(log N) for balanced, O(N) for skewed) due to recursive call stack.
class Solution {
public:

    // Helper DFS function to detect dead ends in BST
    bool dfs(Node* root, int min, int max) {
        if (!root) {
            return 0; // base case: empty subtree cannot have dead end
        }

        // if it's a leaf node
        if (!root->left && !root->right) {
            // check if no number can be inserted at or below this leaf
            if (root->data - min == 1 && max - root->data == 1) {
                return 1; // dead end found
            } else {
                return 0; // not a dead end
            }
        }

        // recursively check in left and right subtrees
        return dfs(root->left, min, root->data) ||
               dfs(root->right, root->data, max);
    }

    bool isDeadEnd(Node* root) {
        // Start with min = 0 and max = INT_MAX for root
        return dfs(root, 0, INT_MAX);
    }
};

/*
 *
 * Dry Run
 *
 * Input: root[] = [8, 5, 9, 2, 7, N, N, 1]
 *
 * BST structure:
 *          8
 *        /   \
 *      5      9
 *    /   \
 *   2     7
 *  /
 * 1
 *
 * We call dfs(root=8, min=0, max=INT_MAX)
 * -> dfs(5, 0, 8)
 * -> dfs(2, 0, 5)
 *    -> dfs(1, 0, 2)
 *       - It's a leaf node
 *       - root->data = 1, min = 0, max = 2
 *       - 1 - 0 == 1 && 2 - 1 == 1 => TRUE => Dead End at node 1
 *    => returns true
 * => returns true
 * => returns true
 *
 * Final result: true (dead end exists)
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Perform DFS traversal and keep track of the min and max bounds where a node can be placed. At each leaf, if (max - min == 2) and root.data is exactly in the middle, it's a dead end (i.e., root.data - min == 1 and max - root.data == 1).
// Time Complexity: O(N), where N is the number of nodes in the BST. Each node is visited once.
// Space Complexity: O(H), where H is the height of the BST (O(log N) for balanced, O(N) for skewed) due to recursive call stack.
class Solution {
    // Helper DFS function to detect dead ends in BST
    private boolean dfs(Node root, int min, int max) {
        if (root == null) {
            return false; // base case: empty subtree cannot have dead end
        }

        // if it's a leaf node
        if (root.left == null && root.right == null) {
            // check if no number can be inserted at or below this leaf
            if (root.data - min == 1 && max - root.data == 1) {
                return true;  // dead end found
            } else {
                return false; // not a dead end
            }
        }

        // recursively check in left and right subtrees
        return dfs(root.left, min, root.data) ||
               dfs(root.right, root.data, max);
    }
    
    public boolean isDeadEnd(Node root) {
        // Start with min = 0 and max = Integer.MAX_VALUE for root
        return dfs(root, 0, Integer.MAX_VALUE);
    }
}

/*
 *
 * Dry Run
 *
 * Input: root[] = [8, 5, 9, 2, 7, N, N, 1]
 *
 * BST structure:
 *          8
 *        /   \
 *      5      9
 *    /   \
 *   2     7
 *  /
 * 1
 *
 * We call dfs(root=8, min=0, max=Integer.MAX_VALUE)
 * -> dfs(5, 0, 8)
 * -> dfs(2, 0, 5)
 *    -> dfs(1, 0, 2)
 *       - It's a leaf node
 *       - root.data = 1, min = 0, max = 2
 *       - 1 - 0 == 1 && 2 - 1 == 1 => TRUE => Dead End at node 1
 *    => returns true
 * => returns true
 * => returns true
 *
 * Final result: true (dead end exists)
 *
 */
