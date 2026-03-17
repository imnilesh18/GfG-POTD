# 🔥 Burning Tree

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/burning-tree/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-53.53%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
    <a href="https://opensource.org/licenses/MIT">
        <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
    </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the `root` of a binary tree and a `target` node, determine the **minimum time** required to burn the entire tree if the `target` node is set on fire. 

In one second, the fire spreads from a burning node to its:
- Left child
- Right child
- Parent node

**Note:** The tree contains unique values.

---

## 💡 Examples

### Example 1

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/702131/Web/Other/blobid0_1747048733.webp" alt="Burning Tree Example 1" />
</div>

```text
Input: root = [1, 2, 3, 4, 5, 6, 7], target = 2
Output: 3

Explanation: Initially 2 is set to fire at 0 sec.
At 1 sec: Nodes 4, 5, 1 catches fire.
At 2 sec: Node 3 catches fire.
At 3 sec: Nodes 6, 7 catches fire.
It takes 3s to burn the complete tree.
````

### Example 2

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/702131/Web/Other/blobid1_1747048769.webp" alt="Burning Tree Example 1" />
</div>

```text
Input: root = [1, 2, 3, 4, 5, N, 7, 8, N, N, 10], target = 10
Output: 5

Explanation: Initially 10 is set to fire at 0 sec.
At 1 sec: Node 5 catches fire.
At 2 sec: Node 2 catches fire.
At 3 sec: Nodes 1 and 4 catches fire.
At 4 sec: Node 3 and 8 catches fire.
At 5 sec: Node 7 catches fire.
It takes 5s to burn the complete tree.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Consider **Example 1** where the root is `1` and the target is `2`.

1.  **Time t = 0:** The target node `2` catches fire.
2.  **Time t = 1:** The fire spreads from node `2` to all its unvisited adjacent nodes. It burns its left child (`4`), right child (`5`), and its parent (`1`).
3.  **Time t = 2:** Now nodes `4`, `5`, and `1` are burning.
      - Nodes `4` and `5` have no unburned adjacent nodes.
      - Node `1` spreads the fire to its right child (`3`).
4.  **Time t = 3:** Node `3` is now burning. It spreads the fire to its left child (`6`) and right child (`7`).
5.  **Time t = 4:** Nodes `6` and `7` have no further unburned adjacent nodes. The fire stops.
6.  **Total Time:** The maximum time taken for the fire to reach the farthest leaf is `3` seconds.

</details>

-----

## 🔒 Constraints

  - $1 \le \text{number of nodes} \le 10^5$
  - $1 \le \text{node.data} \le 10^5$

-----

## 🛠️ Solution Approaches

### **Breadth-First Search (BFS) with Parent Mapping**

To simulate the fire spreading in all directions, we need to traverse from children back to their parents. However, standard binary tree nodes do not have a parent pointer. Thus, we solve this in two main steps:

1.  **Establish Parent Pointers:** Use BFS (level-order traversal) starting from the root. During this traversal, store the mapping of each node to its parent in a Hash Map. At the same time, search for the target node and store its reference.
2.  **Simulate the Fire:** Once parent mappings are established, the tree acts as an undirected graph. Perform a second BFS starting from the target node. Keep track of visited (burned) nodes using a Map to avoid revisiting. Each level of the BFS corresponds to $1$ second of burning time. The number of levels traversed gives the minimum time to burn the entire tree.

### 💻 C++ Solution

```cpp
// Intuition: The problem can be modeled as finding the shortest path to all nodes in an undirected graph. We map parent pointers to traverse upwards and use BFS to simulate the fire spreading radially.
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
 * 1
 * / \
 * 2     3
 * / \   / \
 * 4   5 6   7
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
```

### ☕ Java Solution

```java
// Intuition: The problem can be modeled as finding the shortest path to all nodes in an undirected graph. We map parent pointers to traverse upwards and use BFS to simulate the fire spreading radially.
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
 * 1
 * / \
 * 2     3
 * / \   / \
 * 4   5 6   7
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
```

-----

## 🧠 Key Insights

  - **Graph Conversion:** By simply mapping each node to its parent using a HashMap, we effectively convert a single-direction Tree into an undirected Graph.
  - **Level-Order Spread:** Standard Breadth-First Search (BFS) operates level-by-level radially. This property naturally perfectly mimics the "1 second per level" fire spreading requirement.
  - **Time Initial State:** We initialize the time `t = -1` (or process time after level iteration appropriately) to account for the $0^{th}$ second when the target node is initially ignited but hasn't spread the fire yet.

-----

## 🚀 Further Exploration

If you enjoyed this problem, you might want to check out these related concepts and problems:

  - **All Nodes Distance K in Binary Tree:** Similar parent-mapping graph traversal technique.
  - **Rotting Oranges:** Classic BFS on a Grid using a similar time-based simulation concept.
  - **Amount of Time for Binary Tree to Be Infected:** The direct LeetCode equivalent to this exact problem.

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Burning Tree](https://www.geeksforgeeks.org/problems/burning-tree/1)

-----

## ✍️ Author

- [imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

`#Tree` `#BFS` `#DataStructures` `#Algorithms` `#GeeksforGeeks`