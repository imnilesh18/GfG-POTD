/*
 * Maximum sum of Non-adjacent nodes
 *
 * Difficulty: Medium Accuracy: 55.35% Submissions: 83K+ Points: 4 Average Time: 45m
 *
 * Given a binary tree with a value associated with each node. Your task is to select a subset of nodes such that the sum of their values is maximized, with the condition that no two selected nodes are directly connected that is, if a node is included in the subset, neither its parent nor its children can be included.
 *
 * Examples:
 *
 * Input: root[] = [11, 1, 2]
 * Output: 11
 * Explanation: The maximum sum is obtained by selecting the node 11.
 *
 * Input: root[] = [1, 2, 3, 4, N, 5, 6]
 * Output: 16
 * Explanation: The maximum sum is obtained by selecting the nodes 1, 4, 5, and 6, which are not directly connected to each other. Their total sum is 16.
 *
 * Constraints:
 * 1 ≤ no. of nodes in the tree ≤ 10^4
 * 1 ≤ Node.val ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use post-order traversal (DFS) and at each node, calculate two values:
//           1. Including the node (can't include its children)
//           2. Excluding the node (can include or exclude children independently)
// Time Complexity: O(N), where N = number of nodes (each node visited once)
// Space Complexity: O(H), where H = height of the tree (due to recursion stack)
class Solution {
public:

    pair<int, int> maxSumHelper(Node* root) {
        if (root == nullptr) {
            // If root is null, both include and exclude sums are 0
            pair<int, int> sum(0, 0);
            return sum;
        }

        // Recursively calculate for left and right subtrees
        pair<int, int> sum1 = maxSumHelper(root->left);
        pair<int, int> sum2 = maxSumHelper(root->right);
        pair<int, int> sum;

        // Including this node: Add root's value + exclude sums of left and right children
        sum.first = sum1.second + sum2.second + root->data;

        // Excluding this node: Take maximum of including or excluding left child + same for right
        sum.second = max(sum1.first, sum1.second) + max(sum2.first, sum2.second);

        return sum;
    }
    // Returns maximum sum from subset of nodes of binary tree under given constraints
    int getMaxSum(Node* root) {
        pair<int, int> res = maxSumHelper(root);

        // Return maximum of including or excluding the root
        return max(res.first, res.second);
    }
};

/*
 *
 * Dry Run
 *
 * Example: Tree = [1, 2, 3, 4, N, 5, 6]
 *
 * Structure:
 *        1
 *       / \
 *      2   3
 *     /    / \
 *    4    5   6
 *
 * Step-by-step:
 * - At node 4:
 *   - Include = 4 (no children)
 *   - Exclude = 0
 *
 * - At node 2:
 *   - Left child (4): Include=4, Exclude=0
 *   - Right child (null): Include=0, Exclude=0
 *   - Include = 0 (left and right children Exclude) + 2 (current node) = 2
 *   - Exclude = max(4,0) + 0 = 4
 *
 * - At node 5:
 *   - Include = 5
 *   - Exclude = 0
 *
 * - At node 6:
 *   - Include = 6
 *   - Exclude = 0
 *
 * - At node 3:
 *   - Left child (5): Include=5, Exclude=0
 *   - Right child (6): Include=6, Exclude=0
 *   - Include = 0 + 0 + 3 = 3
 *   - Exclude = max(5,0) + max(6,0) = 11
 *
 * - At node 1:
 *   - Left child (2): Include=2, Exclude=4
 *   - Right child (3): Include=3, Exclude=11
 *   - Include = 4 + 11 + 1 = 16
 *   - Exclude = max(2,4) + max(3,11) = 4 + 11 = 15
 *
 * Final Answer = max(16, 15) = 16
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use post-order traversal (DFS) to calculate for each node:
//           1. Maximum sum including the node (excluding its children)
//           2. Maximum sum excluding the node (can include or exclude its children independently)
// Time Complexity: O(N), where N = number of nodes (each node processed once)
// Space Complexity: O(H), where H = height of the tree (due to recursion stack)
class Solution {
    // Helper function that returns a pair of (include, exclude) sums
    private int[] maxSumHelper(Node root) {
        if (root == null) {
            // If node is null, both include and exclude sums are 0
            return new int[]{ 0, 0 };
        }

        // Recursive calls for left and right subtrees
        int[] left  = maxSumHelper(root.left);
        int[] right = maxSumHelper(root.right);

        int[] result = new int[2];

        // If we include this node, we cannot include its immediate children
        result[0] = root.data + left[1] + right[1];

        // If we exclude this node, we can take maximum of including or excluding each child
        result[1] = Math.max(left[0], left[1]) + Math.max(right[0], right[1]);

        return result;
    }
    // Function to return the maximum sum of non-adjacent nodes
    public int getMaxSum(Node root) {
        int[] res = maxSumHelper(root);

        // Return the maximum of including or excluding the root
        return Math.max(res[0], res[1]);
    }
}

/*
 *
 * Dry Run
 *
 * Example: Tree = [1, 2, 3, 4, N, 5, 6]
 *
 * Structure:
 *        1
 *       / \
 *      2   3
 *     /    / \
 *    4    5   6
 *
 * Step-by-step:
 * - At node 4:
 *   - Include = 4 (no children)
 *   - Exclude = 0
 *
 * - At node 2:
 *   - Left child (4): Include=4, Exclude=0
 *   - Right child (null): Include=0, Exclude=0
 *   - Include = 0 + 0 + 2 = 2
 *   - Exclude = max(4,0) + 0 = 4
 *
 * - At node 5:
 *   - Include = 5
 *   - Exclude = 0
 *
 * - At node 6:
 *   - Include = 6
 *   - Exclude = 0
 *
 * - At node 3:
 *   - Left child (5): Include=5, Exclude=0
 *   - Right child (6): Include=6, Exclude=0
 *   - Include = 0 + 0 + 3 = 3
 *   - Exclude = max(5,0) + max(6,0) = 5 + 6 = 11
 *
 * - At node 1:
 *   - Left child (2): Include=2, Exclude=4
 *   - Right child (3): Include=3, Exclude=11
 *   - Include = 4 + 11 + 1 = 16
 *   - Exclude = max(2,4) + max(3,11) = 4 + 11 = 15
 *
 * Final Answer = max(16, 15) = 16
 *
 */
