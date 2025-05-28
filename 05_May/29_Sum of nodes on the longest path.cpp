/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sum-of-the-longest-bloodline-of-a-tree/1
 *
 * Sum of nodes on the longest path
 *
 * Difficulty: MediumA ccuracy: 52.39% Submissions: 114K+ Points: 4
 *
 * Given a binary tree root[], you need to find the sum of the nodes on the longest path from the root to any leaf node. If two or more paths have the same length, the path with the maximum sum of node values should be considered.
 *
 * Examples:
 *
 * Input: root[] = [4, 2, 5, 7, 1, 2, 3, N, N, 6, N]
 * Output: 13
 * Explanation:
 * The highlighted nodes (4, 2, 1, 6) above are part of the longest root to leaf path having sum = (4 + 2 + 1 + 6) = 13
 *
 * Input: root[] = [1, 2, 3, 4, 5, 6, 7]
 * Output: 11
 * Explanation:
 * The longest root-to-leaf path is 1 -> 3 -> 7, with sum 11.
 * Input: root[] = [10, 5, 15, 3, 7, N, 20, 1]
 * Output: 19
 * Explanation:
 * The longest root-to-leaf path is 10 -> 5 -> 3 -> 1 with a sum of 10 + 5 + 3 + 1 = 19.
 *
 * Constraints:
 * 1 <= number of nodes <= 10^6
 * 0 <= node->data <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS traversal from root to each leaf, keeping track of the current path length and current path sum. At each leaf, update the maxLen and maxSum accordingly.
// Time Complexity: O(N) where N is the number of nodes, since each node is visited once.
// Space Complexity: O(H) where H is the height of the tree, due to the recursion stack.

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
 * }; */

class Solution {
public:

    int maxLen = 0;  // Stores the length of the longest path from root to leaf
    int maxSum = 0;  // Stores the maximum sum along the longest path

    void dfs(Node* node, int currLen, int currSum) {
        if (!node) {
            return;  // Base case: if node is null, just return
        }

        currLen += 1;             // Increment path length
        currSum += node->data;    // Add node value to path sum

        // If it's a leaf node
        if (!node->left && !node->right) {
            // If this path is longer than the previous longest
            if (currLen > maxLen) {
                maxLen = currLen;
                maxSum = currSum;
            }
            // If path length is same but sum is greater
            else if (currLen == maxLen && currSum > maxSum) {
                maxSum = currSum;
            }
            return;
        }

        // Recur for left and right subtree
        dfs(node->left, currLen, currSum);
        dfs(node->right, currLen, currSum);
    }
    
    int sumOfLongRootToLeafPath(Node* root) {
        dfs(root, 0, 0);  // Start DFS with initial length and sum as 0
        return maxSum;    // Return the max sum found
    }
};

/*
 *
 * Dry Run
 * Tree:
 *          1
 *        /   \
 *       2     3
 *      /     / \
 *     4     5   6
 *            \
 *             7
 *
 * Start at root (1)
 * - currLen = 1, currSum = 1
 *
 * Go to left child (2)
 * - currLen = 2, currSum = 3
 *
 * Go to left child (4)
 * - currLen = 3, currSum = 7 -> leaf node
 * - maxLen = 3, maxSum = 7
 *
 * Backtrack to node 1 -> Go to right child (3)
 * - currLen = 2, currSum = 4
 *
 * Go to left child (5)
 * - currLen = 3, currSum = 9
 *
 * Go to right child (7)
 * - currLen = 4, currSum = 16 -> leaf node
 * - maxLen = 4, maxSum = 16
 *
 * Go to right child (6)
 * - currLen = 3, currSum = 10 -> leaf node
 * - maxLen remains 4, maxSum remains 16
 *
 * Final answer: 16
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use DFS traversal from root to each leaf, keeping track of the current path length and current path sum. At each leaf, update the maxLen and maxSum accordingly.
// Time Complexity: O(N) where N is the number of nodes, since each node is visited once.
// Space Complexity: O(H) where H is the height of the tree, due to the recursion stack.

/*
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  public Node(int data){
 *      this.data = data;
 *  }
 * }
 */

class Solution {
    int maxLen = 0; // Stores the length of the longest path from root to leaf
    int maxSum = 0; // Stores the maximum sum along the longest path

    // Helper method to perform DFS traversal
    void dfs(Node node, int currLen, int currSum) {
        if (node == null) {
            return; // Base case: if node is null, just return
        }

        currLen += 1;             // Increment path length
        currSum += node.data;     // Add node value to path sum

        // If it's a leaf node
        if (node.left == null && node.right == null) {
            if (currLen > maxLen) {
                maxLen = currLen;
                maxSum = currSum;
            } else if (currLen == maxLen && currSum > maxSum) {
                maxSum = currSum;
            }
            return;
        }

        // Recur for left and right subtree
        dfs(node.left, currLen, currSum);
        dfs(node.right, currLen, currSum);
    }

    public int sumOfLongRootToLeafPath(Node root) {
        dfs(root, 0, 0);  // Start DFS with initial length and sum as 0
        return maxSum;    // Return the max sum found
    }
}

/*
 *
 * Dry Run
 * Tree:
 *          1
 *        /   \
 *       2     3
 *      /     / \
 *     4     5   6
 *            \
 *             7
 *
 * Start at root (1)
 * - currLen = 1, currSum = 1
 *
 * Go to left child (2)
 * - currLen = 2, currSum = 3
 *
 * Go to left child (4)
 * - currLen = 3, currSum = 7 -> leaf node
 * - maxLen = 3, maxSum = 7
 *
 * Backtrack to node 1 -> Go to right child (3)
 * - currLen = 2, currSum = 4
 *
 * Go to left child (5)
 * - currLen = 3, currSum = 9
 *
 * Go to right child (7)
 * - currLen = 4, currSum = 16 -> leaf node
 * - maxLen = 4, maxSum = 16
 *
 * Go to right child (6)
 * - currLen = 3, currSum = 10 -> leaf node
 * - maxLen remains 4, maxSum remains 16
 *
 * Final answer: 16
 *
 */
