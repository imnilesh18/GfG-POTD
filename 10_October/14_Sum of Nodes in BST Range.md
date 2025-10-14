# 🌳 Sum of Nodes in BST Range

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-94.0%25-brightgreen.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/range-sum-of-bst/1).

---

## Problem Statement

Given the `root` of a Binary Search Tree and two integers `l` and `r`, the task is to find the **sum of all nodes** that lie between `l` and `r`, including both `l` and `r`.

### Constraints:

- `0 ≤ number of nodes ≤ 10^4`
- `0 ≤ node->data ≤ 10^4`
- `0 ≤ l ≤ r ≤ 10^4`

---

## examples

Here are a couple of examples to illustrate the problem:

### Example 1:

```
Input:
root = [22, 12, 30, 8, 20]
l = 10
r = 22

Output: 54
```

**Explanation:** The nodes in the given Tree that lie in the range `[10, 22]` are `{12, 20, 22}`. Therefore, the sum of nodes is `12 + 20 + 22 = 54`.

<details>
<summary>📖 Example Breakdown</summary>

Let's trace the execution with `root = [22, 12, 30, 8, 20]`, `l = 10`, `r = 22`.

1.  **Start at the root (22):**

    - Is `22` in the range `[10, 22]`? Yes.
    - Add `22` to our sum.
    - Since `22` is not less than `l` (10) and not greater than `r` (22), we must explore both left and right children.
    - `Sum = 22 + nodeSum(left_child, 10, 22) + nodeSum(right_child, 10, 22)`

2.  **Go to the left child (12):**

    - Is `12` in the range `[10, 22]`? Yes.
    - Add `12` to our sum.
    - We must explore both its children.
    - `Sum += 12 + nodeSum(left_child_of_12, 10, 22) + nodeSum(right_child_of_12, 10, 22)`

3.  **Go to the left child of 12 (8):**

    - Is `8` in the range `[10, 22]`? No (`8 < 10`).
    - Because this is a BST, we know no nodes in the left subtree of `8` can be in the range. We only need to check its right child.
    - The right child is `null`, so this path returns `0`.

4.  **Go to the right child of 12 (20):**

    - Is `20` in the range `[10, 22]`? Yes.
    - Add `20` to our sum.
    - Both its children are `null`, so this path returns `20`.

5.  **Back at node 12**, the total sum from its subtrees is `0 + 20 = 20`.

6.  **Go to the right child of the root (30):**

    - Is `30` in the range `[10, 22]`? No (`30 > 22`).
    - Because this is a BST, we know no nodes in the right subtree of `30` can be in the range. We only need to check its left child.
    - The left child is `null`, so this path returns `0`.

7.  **Final Calculation:**
    - From the root (22): `22`
    - From the left subtree (rooted at 12): `12 + 0 + 20 = 32`
    - From the right subtree (rooted at 30): `0`
    - Total Sum = `22 + 12 + 20 = 54`.

</details>

### Example 2:

```
Input:
root = [8, 5, 11, 3, 6, N, 20]
l = 11
r = 15

Output: 11
```

**Explanation:** The only node in the given Tree that lies in the range `[11, 15]` is `{11}`. Therefore, the sum is `11`.

---

## Solution Approach

The key insight is to leverage the properties of a **Binary Search Tree (BST)**. We can perform a traversal (like DFS) and prune branches that are guaranteed not to contain nodes within the `[l, r]` range.

### C++ Solution

```cpp
// Intuition: The problem asks for the sum of node values in a BST that fall within a given range [l, r].
// Since it's a BST, we can optimize the traversal. If a node's value is outside the range, we may not need to visit both of its subtrees.

// Approach: We use a recursive Depth-First Search (DFS) approach.
// 1. Base Case: If the current node is null, we return 0 as there's nothing to add.
// 2. Pruning (Optimization):
//    - If the current node's data is less than 'l', all nodes in its left subtree will also be less than 'l'. So, we only need to traverse the right subtree.
//    - If the current node's data is greater than 'r', all nodes in its right subtree will also be greater than 'r'. So, we only need to traverse the left subtree.
// 3. In-Range Case:
//    - If the current node's data is within the range [l, r], we must include its value in the sum. Then, we recursively explore both the left and right subtrees to find other valid nodes.
// The total sum is the current node's data plus the sum from the valid recursive calls.

// Time Complexity: O(N), where N is the number of nodes in the tree. In the worst case, we might need to visit every node if the range [l, r] includes all nodes.
// Space Complexity: O(H), where H is the height of the tree. This is due to the recursion stack. In a balanced tree, H = log(N). In a skewed tree, H = N.

/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};
*/

class Solution {
  public:
    int nodeSum(Node* root, int l, int r) {
        // Base case: if the node is null, there is no sum to add.
        if (root == nullptr) return 0;

        // If the current node's value is less than the lower bound 'l'.
        // We know all values in the left subtree are even smaller, so we only
        // need to explore the right subtree.
        if (root->data < l) {
            return nodeSum(root->right, l, r);
        }

        // If the current node's value is greater than the upper bound 'r'.
        // We know all values in the right subtree are even larger, so we only
        // need to explore the left subtree.
        else if (root->data > r) {
            return nodeSum(root->left, l, r);
        }

        // If the current node's value is within the range [l, r].
        // We add its value and recursively explore both left and right subtrees.
        int left = nodeSum(root->left, l, r);
        int right = nodeSum(root->right, l, r);

        // Return the sum of the current node's data and the sums from its children.
        return left + right + root->data;
    }
};

/*
*
* Dry Run
* Let's trace with root = [22, 12, 30, 8, 20], l = 10, r = 22
*
* nodeSum(22, 10, 22):
* - 22 is in [10, 22].
* - Returns nodeSum(12, 10, 22) + nodeSum(30, 10, 22) + 22
*
* nodeSum(12, 10, 22):
* - 12 is in [10, 22].
* - Returns nodeSum(8, 10, 22) + nodeSum(20, 10, 22) + 12
*
* nodeSum(8, 10, 22):
* - 8 < 10.
* - Returns nodeSum(null, 10, 22) -> returns 0.
*
* nodeSum(20, 10, 22):
* - 20 is in [10, 22].
* - Returns nodeSum(null, 10, 22) + nodeSum(null, 10, 22) + 20 -> returns 0 + 0 + 20 = 20.
*
* So, nodeSum(12, ...) returns 0 + 20 + 12 = 32.
*
* nodeSum(30, 10, 22):
* - 30 > 22.
* - Returns nodeSum(null, 10, 22) -> returns 0.
*
* Final result from nodeSum(22, ...) is 32 + 0 + 22 = 54.
*
*/
```

---

## 💡 Key Insights

- The primary optimization comes from the **pruning** of subtrees. By checking if a node's value is outside the `[l, r]` range, we can eliminate entire branches from the traversal, significantly improving performance over a simple traversal of a regular binary tree.
- This recursive solution elegantly performs a modified in-order traversal of the BST.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also like these related GFG challenges:

- [Lowest Common Ancestor in a BST](https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/)
- [Kth Smallest Element in a BST](https://www.geeksforgeeks.org/problems/find-k-th-smallest-element-in-bst/1)
- [Validate Binary Search Tree](https://www.geeksforgeeks.org/problems/check-for-bst/1)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Range Sum of BST](https://www.geeksforgeeks.org/problems/range-sum-of-bst/1)
- **Data Structure:** [Binary Search Tree (BST)](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Binary Search Tree](https://img.shields.io/badge/-Binary%20Search%20Tree-blue?style=for-the-badge)
![Tree](https://img.shields.io/badge/-Tree-green?style=for-the-badge)
![Recursion](https://img.shields.io/badge/-Recursion-orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks-lightgrey?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A strong reminder:** The solutions and code provided in this repository are for educational purposes only. They are meant to help you understand different problem-solving techniques and are not intended for direct submission or any unethical practices.
