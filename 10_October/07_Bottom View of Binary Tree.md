# ⬇️ Bottom View of Binary Tree

<div align="center">
  
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-43853D?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)
![Accuracy: 54.18%](https://img.shields.io/badge/Accuracy-54.18%25-red.svg)
![Points: 4](https://img.shields.io/badge/Points-4-blue.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

</div>
<br>

⚠️ Educational Use Only:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📜 Problem Statement

You are given the **root** of a binary tree, and your task is to return its **bottom view**. The bottom view of a binary tree is the set of nodes visible when the tree is viewed from the bottom.

**Note**: If there are multiple bottom-most nodes for a horizontal distance from the root, then the **latter** one in the level order traversal is considered.

---

## 💡 Examples

### Example 1:

```
Input: root = [1, 2, 3, 4, 5, N, 6]
Output: [4, 2, 5, 3, 6]
```

<details>
<summary>📖 Example Breakdown</summary>

| Node | Horizontal Distance (HD) |
| :--: | :----------------------: |
|  4   |            -2            |
|  2   |            -1            |
| 1, 5 |    0 (5 overwrites 1)    |
|  3   |            1             |
|  6   |            2             |

Viewing the tree from the bottom, at horizontal distance `HD=0`, the node `5` is lower than node `1`, so `5` is visible. The final ordered view (left to right) is `[4, 2, 5, 3, 6]`.

</details>

### Example 2:

```
Input: root = [20, 8, 22, 5, 3, 4, 25, N, N, 10, 14, N, N, 28, N]
Output: [5, 10, 4, 28, 25]
```

---

## 🧱 Constraints

- **1 ≤** number of nodes **≤ 10^5**
- **1 ≤** node->data **≤ 10^5**

| Expected Time Complexity | Expected Auxiliary Space |
| :----------------------- | :----------------------- |
| **O(N)**                 | **O(N)**                 |

---

## 💻 Solution Approaches

### Optimized Solution: Level Order Traversal (BFS) with HashMap

The most efficient approach to find the bottom view is using **Level Order Traversal (BFS)** combined with tracking the **Horizontal Distance (HD)** of each node.

1.  We assign the root an HD of `0`.
2.  The left child of a node gets `HD - 1`, and the right child gets `HD + 1`.
3.  We use a `map` (or `TreeMap` in Java/sorted `std::map` in C++) to store the nodes, mapping the `HD` to the node's `data`.
4.  Since we process the tree level by level using BFS, when multiple nodes fall on the same HD, the node that is processed _later_ in the traversal (which is guaranteed to be either on a deeper level or the latter node on the same level) will simply **overwrite** the value in the map for that HD. This property naturally ensures that we keep the bottom-most node for every horizontal column.
5.  Finally, iterating through the map (which is sorted by key/HD in C++'s `std::map`) gives the bottom view in left-to-right order.

### C++ Code (Optimized)

```cpp
/*
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};
*/

class Solution {
 public:
    // Intuition: The bottom view consists of the nodes that are deepest at each horizontal distance (HD).
    // Approach: Perform a Level Order Traversal (BFS) while tracking the HD for each node. Use a map to store
    //            the node value for each HD, allowing later (deeper) nodes to overwrite previous ones.
    // Time Complexity: O(N log W) where N is the number of nodes and W is the width of the tree.
    //                  The log W factor comes from map insertion/update (if using C++'s std::map).
    //                  It would be O(N) if using std::unordered_map + sorting keys.
    // Space Complexity: O(N) for storing the map and the queue.
    vector<int> bottomView(Node *root) {
        // Handle the edge case of an empty tree.
        if (!root) return {};

        // Map to store the last node at each horizontal distance (HD).
        // std::map keeps keys (HDs) sorted, giving the final left-to-right order.
        map<int, int> hdMap;

        // Queue to store nodes along with their horizontal distances (HD).
        queue<pair<Node*, int>> q;

        // Start level order traversal with the root at HD 0.
        q.push({root, 0});

        // Process nodes until the queue is empty (standard BFS).
        while (!q.empty()) {

            // Get current node and its HD from the front of the queue.
            Node *curr = q.front().first;
            int hd = q.front().second;
            q.pop();

            // Update the map: current node's data is stored for the calculated HD.
            // This implicitly handles the "bottom-most" and "latter" condition,
            // as nodes processed later in BFS will overwrite shallower/earlier nodes.
            hdMap[hd] = curr->data;

            // If the left child exists, push it to the queue with HD - 1.
            if (curr->left) {
                q.push({curr->left, hd - 1});
            }

            // If the right child exists, push it to the queue with HD + 1.
            if (curr->right) {
                q.push({curr->right, hd + 1});
            }
        }

        // Vector to store the final result in HD order.
        vector<int> result;

        // Iterate through the map. Since std::map is sorted by key (HD),
        // the elements are extracted in the correct left-to-right order.
        for (auto it : hdMap) {
            result.push_back(it.second);
        }

        return result;

    }
};

/*
*
* Dry Run
* Input: root = [1, 2, 3, 4, 5, N, 6]
* Tree Structure:
* 1(HD 0)
* / \
* 2(HD -1) 3(HD 1)
* / \      / \
* 4(-2) 5(0)  N 6(2)
*
* Steps:
* 1. Initialize: hdMap = {}, q = [{1, 0}]
* 2. Pop {1, 0}: hdMap = {0: 1}. q.push({2, -1}), q.push({3, 1}). q = [{2, -1}, {3, 1}]
* 3. Pop {2, -1}: hdMap = {0: 1, -1: 2}. q.push({4, -2}), q.push({5, 0}). q = [{3, 1}, {4, -2}, {5, 0}]
* 4. Pop {3, 1}: hdMap = {0: 1, -1: 2, 1: 3}. q.push({6, 2}). q = [{4, -2}, {5, 0}, {6, 2}]
* 5. Pop {4, -2}: hdMap = {0: 1, -1: 2, 1: 3, -2: 4}. q = [{5, 0}, {6, 2}]
* 6. Pop {5, 0}: hdMap[0] = 5 (OVERWRITE 1 with 5). hdMap = {0: 5, -1: 2, 1: 3, -2: 4}. q = [{6, 2}]
* 7. Pop {6, 2}: hdMap = {0: 5, -1: 2, 1: 3, -2: 4, 2: 6}. q = []
* 8. Final Result (from sorted hdMap keys: -2, -1, 0, 1, 2): [4, 2, 5, 3, 6]
*
*/
```

---

## 🔑 Key Insights

- **Horizontal Distance (HD):** This concept is crucial for all vertical/horizontal views of a tree. It acts as a column index (Root at 0, Left at -1, Right at +1).
- **BFS (Level Order Traversal):** BFS processes nodes in a top-down, level-by-level manner. This is essential because the "bottom view" is defined by the nodes closest to the base.
- **Overwriting Property:** By using a map (`HD -> NodeValue`) and performing BFS, any later node encountered (which must be at the same HD but a deeper level or later in the same level) automatically overwrites the data of a shallower/earlier node. The _last_ node processed for a given HD is thus the bottom-most visible node.
- **Map for Ordering:** Using `std::map` (C++) or `TreeMap` (Java) automatically sorts the horizontal distances, ensuring the final output array is correctly ordered from left-to-right.

---

## 🚀 Further Exploration

- **Top View of Binary Tree:** Modify the logic to only keep the _first_ node encountered for any given HD (i.e., do not overwrite the map entry).
- **Vertical Order Traversal:** Store all nodes at each HD, sorted by their vertical level, instead of just the last one. This requires using a List/Vector of Pairs for the map value: `Map<HD, List<Pair<LV, NodeData>>>`.

---

## 🔗 References

- [Original GFG Problem: Bottom View of Binary Tree](https://www.geeksfor geeks.org/problems/bottom-view-of-binary-tree/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

- `binary-tree`
- `tree-traversal`
- `bfs`
- `level-order`
- `hashmap`
- `data-structure`
- `geeksforgeeks`

---

## ⚖️ License

The code and content in this repository are distributed under the **MIT License**.
_An explicit reminder that this content is for educational use and personal learning._
