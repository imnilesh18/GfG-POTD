# 🌲 Vertical Tree Traversal

<div align="center">
  
[![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/print-a-binary-tree-in-vertical-order/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy: 32.87%](https://img.shields.io/badge/Accuracy-32.87%25-green?style=for-the-badge)]()
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statements and test cases are based on the GeeksforGeeks platform.

---

## 📜 Problem Statement

Given the root of a Binary Tree, find the **vertical traversal** of the tree starting from the leftmost level to the rightmost level.

**Note:** If there are multiple nodes passing through a vertical line, then they should be printed as they appear in level order traversal of the tree.

---

## 💡 Examples

### Example 1
```text
Input: root = [1, 2, 3, 4, 5, 6, 7, N, N, N, 8, N, 9, N, 10, 11, N]
Output: [[4], [2], [1, 5, 6, 11], [3, 8, 9], [7], [10]]
Explanation: 
The output groups the nodes based on their horizontal distances from the leftmost vertical line to the rightmost vertical line. Nodes on the same vertical line appear together in level order.
```

### Example 2
```text
Input: root = [1, 2, 3, 4, 5, N, 6]
Output: [[4], [2], [1, 5], [3], [6]]
Explanation: 
From left to right the vertical order will be [[4], [2], [1, 5], [3], [6]].
```

<details>
<summary>📖 Example Breakdown (Example 2)</summary>

1. **Root `1`**: Horizontal Distance (HD) = 0.
2. **Left child `2`**: HD = 0 - 1 = -1.
3. **Right child `3`**: HD = 0 + 1 = 1.
4. **Left child of `2` (`4`)**: HD = -1 - 1 = -2.
5. **Right child of `2` (`5`)**: HD = -1 + 1 = 0.
6. **Right child of `3` (`6`)**: HD = 1 + 1 = 2.

Grouping nodes by their HDs in ascending order:
- **HD = -2**: `[4]`
- **HD = -1**: `[2]`
- **HD = 0**: `[1, 5]` (Level order maintained: `1` was visited before `5`)
- **HD = 1**: `[3]`
- **HD = 2**: `[6]`

Final Output: `[[4], [2], [1, 5], [3], [6]]`
</details>

---

## ⚠️ Constraints

> - `1 ≤ number of nodes ≤ 10^5`
> - `1 ≤ node->data ≤ 10^5`

---

## 🛠️ Solution Approach

### Level Order Traversal with Horizontal Distance Tracking (Optimized BFS)

```cpp
// Intuition: We need to group nodes based on their horizontal distance from the root. A level-order traversal (BFS) ensures that nodes appearing higher in the tree are processed first, which naturally handles the vertical order requirement.
// Approach: We use a queue to perform BFS, storing pairs of the node and its horizontal distance. We maintain an unordered_map to store lists of node values for each horizontal distance. To avoid sorting map keys, we track the minimum and maximum horizontal distances seen during the traversal. Finally, we iterate from the minimum to maximum distance to collect grouped nodes.
// Time Complexity: O(N), where N is the number of nodes. Each node is processed exactly once, and unordered_map operations take O(1) time on average.
// Space Complexity: O(N) for storing the nodes in the queue during BFS and grouping them in the unordered_map.

class Solution {
  public:
    vector<vector<int>> verticalOrder(Node *root) {
        
        // Map to store lists of nodes for each horizontal distance
        unordered_map<int, vector<int>> mp;
        
        // Create a queue for level order traversal: pair<Node*, Horizontal_Distance>
        queue<pair<Node*, int>> q;
        q.push({ root, 0 });

        // mn and mx contain the minimum and maximum horizontal distance from root
        int mn = 0, mx = 0;
        
        while (!q.empty()) {

            // Pop from queue front
            pair<Node*, int> curr = q.front();
            q.pop();

            Node* node = curr.first;
            int hd = curr.second;

            // Insert this node's data in the array of the 'hd' level in map
            mp[hd].push_back(node->data);

            // If left child exists, push it with hd - 1
            if (node->left)
                q.push({ node->left, hd - 1 });
                
            // If right child exists, push it with hd + 1
            if (node->right)
                q.push({ node->right, hd + 1 });

            // Update mn and mx boundary values
            mn = min(mn, hd);
            mx = max(mx, hd);
        }
  
        vector<vector<int>> res;
  
        // Traverse the map from minimum to maximum horizontal distance (hd)
        for (int i = mn; i <= mx; i++) {
            res.push_back(mp[i]);
        }
        
        return res;
    }   
};

/*
*
* Dry Run
*
* Input: root = [1, 2, 3, 4, 5, N, 6]
* * Initial State:
* q = [(Node(1), 0)], mp = {}, mn = 0, mx = 0
* * Step 1:
* Pop (Node(1), 0). hd = 0.
* mp[0] = [1]
* Push children: q = [(Node(2), -1), (Node(3), 1)]
* mn = 0, mx = 0
* * Step 2:
* Pop (Node(2), -1). hd = -1.
* mp[-1] = [2]
* Push children: q = [(Node(3), 1), (Node(4), -2), (Node(5), 0)]
* mn = -1, mx = 0
* * Step 3:
* Pop (Node(3), 1). hd = 1.
* mp[1] = [3]
* Push right child: q = [(Node(4), -2), (Node(5), 0), (Node(6), 2)]
* mn = -1, mx = 1
* * Step 4:
* Pop (Node(4), -2). hd = -2.
* mp[-2] = [4]
* No children. q = [(Node(5), 0), (Node(6), 2)]
* mn = -2, mx = 1
* * Step 5:
* Pop (Node(5), 0). hd = 0.
* mp[0] = [1, 5]
* No children. q = [(Node(6), 2)]
* mn = -2, mx = 1
* * Step 6:
* Pop (Node(6), 2). hd = 2.
* mp[2] = [6]
* No children. q = []
* mn = -2, mx = 2
* * End Traversal.
* * Build Result (from i = -2 to i = 2):
* i = -2 => res.push_back([4])
* i = -1 => res.push_back([2])
* i = 0  => res.push_back([1, 5])
* i = 1  => res.push_back([3])
* i = 2  => res.push_back([6])
* * Output: [[4], [2], [1, 5], [3], [6]]
*/
```

---

## 🧠 Key Insights

1. **Breadth-First Search (BFS) Advantage:** BFS ensures that when multiple nodes lie on the same vertical line, the ones closer to the root (higher up in the tree) are encountered and inserted first, preserving the level-order constraint.
2. **`unordered_map` over `map`:** While a standard `map` natively sorts keys, it incurs an $O(\log K)$ overhead for insertions. Using an `unordered_map` brings insertion down to $O(1)$. By manually tracking the `min` and `max` horizontal distance variables (`mn` and `mx`), we can iterate through the map in sorted order sequentially without the cost of logarithmic operations.

---

## 🔍 Further Exploration

- **Bottom View of Binary Tree**: A variation where only the last node seen at each horizontal distance is kept.
- **Top View of Binary Tree**: Similar to vertical traversal, but keeping only the first node encountered for each horizontal distance.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Vertical Tree Traversal](https://www.geeksforgeeks.org/problems/print-a-binary-tree-in-vertical-order/1)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BinaryTree` `#TreeTraversal` `#DataStructures` `#Queue` `#Hashing` `#GeeksforGeeks`