# 🌳 Top View of Binary Tree

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy: 38.43%](https://img.shields.io/badge/Accuracy-38.43%25-brightgreen?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given the `root` of a binary tree, and your task is to return its **top view**. The top view of a binary tree is the set of nodes visible when the tree is viewed from the top.

**Note:**
- Return the nodes from the leftmost node to the rightmost node.
- If multiple nodes overlap at the same horizontal position, only the topmost (closest to the root) node is included in the view. 

---

## 💡 Examples

### Example 1
```text
Input: root = [1, 2, 3]
Output: [2, 1, 3]
Explanation: The Green colored nodes represents the top view in the below Binary tree.

```

### Example 2

```text
Input: root = [10, 20, 30, 40, 60, 90, 100]
Output: [40, 20, 10, 30, 100]
Explanation: The Green colored nodes represents the top view in the below Binary tree.

```

<details>
<summary>📖 <b>Example Breakdown</b> (Click to expand)</summary>

Let's trace **Example 1**: `root = [1, 2, 3]`

1. **Initial Root `(1)`:** - Positioned at Horizontal Distance (HD) = `0`.
* First node seen at `HD = 0`, so it is visible from the top.


2. **Left Child `(2)`:**
* Positioned at `HD = -1` (root's HD - 1).
* First node seen at `HD = -1`, so it is visible from the top.


3. **Right Child `(3)`:**
* Positioned at `HD = +1` (root's HD + 1).
* First node seen at `HD = +1`, so it is visible from the top.



*Sorting horizontally from left to right (by HD: -1, 0, 1):* The top view is `[2, 1, 3]`.

</details>

---

## ⚠️ Constraints

* `1 ≤ number of nodes ≤ 10^5`
* `1 ≤ node->data ≤ 10^5`

**Expected Complexities:**

* **Time Complexity:** `O(n log n)` *(Due to Map sorting properties, though O(n) is possible with limits)*
* **Auxiliary Space:** `O(n)`

---

## 🛠️ Solution Approaches

### BFS Traversal with Horizontal Distance Mapping

By traversing the tree level by level (Breadth-First Search) and keeping track of the horizontal distance from the root, we ensure that the first time we visit a specific horizontal distance, we are looking at the topmost node at that vertical line. Using a standard `map` ensures our final result remains sorted from left to right.

```cpp
// Intuition: To view the tree from the top, we only need the first node we encounter at each vertical line (horizontal distance). Level Order Traversal (BFS) perfectly guarantees that the first node we see at any horizontal distance is the topmost one.
// Approach: Use a queue to perform BFS, storing pairs of (node, horizontal distance). Use a map to store the first node's data encountered at each horizontal distance. As we traverse, we push children into the queue with updated distances (hd - 1 for left, hd + 1 for right). Finally, extract the values from the map which keeps them sorted by horizontal distance.
// Time Complexity: O(N log N) where N is the number of nodes. We visit each node once, and inserting into the std::map takes O(log N) time.
// Space Complexity: O(N) to store the nodes in the queue for BFS and the unique horizontal distances in the map.

/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
  public:
    vector<int> topView(Node *root) {
        vector<int> result;
        if (!root) return result;
    
        // Map to store the first node at each horizontal distance (hd)
        map<int, int> topNodes;
        
        // Queue to store nodes along with their horizontal distance
        queue<pair<Node*, int>> q;
    
        q.push({root, 0});
    
        while (!q.empty()) {
            
            auto nodeHd = q.front();
            
            // Current node
            Node *node = nodeHd.first;  
            
            // Current horizontal distance
            int hd = nodeHd.second;     
            q.pop();
    
            // If this horizontal distance is seen for the first time, store the node
            if (topNodes.find(hd) == topNodes.end()) {
                topNodes[hd] = node->data;
            }
    
            // Add left child to the queue with horizontal distance - 1
            if (node->left) {
                q.push({node->left, hd - 1});
            }
    
            // Add right child to the queue with horizontal distance + 1
            if (node->right) {
                q.push({node->right, hd + 1});
            }
        }
    
        // Extract the nodes from the map in sorted order of their horizontal distances
        for (auto it : topNodes) {
            result.push_back(it.second);
        }
    
        return result;
    }
};

/*
*
* Dry Run
* Input: root = [1, 2, 3]
* * Initial Setup:
* Queue: [({Node 1}, 0)]
* Map topNodes: {}
* * Iteration 1:
* Pop: node = 1, hd = 0
* map doesn't contain hd=0. Add it: topNodes = {0: 1}
* node->left (2) exists: Push ({Node 2}, -1)
* node->right (3) exists: Push ({Node 3}, 1)
* Queue: [({Node 2}, -1), ({Node 3}, 1)]
* * Iteration 2:
* Pop: node = 2, hd = -1
* map doesn't contain hd=-1. Add it: topNodes = {-1: 2, 0: 1}
* No children for Node 2.
* Queue: [({Node 3}, 1)]
* * Iteration 3:
* Pop: node = 3, hd = 1
* map doesn't contain hd=1. Add it: topNodes = {-1: 2, 0: 1, 1: 3}
* No children for Node 3.
* Queue: [] (Empty)
* * Final Result Generation:
* Extract from map in sorted order of keys (-1, 0, 1) -> Values: [2, 1, 3]
* Output: [2, 1, 3]
*
*/

```

---

## 🧠 Key Insights

* **Why BFS over DFS?** In DFS, you might reach a lower node at a specific horizontal distance before reaching a higher node at the same distance (e.g., exploring deeply down the right side of a left subtree). BFS guarantees you always discover the topmost nodes first due to its level-by-level traversal.
* **Horizontal Distance (HD):** We treat the root as the center point (0). Moving left decreases the HD by 1, and moving right increases it by 1.
* **Automatic Sorting:** Using `std::map` inherently keeps our horizontal distances ordered from the minimum (leftmost) to maximum (rightmost), avoiding the need for an explicit sorting step at the end.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also want to try:

* **Bottom View of Binary Tree**: Instead of capturing the *first* node seen at each horizontal distance, capture the *last* node seen.
* **Left/Right View of Binary Tree**: Print the first/last node seen at each vertical level (depth) rather than horizontal distance.
* **Vertical Order Traversal**: Print *all* nodes clustered by their horizontal distance.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Top View of Binary Tree](https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1)
* **Concept Reference:** [Breadth-First Search in Trees](https://www.geeksforgeeks.org/level-order-tree-traversal/)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BinaryTree` `#TreeTraversal` `#BFS` `#DataStructures` `#GeeksforGeeks` `#CPP`