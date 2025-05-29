/*
 * GfG Link: https://www.geeksforgeeks.org/problems/closest-neighbor-in-bst/1
 *
 * Closest Neighbour in BST
 *
 * Difficulty: Easy Accuracy: 36.98% Submissions: 50K+ Points: 2
 *
 * Given the root of a binary search tree and a number k, find the greatest number in the binary search tree that is less than or equal to k.
 *
 * Examples:
 *
 * Input: root = [10, 7, 15, 2, 8, 11, 16], k = 14
 * Output: 11
 * Explanation: The greatest element in the tree which is less than or equal to 14, is 11.
 *
 * Input: root = [5, 2, 12, 1, 3, 9, 21, N, N, N, N, N, N, 19, 25], k = 24
 * Output: 21
 * Explanation: The greatest element in the tree which is less than or equal to 24, is 21.
 *
 * Input: root = [5, 2, 12, 1, 3, 9, 21, N, N, N, N, N, N, 19, 25], k = 4
 * Output: 3
 * Explanation: The greatest element in the tree which is less than or equal to 4, is 3.
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 1 <= node->data, k <= 10^5
 * All nodes are unique in the BST
 */

/************************************************************ C++ ************************************************/

// Approach: Use BST property to move right when node->data <= k and update result. Move left if node->data > k
// Time Complexity: O(h), where h is the height of the BST. For balanced BST, it's O(log N), and for skewed, O(N)
// Space Complexity: O(1), iterative traversal uses constant space

/*
 * class Node {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int x) {
 *      data = x;
 *      left = NULL;
 *      right = NULL;
 *  }
 * };
 */

class Solution {
public:
    int findMaxFork(Node* root, int k) {
        int result = -1;  // Initialize result to -1 assuming no element found <= k

        while (root != NULL) {
            if (root->data <= k) {
                result = root->data;        // Current node is a valid candidate (<= k)
                root   = root->right;       // Try finding a bigger candidate on the right
            } else {
                root = root->left;          // Current node > k, go left to find smaller value
            }
        }

        return result; // Will hold the largest node value ≤ k, or -1 if no such value exists
    }
};

/*
 *
 * Dry Run
 * Input: root = [10, 7, 15, 2, 8, 11, 16], k = 14
 * Tree Structure:
 *         10
 *       /    \
 *      7      15
 *     / \    /  \
 *    2   8  11  16
 *
 * Initialize result = -1
 * Start at root = 10
 * - 10 <= 14 → result = 10 → move to right child (15)
 * - 15 > 14 → move to left child (11)
 * - 11 <= 14 → result = 11 → move to right child (NULL)
 * End traversal. Final result = 11
 *
 * Output: 11
 */

/************************************************************ JAVA ************************************************/

// Approach: Use BST traversal to find the max value ≤ k by moving right when node.data ≤ k and updating result
// Time Complexity: O(h), where h is the height of the tree. For balanced BST it's O(log N), for skewed it's O(N)
// Space Complexity: O(1), iterative solution uses constant space

/*
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  Node(int x) {
 *      data = x;
 *      left = right = null;
 *  }
 * }
 */

class Solution {
    public int findMaxFork(Node root, int k) {
        int result = -1; // Initialize result with -1 in case no value ≤ k is found

        while (root != null) {
            if (root.data <= k) {
                result = root.data;     // Valid candidate, update result
                root   = root.right;    // Try to find a bigger candidate on the right
            } else {
                root = root.left;       // Too big, go left to find smaller value
            }
        }

        return result; // Return the closest value ≤ k
    }
}

/*
 *
 * Dry Run
 * Input: root = [10, 7, 15, 2, 8, 11, 16], k = 14
 * Tree:
 *         10
 *       /    \
 *      7      15
 *     / \    /  \
 *    2   8  11  16
 *
 * result = -1
 * root = 10 → 10 ≤ 14 → result = 10 → go right (15)
 * root = 15 → 15 > 14 → go left (11)
 * root = 11 → 11 ≤ 14 → result = 11 → go right (null)
 * End loop → return result = 11
 *
 * Output: 11
 */
