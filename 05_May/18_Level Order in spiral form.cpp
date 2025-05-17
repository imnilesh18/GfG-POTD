/*
 * GfG Link: https://www.geeksforgeeks.org/problems/level-order-traversal-in-spiral-form/1
 *
 * Level Order in spiral form
 *
 * Difficulty: Easy Accuracy: 36.43% Submissions: 219K+ Points: 2 Average Time: 20m
 *
 * Given a binary tree and the task is to find the spiral order traversal of the tree and return the list containing the elements.
 * Spiral order Traversal mean: Starting from level 0 for root node, for all the even levels we print the node's value from right to left and for all the odd levels we print the node's value from left to right.
 * For below tree, function should return [1, 2, 3, 4, 5, 6, 7]
 *
 * Examples:
 *
 * Input: root = [1, 3, 2]
 * Output: [1, 3, 2]
 * Explanation: Start with root (1), print level 0 (right to left), then level 1 (left to right).
 *
 * Input: root = [10, 20, 30, 40, 60]
 * Output: [10, 20, 30, 60, 40]
 * Explanation: Start with root (10), print level 0 (right to left), level 1 (left to right), and continue alternating.
 *
 * Input: root = [1, 2, N, 4]
 * Output: [1, 2, 4]
 * Explanation: Start with root (1), then level 1 (left to right), then level 2 (right to left).
 *
 * Constraints:
 * 1 <= number of nodes <= 10^5
 * 0 <= node->data <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use Level Order Traversal with a queue. For each level, use a temporary array to store node values in reverse or normal order based on current level's direction.
// Time Complexity: O(n) - each node is visited exactly once.
// Space Complexity: O(n) - for queue and temporary vector used for each level.

/*
 * class Node
 * {
 *  int data;
 *  Node* left;
 *  Node* right;
 *
 *  Node(int x){
 *      data = x;
 *      left = right = NULL;
 *  }
 * };
 *
 */

class Solution {
public:
    vector<int> findSpiral(Node* root) {
        vector<int> result; // To store the final spiral order traversal

        if (root == nullptr) {
            return result; // Edge case: empty tree
        }

        queue<Node*> que; // Queue for level order traversal
        que.push(root);

        bool direction = false; // false => right to left, true => left to right

        while (!que.empty()) {
            int         n = que.size(); // Number of nodes at current level
            vector<int> row(n);         // Temporary vector to store current level's values

            for (int i = 0; i < n; i++) {
                Node* node = que.front();
                que.pop();

                // Determine index based on current direction
                int idx = direction ? i : (n - 1 - i);
                row[idx] = node->data; // Place node's value at calculated index

                if (node->left) {
                    que.push(node->left); // Add left child to queue
                }

                if (node->right) {
                    que.push(node->right); // Add right child to queue
                }
            }

            // Append current level's values to result
            for (int val : row) {
                result.push_back(val);
            }

            direction = !direction; // Toggle direction for next level
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: [1, 2, 3, 4, 5, N, 6]
 *
 *        1
 *       / \
 *      2   3
 *     / \   \
 *    4   5   6
 *
 *
 * Level 0:
 * queue = [1]
 * direction = false (right to left)
 * row = [1]                     → result = [1]
 *
 * Level 1:
 * queue = [2, 3]
 * direction = true (left to right)
 * row = [2, 3]                  → result = [1, 2, 3]
 *
 * Level 2:
 * queue = [4, 5, 6]
 * direction = false (right to left)
 * row = [6, 5, 4]               → result = [1, 2, 3, 6, 5, 4]
 *
 * Final Output: [1, 2, 3, 6, 5, 4]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Level Order Traversal with a queue. For each level, use a temporary array to store node values in reverse or normal order based on current level's direction.
// Time Complexity: O(n) - each node is visited exactly once.
// Space Complexity: O(n) - for queue and temporary array used for each level.

/*
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
 * }
 */

class Solution {
    public ArrayList<Integer> findSpiral(Node root) {
        ArrayList<Integer> result = new ArrayList<>(); // To store final spiral order

        if (root == null) {
            return result; // Edge case: empty tree
        }

        Queue<Node> que = new LinkedList<>(); // Queue for level order
        que.add(root);

        boolean direction = false; // false => right to left, true => left to right

        while (!que.isEmpty()) {
            int n = que.size();             // Number of nodes at current level
            Integer[] row = new Integer[n]; // Temporary array for current level

            for (int i = 0; i < n; i++) {
                Node node = que.poll(); // Dequeue the front node

                // Determine index based on current direction
                int idx = direction ? i : (n - 1 - i);
                row[idx] = node.data; // Place data at correct index

                if (node.left != null) {
                    que.add(node.left); // Enqueue left child
                }

                if (node.right != null) {
                    que.add(node.right); // Enqueue right child
                }
            }

            // Add all elements of row to result
            for (int val : row) {
                result.add(val);
            }

            direction = !direction; // Toggle direction
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: [1, 2, 3, 4, 5, N, 6]
 *
 *        1
 *       / \
 *      2   3
 *     / \   \
 *    4   5   6
 *
 * Level 0:
 * queue = [1]
 * direction = false (right to left)
 * row = [1]                     → result = [1]
 *
 * Level 1:
 * queue = [2, 3]
 * direction = true (left to right)
 * row = [2, 3]                  → result = [1, 2, 3]
 *
 * Level 2:
 * queue = [4, 5, 6]
 * direction = false (right to left)
 * row = [6, 5, 4]               → result = [1, 2, 3, 6, 5, 4]
 *
 * Final Output: [1, 2, 3, 6, 5, 4]
 *
 */
