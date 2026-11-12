# 🌳 Closest in BST

<div align="center">
  
  ![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
  ![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
  ![Accuracy](https://img.shields.io/badge/Accuracy-47.51%25-green?style=for-the-badge)
  ![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
  ![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the root of a Binary Search Tree (BST) and an integer `k`, find the minimum absolute difference between `k` and the value of any node in the BST.[cite: 1]

### 💡 Constraints

> - $1 \le \text{size of binary tree, } k \le 10^5$[cite: 1]
> - $0 \le \text{Node.data} \le 10^5$[cite: 1]

---

## 🔍 Examples

**Example 1:**

```text
Input: root = [10, 2, 11, 1, 5, N, N, N, N, 3, 6, N, 4], k = 13
Output: 2
Explanation: The node with value 11 is closest to k = 13. So, the minimum absolute difference is |11 - 13| = 2.[cite: 1]
```

**Example 2:**

```text
Input: root = [8, 1, 9, N, 4, N, 10, 3], k = 9
Output: 0
Explanation: The node with value 9 is closest to k = 9. So, the minimum absolute difference is |9 - 9| = 0.[cite: 1]
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>

1. **Target `k` = 13**. Start at the root node `10`.
2. Absolute difference $|10 - 13| = 3$. Current minimum difference is `3`.
3. Since `13 > 10`, we know any closer elements must be in the right subtree. Move right to node `11`.
4. Absolute difference $|11 - 13| = 2$. Current minimum difference updates to `2`.
5. Since `13 > 11`, move right. The right child is `NULL`.
6. Traversal ends. The minimum difference found is `2`.
</details>

---

## 🚀 Solution Approach

### Recursive DFS Traversal

**Intuition:** 
Instead of traversing every node in the tree (which would take $O(n)$ time), we can leverage the core property of a Binary Search Tree: left children are smaller, and right children are larger. By comparing the target `k` to the current node, we can dynamically prune half of the tree at each step, significantly optimizing our search path to quickly hone in on the closest value.

```cpp
// Intuition: We can leverage the properties of a Binary Search Tree (BST) to efficiently find the closest element. Since left children are smaller and right children are larger, we can narrow down our search path rather than checking every node.
// Approach:
// 1. Initialize `ans` with INT_MAX to track the minimum difference.
// 2. Traverse the tree. At each node, update `ans` with the minimum of current `ans` and the absolute difference between the node's data and `k`.
// 3. If the node's data perfectly matches `k`, the difference is 0, so we return immediately.
// 4. If `k` is smaller than the node's data, search the left subtree. Otherwise, search the right subtree.
// Time Complexity: O(h), where h is the height of the BST. We travel down a single path from root to leaf.[cite: 1]
// Space Complexity: O(h), auxiliary stack space used by the recursive calls.[cite: 1]

class Solution {
  public:
    void solve(Node* root, int k, int& ans) {
        // Base case: if node is null, reach end of path
        if (!root) return;

        // Update the minimum absolute difference found so far
        ans = min(ans, abs(root->data - k));

        // If exact match found, minimum difference is 0 (optimal)
        if (root->data == k) {
            return;
        } 
        // If k is smaller, closest value must lie in left subtree
        else if (k < root->data) {
            solve(root->left, k, ans);
        } 
        // If k is larger, closest value must lie in right subtree
        else {
            solve(root->right, k, ans);
        }
    }

    int minDiff(Node *root, int k) {
        int ans = INT_MAX;
        solve(root, k, ans);
        return ans;
    }
};

/*
*
* Dry Run
* Input: root = [8, 1, 9, N, 4, N, 10, 3], k = 9
* ans = INT_MAX
* 1. Node(8): abs(8-9) = 1 -> ans = 1. k(9) > 8, go right.
* 2. Node(9): abs(9-9) = 0 -> ans = 0. root->data == k, return.
* Output: 0
*
*/
```

---

## 🧠 Key Insights
- **Pruning the Search Space:** The standard difference computation takes $O(n)$, but the BST structure allows us to discard an entire subtree at each node comparison. If the target `k` is smaller than the current node, exploring the right subtree is futile because all values there will only increase the gap.
- **Early Exit:** Encountering a node where `root->data == k` immediately yields a difference of `0`. This is the mathematical minimum for absolute difference, meaning we can instantly terminate the recursion and save CPU cycles.

---

## 🔗 Further Exploration
- **Related Problem:** Search in a Binary Search Tree
- **Related Problem:** Inorder Successor in BST
- **Related Problem:** Kth Smallest Element in a BST

---

## 📚 References
- **GeeksforGeeks Problem:** [Find the Closest Element in BST](https://www.geeksforgeeks.org/problems/find-the-closest-element-in-bst/1)[cite: 1]

---

## 👨‍💻 Author
**Nilesh Kumar**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
- `#Binary Search Tree`[cite: 1]
- `#Tree`[cite: 1]
- `#C++`
- `#GeeksforGeeks`
- `#Data Structures`