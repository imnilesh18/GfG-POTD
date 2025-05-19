/*
 * Burning Tree
 *
 * Difficulty: Hard Accuracy: 53.53% Submissions: 108K+ Points: 8
 *
 * Given a binary tree and a target node, determine the minimum time required to burn the entire tree if the target node is set on fire. In one second, the fire spreads from a node to its left child, right child, and parent.
 * Note: The tree contains unique values.
 *
 * Examples :
 *
 * Input: root[] = [1, 2, 3, 4, 5, 6, 7], target = 2
 * Output: 3
 * Explanation: Initially 2 is set to fire at 0 sec
 * At 1 sec: Nodes 4, 5, 1 catches fire.
 * At 2 sec: Node 3 catches fire.
 * At 3 sec: Nodes 6, 7 catches fire.
 * It takes 3s to burn the complete tree.
 *
 * Input: root[] = [1, 2, 3, 4, 5, N, 7, 8, N, 10], target = 10
 * Output: 5
 * Explanation: Initially 2 is set to fire at 0 sec
 * At 1 sec: Node 5 catches fire.
 * At 2 sec: Node 2 catches fire.
 * At 3 sec: Nodes 1 and 4 catches fire.
 * At 4 sec: Node 3 and 8 catches fire.
 * At 5 sec: Node 7 catches fire.
 * It takes 5s to burn the complete tree.
 *
 * Constraints:
 * 1 ≤ number of nodes ≤ 10^5
 * 1 ≤ node->data ≤ 10^5
 */

/************************************************************ C++ ************************************************/

/*
 * class Node {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int val) {
 *      data = val;
 *      left = right = NULL;
 *  }
 * };
 */

// Approach: First map each node to its parent using BFS. Then simulate fire spreading using BFS from the target node to its neighbors (left, right, parent) while tracking visited nodes and counting time.
// Time Complexity: O(N), where N is the number of nodes in the tree. We traverse each node once.
// Space Complexity: O(N), for storing parent mapping, visited map, and queue for BFS.
class Solution {
public:
    int minTime(Node* root, int target) {
        // Step 1: Map each node to its parent and locate the target node
        queue<Node*> que;

        que.push(root);

        unordered_map<Node*, Node*> parent; // To store parent of each node
        parent[root] = nullptr;

        Node* tar = nullptr; // Pointer to store target node

        while (!que.empty()) {
            Node* curr = que.front();
            que.pop();

            // Locate the target node
            if (curr->data == target) {
                tar = curr;
            }

            // Map left child to parent
            if (curr->left) {
                que.push(curr->left);
                parent[curr->left] = curr;
            }

            // Map right child to parent
            if (curr->right) {
                que.push(curr->right);
                parent[curr->right] = curr;
            }
        }

        // Step 2: Simulate burning using BFS from target node
        unordered_map<Node*, bool> visited; // Track visited nodes to prevent re-burning
        int t = -1;                         // Time counter
        que.push(tar);                      // Start BFS from target node

        while (!que.empty()) {
            int n = que.size(); // Nodes burning at current second

            while (n--) {
                Node* curr = que.front();
                que.pop();

                visited[curr] = true; // Mark current node as burned

                // Spread to left child
                if (curr->left && !visited[curr->left]) {
                    que.push(curr->left);
                }

                // Spread to right child
                if (curr->right && !visited[curr->right]) {
                    que.push(curr->right);
                }

                // Spread to parent
                if (parent[curr] && !visited[parent[curr]]) {
                    que.push(parent[curr]);
                }
            }
            t++; // Increment time after processing current level
        }
        return t;
    }
};

/*
 *
 * Dry Run
 *
 * Input: root = [1, 2, 3, 4, 5, 6, 7], target = 2
 *
 * Binary Tree Structure:
 *          1
 *         / \
 *       2     3
 *      / \   / \
 *     4   5 6   7
 *
 * Step 1: Map each node to its parent
 * parent[2] = 1
 * parent[4] = 2
 * parent[5] = 2
 * parent[3] = 1
 * parent[6] = 3
 * parent[7] = 3
 *
 * Target node = 2
 *
 * Step 2: BFS from node 2 to simulate burning
 *
 * Initialize:
 * Queue = [2]
 * Visited = {}
 * Time = -1
 *
 * → Time = 0
 * Process node: 2
 * Burns:
 * - 4 (left of 2)
 * - 5 (right of 2)
 * - 1 (parent of 2)
 * Queue = [4, 5, 1]
 *
 * → Time = 1
 * Process nodes: 4, 5, 1
 * Burns:
 * - 3 (right of 1)
 * Queue = [3]
 *
 * → Time = 2
 * Process node: 3
 * Burns:
 * - 6 (left of 3)
 * - 7 (right of 3)
 * Queue = [6, 7]
 *
 * → Time = 3
 * Process nodes: 6, 7
 * No more new nodes to burn
 * Queue becomes empty
 *
 * → Done
 *
 * Answer: 3 seconds
 *
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node {
 *  int data;
 *  Node left;
 *  Node right;
 *
 *  Node(int data) {
 *      this.data = data;
 *      left = null;
 *      right = null;
 *  }
 * }
 */

// Approach: First map each node to its parent using BFS. Then simulate fire spreading using BFS from the target node to its neighbors (left, right, parent) while tracking visited nodes and counting time.
// Time Complexity: O(N), where N is the number of nodes in the tree. We traverse each node once.
// Space Complexity: O(N), for storing parent mapping, visited map, and queue for BFS.
class Solution {
    public static int minTime(Node root, int target) {
        // Step 1: Map each node to its parent and locate the target node
        Queue<Node>     que    = new LinkedList<>();
        Map<Node, Node> parent = new HashMap<>();
        Node            tar    = null;

        que.offer(root);
        parent.put(root, null);

        while (!que.isEmpty()) {
            Node curr = que.poll();

            // Locate the target node
            if (curr.data == target) {
                tar = curr;
            }

            // Map left child to parent
            if (curr.left != null) {
                que.offer(curr.left);
                parent.put(curr.left, curr);
            }

            // Map right child to parent
            if (curr.right != null) {
                que.offer(curr.right);
                parent.put(curr.right, curr);
            }
        }

        // Step 2: Simulate burning using BFS from target node
        Map<Node, Boolean> visited = new HashMap<>();
        int t = -1;     // Time counter
        que.offer(tar); // Start BFS from target node

        while (!que.isEmpty()) {
            int n = que.size(); // Nodes burning at current second

            while (n-- > 0) {
                Node curr = que.poll();
                visited.put(curr, true); // Mark current node as burned

                // Spread to left child
                if (curr.left != null && !visited.containsKey(curr.left)) {
                    que.offer(curr.left);
                }

                // Spread to right child
                if (curr.right != null && !visited.containsKey(curr.right)) {
                    que.offer(curr.right);
                }

                // Spread to parent
                if (parent.get(curr) != null && !visited.containsKey(parent.get(curr))) {
                    que.offer(parent.get(curr));
                }
            }

            t++; // Increment time after processing current level
        }

        return t;
    }
}

/*
 *
 * Dry Run
 *
 * Input: root = [1, 2, 3, 4, 5, 6, 7], target = 2
 *
 * Binary Tree Structure:
 *          1
 *         / \
 *       2     3
 *      / \   / \
 *     4   5 6   7
 *
 * Step 1: Map each node to its parent
 * parent[2] = 1
 * parent[4] = 2
 * parent[5] = 2
 * parent[3] = 1
 * parent[6] = 3
 * parent[7] = 3
 *
 * Target node = 2
 *
 * Step 2: BFS from node 2 to simulate burning
 *
 * Initialize:
 * Queue = [2]
 * Visited = {}
 * Time = -1
 *
 * → Time = 0
 * Process node: 2
 * Burns:
 * - 4 (left of 2)
 * - 5 (right of 2)
 * - 1 (parent of 2)
 * Queue = [4, 5, 1]
 *
 * → Time = 1
 * Process nodes: 4, 5, 1
 * Burns:
 * - 3 (right of 1)
 * Queue = [3]
 *
 * → Time = 2
 * Process node: 3
 * Burns:
 * - 6 (left of 3)
 * - 7 (right of 3)
 * Queue = [6, 7]
 *
 * → Time = 3
 * Process nodes: 6, 7
 * No more new nodes to burn
 * Queue becomes empty
 *
 * → Done
 *
 * Answer: 3 seconds
 *
 */
