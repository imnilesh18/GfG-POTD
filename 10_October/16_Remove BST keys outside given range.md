# 🌲 Remove BST keys outside given range

<p align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-61.5%25-brightgreen?style=for-the-badge" alt="Accuracy: 61.5%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-purple?style=for-the-badge" alt="License: MIT" />
</p>

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/remove-bst-keys-outside-given-range/1).

---

## 📝 Problem Statement

Given the `root` of a Binary Search Tree (BST) and two integers `l` and `r`, your task is to **remove all the nodes** whose values lie outside the range `[l, r]`.

**Note**: The modified tree should also be a valid BST.

---

## 🧪 Examples

### Example 1

```
Input:
root = [6, -13, 14, N, -8, 13, 15, N, N, 7]
l = -10
r = 13

Output: [6, -8, 13, N, N, 7]
```
**Explanation:** All nodes with values outside the range `[-10, 13]` (i.e., -13, 14, and 15) are removed, and the remaining tree is a valid BST.

<details>
<summary><b>📖 Example Breakdown</b></summary>
<div align="center">

Let's trace the first example: `root = [6, -13, 14, ...], l = -10, r = 13`.

1.  **Start at Root (6):**
    * The value `6` is within the range `[-10, 13]`.
    * We recursively call `removekeys` on its left child `(-13)` and right child `(14)`.

2.  **Process Left Subtree (Root -13):**
    * Call `removekeys` on node `-13`. Its value is less than `l = -10`.
    * According to the BST property, any left children of `-13` would also be less than `-10`.
    * The function will return the result of processing the *right* subtree of `-13`, which is `-8`.

3.  **Process Node (-8):**
    * The value `-8` is within `[-10, 13]`.
    * Recursively process its children (both `null`). They return `null`.
    * Node `-8` is kept. It returns itself.

4.  **Return to Root (6)'s Left:**
    * The call for the left child `(-13)` returns the processed right subtree, which is the node `-8`.
    * So, `root (6)`'s new left child becomes `-8`.

5.  **Process Right Subtree (Root 14):**
    * Call `removekeys` on node `14`. Its value is greater than `r = 13`.
    * According to the BST property, any right children of `14` would also be greater than `13`.
    * The function will return the result of processing the *left* subtree of `14`, which is `13`.

6.  **Process Node (13):**
    * The value `13` is within `[-10, 13]`.
    * Its left child `(7)` is processed. `7` is in range and its children are null, so it returns itself.
    * Its right child is `null`.
    * Node `13` is kept, with its updated left child `(7)`. It returns itself.

7.  **Return to Root (6)'s Right:**
    * The call for the right child `(14)` returns the processed left subtree, which is the node `13`.
    * So, `root (6)`'s new right child becomes `13`.

8.  **Final Tree:**
    * The root `(6)` is returned with its updated left pointer pointing to `-8` and its right pointer pointing to `13`. The final structure is `[6, -8, 13, N, N, 7]`.

</div>
</details>

### Example 2

```
Input:
root = [14, 4, 16, 2, 8, 15, N, -8, 3, 7, 10]
l = 2
r = 6

Output: [4, 2, N, N, 3]
```
**Explanation:** After removing nodes outside `[2, 6]`, the resulting BST is `[4, 2, N, N, 3]`.

---

## ⛓️ Constraints

> ```
> 1 ≤ number of nodes ≤ 10^4
> 1 ≤ node->data ≤ 10^4
> 1 ≤ l ≤ r ≤ 10^4
> ```

---

## 💡 Solution Approach

### Optimized Recursive Approach

The problem can be efficiently solved using a recursive post-order traversal. We first process the left and right subtrees and then decide what to do with the current node based on its value relative to the range `[l, r]`.

```cpp
// Intuition:
// The core idea is to use a post-order traversal. By processing the children first,
// we can decide what to do with the current node after its subtrees are already valid.
// This allows us to "bubble up" the correct subtree to be linked to the parent.

// Approach:
// 1. Base Case: If the root is null, return null.
// 2. Recursively call the function for the left and right children to update the subtrees first.
// 3. Check the current node's value:
//    a. If `root->data` is within the range [l, r], it's a valid node. Keep it and return the root itself.
//    b. If `root->data` is less than `l`, the current node and its entire left subtree are invalid.
//       We only need to consider its right subtree, so we return the (already processed) right child.
//    c. If `root->data` is greater than `r`, the current node and its entire right subtree are invalid.
//       We only need to consider its left subtree, so we return the (already processed) left child.

// Time Complexity: O(N)
// We visit each node in the tree exactly once.

// Space Complexity: O(H)
// Where H is the height of the tree, due to the recursion stack. In the worst case (a skewed tree), this can be O(N).

class Solution {
  public:
    Node* removekeys(Node* root, int l, int r) {
        // Base case: if the node is null, there's nothing to do.
        if (root == nullptr) return nullptr;

        // Recursively trim the left and right subtrees first (post-order traversal).
        root->left = removekeys(root->left, l, r);
        root->right = removekeys(root->right, l ,r);

        // Now, process the current node after its children have been processed.
        
        // Case 1: The current node's data is within the valid range [l, r].
        if (root->data >= l && root->data <= r) {
            // Keep the current node and return it. Its children are already trimmed.
            return root;
        }
        
        // Case 2: The current node's data is less than the lower bound 'l'.
        else if (root->data < l) {
            // This node and its entire left subtree are invalid.
            // Return the trimmed right subtree to be linked to the parent.
            return root->right;
        }
        
        // Case 3: The current node's data is greater than the upper bound 'r'.
        else {
            // This node and its entire right subtree are invalid.
            // Return the trimmed left subtree to be linked to the parent.
            return root->left;
        }
    }
};

/*
*
* Dry Run
* Input: root = [6, -13, 14, N, -8, 13, 15, N, N, 7], l = -10, r = 13
*
* 1. removekeys(6, -10, 13)
* - Calls removekeys(-13, -10, 13)
* - Calls removekeys(null, -10, 13) -> returns null
* - Calls removekeys(-8, -10, 13)
* - Calls removekeys(null, -10, 13) -> returns null
* - Calls removekeys(7, -10, 13)
* - Calls for children -> returns null
* - 7 is in range, returns node 7.
* - -8's right child becomes 7.
* - -8 is in range, returns node -8.
* - -13 is less than `l` (-10), so it returns its processed right child (node -8).
* - root->left becomes node -8.
* - Calls removekeys(14, -10, 13)
* - Calls removekeys(13, -10, 13)
* - Calls removekeys(7, -10, 13) -> returns node 7 (from previous step, but let's assume it was connected here)
* - 13's left becomes 7.
* - 13 is in range, returns node 13.
* - Calls removekeys(15, -10, 13) -> returns its left child (null).
* - 14 is greater than `r` (13), so it returns its processed left child (node 13).
* - root->right becomes node 13.
* - 6 is in range, returns root (node 6).
*
* Final Tree: Root 6 -> left is -8, right is 13. Node 13 -> left is 7.
* Resulting tree: [6, -8, 13, N, N, 7]
*
*/
```

---

## 🚀 Key Insights

* **Post-Order Traversal is Key**: By fixing the children (`left` and `right` subtrees) before making a decision about the current `root`, we ensure that when we re-link subtrees, those subtrees are already valid.
* **Leveraging BST Properties**: The solution efficiently prunes entire subtrees. If a node's value is less than `l`, we know its entire left subtree must also be out of range. Similarly, if a node's value is greater than `r`, its entire right subtree is also out of range. This avoids unnecessary traversal.

---

## 🧭 Further Exploration

- [Check for BST](https://www.geeksforgeeks.org/problems/check-for-bst/1)
- [Find the Closest Element in BST](https://www.geeksforgeeks.org/problems/find-the-closest-element-in-bst/1)
- [Inorder Successor in BST](https://www.geeksforgeeks.org/problems/inorder-successor-in-bst/1)
- [Delete a node from BST](https://www.geeksforgeeks.org/problems/delete-a-node-from-bst/1)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/remove-bst-keys-outside-given-range/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`binary-search-tree` `recursion` `tree` `data-structures` `geeksforgeeks`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions in this repository are for educational and reference purposes. We encourage you to try solving the problems on your own first to maximize your learning.