/*
 * GfG Link: https://www.geeksforgeeks.org/problems/root-to-leaf-paths/1
 *
 * Root to Leaf Paths
 *
 * Difficulty: Medium Accuracy: 43.65% Submissions: 138K+ Points: 4 Average Time: 30m
 *
 * Given a Binary Tree, you need to find all the possible paths from the root node to all the leaf nodes of the binary tree.
 * Note: The paths should be returned such that paths from the left subtree of any node are listed first, followed by paths from the right subtree.
 *
 * Examples:
 *
 * Input: root[] = [1, 2, 3, 4, 5, N, N]
 * ex-3
 * Output: [[1, 2, 4], [1, 2, 5], [1, 3]]
 * Explanation: All the possible paths from root node to leaf nodes are: 1 -> 2 -> 4, 1 -> 2 -> 5 and 1 -> 3
 *
 * Input: root[] = [1, 2, 3]
 * Output: [[1, 2], [1, 3]]
 * Explanation: All the possible paths from root node to leaf nodes are: 1 -> 2 and 1 -> 3
 *
 * Input: root[] = [10, 20, 30, 40, 60, N, N]
 * Output: [[10, 20, 40], [10, 20, 60], [10, 30]]
 * Explanation: All the possible paths from root node to leaf nodes are: 10 -> 20 -> 40, 10 -> 20 -> 60 and 10 -> 30
 *
 *
 * Constraints:
 * 1 <= number of nodes <= 10^4
 * 1 <= node->data <= 10^4
 */

/************************************************************ C++ ************************************************/

/*
 *
 * Definition for Binary Tree Node
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

// Approach: Use DFS with backtracking to explore all paths from root to leaves, storing paths when a leaf node is reached.
// Time Complexity: O(N) – Every node is visited once.
// Space Complexity: O(H) – H is the height of the tree due to the recursion stack in DFS.
class Solution {
public:
    // Helper function to perform DFS traversal and collect paths
    void solve(Node* node, vector<int>& path, vector<vector<int>>& paths) {
        if (node == nullptr) {
            return;   // base case: if the node is null, just return
        }

        // Add current node's data to path
        path.push_back(node->data);

        // If the current node is a leaf, store the current path
        if (node->left == nullptr && node->right == nullptr) {
            paths.push_back(path);   // add current path to result
        } else {
            // Recursively call for left and right subtrees
            solve(node->left, path, paths);    // left subtree
            solve(node->right, path, paths);   // right subtree
        }

        // Backtrack to explore other paths
        path.pop_back();
    }
    // Function to get all paths from root to leaf
    vector<vector<int>> Paths(Node* root) {
        vector<vector<int>> paths;  // final list of all root-to-leaf paths
        vector<int>          path;   // current path being explored

        solve(root, path, paths);    // start DFS from the root
        return paths;                // return the collected paths
    }
};

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 *
 * Representation:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 *
 * Step 1: Start at root node 1 → path = [1]
 * Step 2: Go to left child 2 → path = [1, 2]
 * Step 3: Go to left child 4 → path = [1, 2, 4]
 * Step 4: 4 is a leaf → store [1, 2, 4]
 * Step 5: Backtrack to 2, then go to right child 5 → path = [1, 2, 5]
 * Step 6: 5 is a leaf → store [1, 2, 5]
 * Step 7: Backtrack to 1, then go to right child 3 → path = [1, 3]
 * Step 8: 3 is a leaf → store [1, 3]
 *
 * Final Output: [[1, 2, 4], [1, 2, 5], [1, 3]]
 *
 */

/************************************************************ JAVA ************************************************/

/*
 *
 * Definition for Binary Tree Node
 * class Node
 * {
 *  int data;
 *  Node left;
 *  Node right;
 *
 *  Node(int data)
 *  {
 *      this.data = data;
 *      left = null;
 *      right = null;
 *  }
 * }
 */

// Approach: Use DFS with backtracking to explore all paths from root to leaves, storing paths when a leaf node is reached.
// Time Complexity: O(N) – Every node is visited once.
// Space Complexity: O(H) – H is the height of the tree due to the recursion stack in DFS.
class Solution {
    // Helper function to perform DFS traversal and collect paths
    private static void solve(Node node, ArrayList<Integer> path, ArrayList<ArrayList<Integer>> paths) {
        if (node == null) {
            return; // base case: if the node is null, just return
        }

        // Add current node's data to path
        path.add(node.data);

        // If the current node is a leaf, store the current path
        if (node.left == null && node.right == null) {
            paths.add(new ArrayList<>(path)); // add a copy of the current path to result
        } else {
            // Recursively call for left and right subtrees
            solve(node.left, path, paths);  // left subtree
            solve(node.right, path, paths); // right subtree
        }

        // Backtrack to explore other paths
        path.remove(path.size() - 1);
    }
    // Main function to return all root-to-leaf paths
    public static ArrayList<ArrayList<Integer>> Paths(Node root) {
        ArrayList<ArrayList<Integer>> paths = new ArrayList<>(); // final list of all root-to-leaf paths
        ArrayList<Integer>             path  = new ArrayList<>(); // current path being explored

        solve(root, path, paths);                                 // start DFS from the root
        return paths;                                             // return the collected paths
    }
}

/*
 *
 * Dry Run
 *
 * Input Tree: [1, 2, 3, 4, 5, N, N]
 *
 * Representation:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 *
 * Step 1: Start at root node 1 → path = [1]
 * Step 2: Go to left child 2 → path = [1, 2]
 * Step 3: Go to left child 4 → path = [1, 2, 4]
 * Step 4: 4 is a leaf → store [1, 2, 4]
 * Step 5: Backtrack to 2, then go to right child 5 → path = [1, 2, 5]
 * Step 6: 5 is a leaf → store [1, 2, 5]
 * Step 7: Backtrack to 1, then go to right child 3 → path = [1, 3]
 * Step 8: 3 is a leaf → store [1, 3]
 *
 * Final Output: [[1, 2, 4], [1, 2, 5], [1, 3]]
 *
 */
