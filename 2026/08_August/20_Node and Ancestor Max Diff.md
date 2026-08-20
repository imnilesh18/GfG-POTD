# 🌳 Maximum Difference Between Node and its Ancestor

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-34.95%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the root of a binary tree, find the maximum difference between an ancestor node `A` and its descendant node `B`, i.e., maximize `A - B`.

---

## 💡 Examples

### Example 1
```text
Input: root[] = [5, 2, 1] 

    5
   / \
  2   1

Output: 4
Explanation: The maximum difference we can get is 4, which is between 5 and 1 (5 - 1 = 4).
```

### Example 2
```text
Input: root[] = [1, 2, 3, N, N, N, 7] 

      1
     / \
    2   3
         \
          7

Output: -1
Explanation: The maximum difference we can get is -1, which is between 1 and 2 (1 - 2 = -1).
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>
<br>

1. **Leaf nodes (2, 1)** return their own values to the parent.
2. **Root node (5)** receives minimum values from its left (2) and right (1) subtrees.
3. The overall minimum in subtrees is `1`.
4. Difference calculation: `Root value - Minimum from subtrees` = `5 - 1 = 4`.
5. Max difference is updated to `4`.
</details>

---

## ⚙️ Constraints

* $2 \le$ number of nodes in root $\le 10^4$
* $0 \le$ `root.node->data` $\le 10^5$
* $2 \le$ Number of edges $\le 10^4$

---

## 🧠 Solution Approach

### Optimized Bottom-Up Approach (Post-order Traversal)
To maximize `A - B`, for every node `A`, we need the smallest possible node `B` in its subtrees. By traversing the tree from the bottom up, each node can calculate the minimum value in its subtree and pass it up to its parent.

```cpp
// Intuition: To maximize the difference (Ancestor - Descendant), we need to subtract the smallest possible descendant value from the current ancestor node. A bottom-up approach allows each subtree to return its minimum value up the tree.
// Approach: Traverse the tree using post-order (bottom-up). For each node, find the minimum value from its left and right subtrees. Calculate the difference between the current node's data and this minimum, updating the global max difference if necessary. Finally, return the minimum of the current node's data and the subtree's minimum to the parent.
// Time Complexity: O(n) because we visit every node in the binary tree exactly once.
// Space Complexity: O(n) auxiliary space in the worst case (skewed tree) due to the recursion stack. For a balanced tree, it would be O(log n).

/* Structure of Binary Tree Node
class Node {
  public:
    int data;
    Node *left;
    Node *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};*/

class Solution {
  public:
  int maxDiffUtil(Node *t, int *res) {
      // Return MAX_INT if null so it doesn't affect min() calculations
      if (t == nullptr)
          return INT_MAX;

      // Leaf node: return its own data as it has no descendants
      if (t->left == nullptr && t->right == nullptr)
          return t->data;

      // Post-order: get minimum value from left and right subtrees
      int val = min(maxDiffUtil(t->left, res), maxDiffUtil(t->right, res));

      // Update max difference: current node data - min subtree value
      *res = max(*res, t->data - val);

      // Return the absolute minimum found so far in this subtree
      return min(val, t->data);
  }

  // Function to return the maximum difference 
  // between any node and its ancestor.
  int maxDiff(Node *root) {
      // Initialize with minimum possible integer
      int res = INT_MIN; 
      // Pass reference to keep track of maximum difference found
      maxDiffUtil(root, &res); 
      return res;
  }
};

/*
*
* Dry Run
* Input: root = [5, 2, 1]
* Initial Call: maxDiff(root=5), res = INT_MIN
* 
* maxDiffUtil(5, &res):
*   left = maxDiffUtil(2, &res):
*     Node 2 is leaf -> returns 2
*   right = maxDiffUtil(1, &res):
*     Node 1 is leaf -> returns 1
* 
*   val = min(2, 1) = 1
*   res = max(INT_MIN, 5 - 1) = max(INT_MIN, 4) = 4
*   returns min(1, 5) = 1
* 
* Final Result: res = 4
*
*/
```

---

## 🔑 Key Insights
* **Bottom-Up Efficiency:** Instead of checking every node against every descendant ($O(N^2)$), pushing the minimum value upwards reduces the problem to a single pass ($O(N)$).
* **Base Case Handling:** Returning `INT_MAX` for null nodes ensures that missing children do not falsely influence the `min()` comparisons.

---

## 🔎 Further Exploration
* **Related Problems:**
  * Maximum Path Sum in a Binary Tree
  * Lowest Common Ancestor (LCA) in a Binary Tree
  * Diameter of a Binary Tree

---

## 🔗 References
* **Original GFG Problem:** [Maximum difference between node and its ancestor](https://www.geeksforgeeks.org/problems/maximum-difference-between-node-and-its-ancestor/1)

---

## 👨‍💻 Author
**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)
