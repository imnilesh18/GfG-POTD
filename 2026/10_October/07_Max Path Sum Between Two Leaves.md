# 🌳 Max Path Sum Between Two Leaves

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)  ![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)  ![Accuracy](https://img.shields.io/badge/Accuracy-18.39%25-blue?style=for-the-badge)  ![Points](https://img.shields.io/badge/Points-8-orange?style=for-the-badge)  ![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Given the root of a binary tree, where each node contains an integer value, find the maximum possible path sum between any two leaf nodes.  If the tree has fewer than two leaf nodes, return `-1`. 

---

## 💡 Examples

<details>
<summary>📖 <b>Example Breakdown (Click to Expand)</b></summary>

```text
Input: root = [3, 4, 5, -10, 4, N, N]
Output: 16

Explanation: 
The leaf nodes are -10, 4 (right child of 4), and 5. 
Possible paths between leaf nodes are: 
-10 -> 4 -> 3 -> 5 = -10 + 4 + 3 + 5 = 2 
-10 -> 4 -> 4 = -10 + 4 + 4 = -2 
4 -> 4 -> 3 -> 5 = 4 + 4 + 3 + 5 = 16 
Hence, the maximum path sum is obtained from the path 4 -> 4 -> 3 -> 5, giving 16. 
```
</details>

```text
Input: root = [-15, 5, 6, -8, 1, 3, 9, 2, -3, N, N, N, N, N, 0, N, N, N, N, 4, -1, N, N, 10]
Output: 27
Explanation: The maximum path sum is obtained from the path 3 -> 6 -> 9 -> 0 -> -1 -> 10, giving 27. 
```

```text
Input: root = [3, 4, 1, -10, 4, N, N]
Output: 12
Explanation: The maximum path sum is obtained from the path 4 -> 4 -> 3 -> 1, giving 12. 
```

---

## ⚙️ Constraints

* $0 \leq \text{size of binary tree} \leq 10^4$ 
* $-10^3 \leq \text{node.data} \leq 10^3$ 

**Expected Complexities:**
* **Time Complexity:** $O(n)$ 
* **Auxiliary Space:** $O(n)$ 

---

## 🚀 Solution Approach

### Optimized DFS (Post-order Traversal)

The core idea is to find an inverted "V" path where the peak is an ancestor node, and the two ends are distinct leaf nodes. By using Depth First Search (DFS), we can evaluate the tree in a post-order manner. At any given node, if both the left and right children exist, this node can serve as the peak. We update our global maximum sum using the best paths coming up from the left and right subtrees. The recursive function then returns the maximum single path extending downwards to feed to its own parent.

```cpp
// Intuition: We need the maximum path connecting two distinct leaves. By using a post-order DFS, we can evaluate each node as a potential "turning point" (lowest common ancestor) for the path connecting its left subtree's maximum leaf-path and right subtree's maximum leaf-path.
// Approach: 
// 1. Run DFS. If the node is a leaf, return its data value.
// 2. If a node has only one child, the path must strictly pass through that existing child to reach a leaf.
// 3. If a node has both left and right children, it's a valid peak. Calculate the local path sum (`left_sum + right_sum + root->data`) and update the global `max_sum` if it's larger.
// 4. Return `max(left_sum, right_sum) + root->data` to the parent so the path can continue upwards.
// Time Complexity: O(n) - The DFS traversal visits every node exactly once .
// Space Complexity: O(n) - The recursive call stack can grow up to O(n) in a skewed tree, and O(log n) for a balanced tree .

class Solution {
private:
    // Helper function to perform DFS and calculate path sums
    int dfs(Node* root, int& max_sum) {
        // Base case: null node
        if (!root) return 0;

        // If it's a leaf node, return its value
        if (!root->left && !root->right) {
            return root->data;
        }

        // If left child is missing, the path MUST go through the right subtree
        if (!root->left) {
            return dfs(root->right, max_sum) + root->data;
        }

        // If right child is missing, the path MUST go through the left subtree
        if (!root->right) {
            return dfs(root->left, max_sum) + root->data;
        }

        // If both children exist, we have a valid turning point for two leaves
        int left_sum = dfs(root->left, max_sum);
        int right_sum = dfs(root->right, max_sum);

        // Update the global maximum path sum between two leaves
        max_sum = std::max(max_sum, left_sum + right_sum + root->data);

        // Return the max path extending downwards from this node
        return std::max(left_sum, right_sum) + root->data;
    }

public:
    int maxPathSum(Node* root) {
        int max_sum = INT_MIN; 

        dfs(root, max_sum);

        // If max_sum was never updated, the tree has fewer than 2 leaves.
        if (max_sum == INT_MIN) {
            return -1;
        }

        return max_sum;
    }
};

/*
* Dry Run
* Input: root = [3, 4, 5, -10, 4, N, N]
* 1. Start DFS at root 3.
* 2. Traverse left to 4. Traverse left to -10 (leaf). Returns -10.
* 3. From 4, traverse right to 4 (leaf). Returns 4.
* 4. Node 4 has both children. Updates max_sum = max(INT_MIN, -10 + 4 + 4) = -2.
*    Node 4 returns max(-10, 4) + 4 = 8 up to root 3.
* 5. From root 3, traverse right to 5 (leaf). Returns 5.
* 6. Node 3 has both children. Updates max_sum = max(-2, 8 + 5 + 3) = 16.
*    Node 3 returns max(8, 5) + 3 = 11 to the caller.
* 7. Final max_sum is 16.
*/
```

---

## 🧠 Key Insights

* **Strictly Leaf-to-Leaf constraint:** The problem specifically asks for a path between two *leaves*. This means a node with only one child cannot act as the turning point for the maximum sum path. We must recursively process only the available child to ensure the path correctly terminates at a leaf.
* **Pass-by-Reference State Management:** By using a single `int& max_sum` reference passed down through the DFS calls, we elegantly track the global maximum without needing class-level variables, which ensures thread-safety and a cleaner scope.

---

## 🔗 Further Exploration

* **Related Problem:** Binary Tree Maximum Path Sum (LeetCode Hard - Allows any node to any node, not just leaf to leaf)
* **Related Problem:** Diameter of Binary Tree (Finds the longest path by edges rather than values)

---

## 📚 References

* [Max Path Sum Between Two Leaves - GeeksforGeeks](https://www.geeksforgeeks.org/problems/maximum-path-sum/1) 

---

## 👨‍💻 Author

**Nilesh Kumar** | [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Tree](https://img.shields.io/badge/Tree-Topic-blue?style=for-the-badge) ![DFS](https://img.shields.io/badge/DFS-Algorithm-orange?style=for-the-badge) ![Binary Tree](https://img.shields.io/badge/Binary_Tree-Data_Structure-green?style=for-the-badge) ![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Platform-lightgrey?style=for-the-badge)