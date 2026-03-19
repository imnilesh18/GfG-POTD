# 🌳 Largest BST

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-29.73%25-brightgreen?style=for-the-badge" alt="Accuracy: 29.73%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

You're given a binary tree. Your task is to find the **size** of the largest subtree within this binary tree that also satisfies the properties of a **Binary Search Tree (BST)**. The size of a subtree is defined as the number of nodes it contains.

> **Note:** A subtree of the binary tree is considered a BST if for every node in that subtree, the left child is less than the node, and the right child is greater than the node, without any duplicate values in the subtree.

---

## 💡 Examples

### Example 1
```text
Input: root = [5, 2, 4, 1, 3]
Output: 3
Explanation: The sub-tree rooted at node 2 is a BST of size 3 (Nodes: 2, 1, 3).
```

### Example 2
```text
Input: root = [6, 7, 3, N, 2, 2, 4]
Output: 3
Explanation: The sub-tree rooted at node 3 is a BST of size 3 (Nodes: 3, 2, 4).
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's break down **Example 1**:  
Tree Structure:
```text
       5
     /   \
    2     4
   / \
  1   3
```

1. **Leaf Node 1**: It's a valid BST of size `1`.
2. **Leaf Node 3**: It's a valid BST of size `1`.
3. **Node 2**: Its left child (1) < 2 and right child (3) > 2. Since both subtrees are BSTs, the tree rooted at 2 is a valid BST of size `1 + 1 + 1 = 3`.
4. **Leaf Node 4**: It's a valid BST of size `1`.
5. **Root Node 5**: Left subtree's max is 3 (valid, since 3 < 5). Right subtree's min is 4 (invalid, since 4 is not > 5). Thus, the tree rooted at 5 is **not** a BST.
6. The maximum valid BST size found is **3**.

</details>

---

## ⚙️ Constraints

- `1 ≤ number of nodes ≤ 10^5`
- `1 ≤ node->data ≤ 10^5`

**Expected Complexities:**
- **Time Complexity:** `O(n)`
- **Auxiliary Space:** `O(h)`

---

## 🚀 Solution Approach

Below is the optimized solution to find the largest BST subtree using a bottom-up (post-order) traversal approach.

```cpp
// Intuition: To find the largest BST subtree, we can evaluate the tree from bottom to top (post-order). If both left and right subtrees are valid BSTs, and the current node's value is strictly greater than the maximum of the left subtree and strictly less than the minimum of the right subtree, then the current subtree is also a valid BST.
// Approach: Traverse the tree using post-order traversal. For each node, return a structure containing the minimum value, maximum value, and the size of the largest BST found so far. If the current node forms a valid BST, update the minimum, maximum, and size. Otherwise, pass up an invalid range to intentionally fail the parent's BST condition while propagating the maximum BST size found so far.
// Time Complexity: O(N) because we visit each node of the tree exactly once during the post-order traversal.
// Space Complexity: O(H) where H is the height of the tree, due to the recursion stack space.

/* Tree node structure used in the program
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

class Solution {
private:
    // 1. Properly encapsulated custom data type in a struct to store subtree info
    struct BSTInfo {
        int mini;
        int maxi;
        int mxSz;

        BSTInfo(int mn, int mx, int sz) {
            mini = mn;
            maxi = mx;
            mxSz = sz;
        }
    };

    // 2. Brought the recursive helper function inside the class to compute largest BST
    BSTInfo largestBSTBT(Node *root) {
        // Base case: An empty tree is a valid BST of size 0
        if (!root)
            return BSTInfo(INT_MAX, INT_MIN, 0);

        // Post-order traversal: compute for left and right subtrees first
        BSTInfo left = largestBSTBT(root->left);
        BSTInfo right = largestBSTBT(root->right);

        // Check if the current subtree is a valid BST
        if (left.maxi < root->data && right.mini > root->data) {
            // It is a valid BST, so return the updated range and size
            return BSTInfo(min(left.mini, root->data), 
                           max(right.maxi, root->data), 
                           1 + left.mxSz + right.mxSz);
        }

        // If it's not a BST, return values that will intentionally fail the parent's BST check
        // Pass INT_MIN as minimum and INT_MAX as maximum, but keep the maximum size found
        return BSTInfo(INT_MIN, INT_MAX, max(left.mxSz, right.mxSz));
    }

public:
    /* You are required to complete this method */
    // 3. Added the main wrapper function expected by the platform
    int largestBst(Node *root) {
        return largestBSTBT(root).mxSz;
    }
};

/*

Dry Run:
Input: root = [5, 2, 4, 1, 3]
Tree Structure:
       5
     /   \
    2     4
   / \
  1   3

1. Node 1 (Leaf):
   left = {INT_MAX, INT_MIN, 0}, right = {INT_MAX, INT_MIN, 0}
   Condition (left.maxi < 1 && right.mini > 1) -> (INT_MIN < 1 && INT_MAX > 1) is True.
   Returns: {1, 1, 1}

2. Node 3 (Leaf):
   left = {INT_MAX, INT_MIN, 0}, right = {INT_MAX, INT_MIN, 0}
   Condition (left.maxi < 3 && right.mini > 3) is True.
   Returns: {3, 3, 1}

3. Node 2:
   left = {1, 1, 1}, right = {3, 3, 1}
   Condition (left.maxi < 2 && right.mini > 2) -> (1 < 2 && 3 > 2) is True.
   Returns: {1, 3, 3}

4. Node 4 (Leaf):
   left = {INT_MAX, INT_MIN, 0}, right = {INT_MAX, INT_MIN, 0}
   Condition (left.maxi < 4 && right.mini > 4) is True.
   Returns: {4, 4, 1}

5. Node 5 (Root):
   left = {1, 3, 3}, right = {4, 4, 1}
   Condition (left.maxi < 5 && right.mini > 5) -> (3 < 5 && 4 > 5) is False!
   Returns: {INT_MIN, INT_MAX, max(3, 1)} -> {INT_MIN, INT_MAX, 3}

Final Answer is 3.

*/
```

---

## 🔑 Key Insights

- **Bottom-Up Traversal:** By using post-order traversal, we gather information about the left and right subtrees before making a decision on the parent node. This prevents recalculating the validity of subtrees multiple times.
- **Custom Data Structure:** Returning multiple values from the recursive call (minimum value, maximum value, and the largest BST size) using a `struct` makes the state management remarkably clean.
- **Intentional Sabotage:** If a subtree is determined to *not* be a valid BST, returning `INT_MIN` for the min and `INT_MAX` for the max ensures that any parent node checking the `left.maxi < root->data && right.mini > root->data` condition will definitively fail, maintaining correctness up the tree.

---

## 🌍 Further Exploration

If you enjoyed solving this, try these related tree problems:
- [Check for BST](https://www.geeksforgeeks.org/problems/check-for-bst/1)
- [Merge two BSTs](https://www.geeksforgeeks.org/problems/merge-two-bst-s/1)
- [Fix two nodes of a BST](https://www.geeksforgeeks.org/problems/fixed-two-nodes-of-a-bst/1)

---

## 🔗 References

- **Original Problem:** [Largest BST on GeeksforGeeks](https://www.geeksforgeeks.org/problems/largest-bst/1)
- **Topic Reference:** [Binary Search Tree Properties](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

- `Binary Search Tree`
- `Tree`
- `Data Structures`
- `Depth First Search`
- `GeeksforGeeks`