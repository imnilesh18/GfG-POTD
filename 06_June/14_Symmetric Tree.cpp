/*
 * GfG Link: https://www.geeksforgeeks.org/problems/symmetric-tree/1
 *
 * Symmetric Tree
 *
 * Difficulty: Easy Accuracy: 44.96% Submissions: 160K+ oints: 2 Average Time: 20m+
 *
 * Given the root of a binary tree, check whether it is symmetric, i.e., whether the tree is a mirror image of itself.
 * A binary tree is symmetric if the left subtree is a mirror reflection of the right subtree.
 *
 * Examples:
 * Input: root[] = [1, 2, 2, 3, 4, 4, 3]
 * ex-1_1
 * Output: True
 * Explanation: As the left and right half of the above tree is mirror image, tree is symmetric.
 *
 * Input: root[] = [1, 2, 2, N, 3, N, 3]
 * ex-2_1
 * Output: False
 * Explanation:  As the left and right half of the above tree is not the mirror image, tree is not symmetric.
 *
 * Constraints:
 * 1  ≤ number of nodes ≤ 2000
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursion to check whether the left and right subtrees are mirror images of each other.
// Time Complexity: O(N), where N is the number of nodes. Each node is visited once.
// Space Complexity: O(H), where H is the height of the tree due to recursion stack (O(logN) for balanced tree, O(N) for skewed).
class Solution {
public:

    // Helper function to check if two subtrees are mirror images
    bool isMirror(Node* l, Node* r) {
        // If both nodes are NULL, they are mirror images
        if (l == NULL && r == NULL) {
            return true;
        }

        // If one is NULL and the other is not, not mirror images
        if (l == NULL || r == NULL) {
            return false;
        }

        // Check if current nodes are equal and subtrees are mirror images
        if ((l->data == r->data) && isMirror(l->left, r->right) && isMirror(l->right, r->left)) {
            return true;
        }

        // Otherwise, not mirror images
        return false;
    }

    // Main function to check if the tree is symmetric
    bool isSymmetric(Node* root) {
        // Empty tree is not symmetric as per this code
        if (!root) {
            return false;
        }

        // Check if left and right subtrees are mirror images
        return isMirror(root->left, root->right);
    }
};

/*
 *
 * Dry Run
 * Input: root[] = [1, 2, 2, 3, 4, 4, 3]
 *
 * Tree Structure:
 *         1
 *       /   \
 *      2     2
 *     / \   / \
 *    3  4  4  3
 *
 * Step 1: isSymmetric(1) → isMirror(2, 2)
 * Step 2: isMirror(2, 2) → values equal → check isMirror(3, 3) and isMirror(4, 4)
 * Step 3: isMirror(3, 3) → values equal → check isMirror(NULL, NULL) and isMirror(NULL, NULL) → both true
 * Step 4: isMirror(4, 4) → values equal → check isMirror(NULL, NULL) and isMirror(NULL, NULL) → both true
 * Step 5: all recursive calls return true → Final Output: true
 *
 * Input: root[] = [1, 2, 2, N, 3, N, 3]
 *
 * Tree Structure:
 *         1
 *       /   \
 *      2     2
 *       \     \
 *        3     3
 *
 * Step 1: isSymmetric(1) → isMirror(2, 2)
 * Step 2: isMirror(2, 2) → values equal → check isMirror(NULL, 3) → false (one side NULL)
 * Step 3: returns false → Final Output: false
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use recursion to check whether the left and right subtrees are mirror images of each other.
// Time Complexity: O(N), where N is the number of nodes. Each node is visited once.
// Space Complexity: O(H), where H is the height of the tree due to recursion stack (O(logN) for balanced tree, O(N) for skewed).
class Solution {
    // Helper function to check if two subtrees are mirror images
    public boolean isMirror(Node l, Node r) {
        // If both nodes are null, they are mirror images
        if (l == null && r == null) {
            return true;
        }

        // If one is null and the other is not, not mirror images
        if (l == null || r == null) {
            return false;
        }

        // Check if current nodes are equal and subtrees are mirror images
        if ((l.data == r.data) && isMirror(l.left, r.right) && isMirror(l.right, r.left)) {
            return true;
        }

        // Otherwise, not mirror images
        return false;
    }
    
    // Main function to check if the tree is symmetric
    public boolean isSymmetric(Node root) {
        // If tree is empty, it's not symmetric (based on this implementation)
        if (root == null) {
            return false;
        }

        // Check if left and right subtrees are mirror images
        return isMirror(root.left, root.right);
    }
}

/*
 *
 * Dry Run
 * Input: root[] = [1, 2, 2, 3, 4, 4, 3]
 *
 * Tree Structure:
 *         1
 *       /   \
 *      2     2
 *     / \   / \
 *    3  4  4  3
 *
 * Step 1: isSymmetric(1) → isMirror(2, 2)
 * Step 2: isMirror(2, 2) → values equal → check isMirror(3, 3) and isMirror(4, 4)
 * Step 3: isMirror(3, 3) → values equal → check isMirror(null, null) and isMirror(null, null) → both true
 * Step 4: isMirror(4, 4) → values equal → check isMirror(null, null) and isMirror(null, null) → both true
 * Step 5: all recursive calls return true → Final Output: true
 *
 * Input: root[] = [1, 2, 2, N, 3, N, 3]
 *
 * Tree Structure:
 *         1
 *       /   \
 *      2     2
 *       \     \
 *        3     3
 *
 * Step 1: isSymmetric(1) → isMirror(2, 2)
 * Step 2: isMirror(2, 2) → values equal → check isMirror(null, 3) → false (one side null)
 * Step 3: returns false → Final Output: false
 *
 */
