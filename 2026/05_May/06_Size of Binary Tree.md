# 🌳 Size of Binary Tree

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/size-of-binary-tree/1)
[![Difficulty: Basic](https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge)]()
[![Accuracy: 82.91%](https://img.shields.io/badge/Accuracy-82.91%25-blue?style=for-the-badge)]()
[![Points: 1](https://img.shields.io/badge/Points-1-blueviolet?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the root of a binary tree, return the size of the tree. The size of a binary tree is the total number of nodes in the tree.

### 🛑 Constraints

> * `1 ≤ number of nodes ≤ 10^5`
> * `1 ≤ node->data ≤ 10^5`
> * **Expected Time Complexity:** `O(n)`
> * **Expected Auxiliary Space:** `O(h)`

---

## 💡 Examples

<details>
<summary>📖 Example Breakdown</summary>

**Input:**
```text
      1
    /   \
   2     3
```
**Output:**
```text
3
```
**Explanation:** 
There are exactly 3 nodes in the given binary tree (nodes 1, 2, and 3). Therefore, its size is 3.

</details>

**Example 2:**
```text
Input:
      10
     /  \
    5    9
   / \  / \
  1  2 3   4
  
Output: 7

Explanation: 
There are 7 nodes in the given binary tree, so its size is 7.
```

---

## 🚀 Solution Approaches

### Recursive Depth-First Search (DFS)

**Intuition:** 
The size of any given binary tree is simply the size of its left subtree plus the size of its right subtree, plus `1` to account for the current node itself. Because trees have a recursive structure, we can easily break this problem down into smaller sub-problems using a recursive traversal.
```cpp
// Intuition: The total number of nodes in a tree is the sum of nodes in its left and right subtrees, plus 1 for the root itself.
// Approach: Use a recursive Depth-First Search (DFS). Traverse down to the leaf nodes. If a node is null, return 0. Otherwise, recursively compute the size of the left and right subtrees and add 1 for the current node.
// Time Complexity: O(n) because we traverse and visit every single node in the tree exactly once.
// Space Complexity: O(h) where h is the height of the tree. This is the auxiliary space used by the recursion stack. In the worst-case (skewed tree), this could be O(n).

/*
Definition for Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/
class Solution {
  public:
    // Recursive function to find the size of binary tree.
    int getSize(Node *root) {
        // Base case: an empty tree (or child) contributes 0 to the size
        if (root == nullptr)
            return 0;
    
        // Recursively calculate the size of the left subtree
        int left = getSize(root->left);
        
        // Recursively calculate the size of the right subtree
        int right = getSize(root->right);
    
        // Total size is left + right + 1 (the current node)
        return left + right + 1;
    }
};

/*
 * Dry Run
 *
 * Input Tree:
 *       5
 *      / \
 *     1   2
 *
 * Execution Steps:
 * 1. getSize(5) is called.
 *    - Needs left = getSize(1)
 * 2. getSize(1) is called.
 *    - Needs left = getSize(null) -> returns 0
 *    - Needs right = getSize(null) -> returns 0
 *    - Returns 0 + 0 + 1 = 1. So, left subtree of 5 has size 1.
 * 3. Back to getSize(5), now needs right = getSize(2).
 * 4. getSize(2) is called.
 *    - Needs left = getSize(null) -> returns 0
 *    - Needs right = getSize(null) -> returns 0
 *    - Returns 0 + 0 + 1 = 1. So, right subtree of 5 has size 1.
 * 5. Back to getSize(5).
 *    - Total = left(1) + right(1) + 1(current node 5) = 3.
 * 
 * Final Output: 3
 */
```

---

## 🧠 Key Insights

* **Divide and Conquer:** This problem is a textbook example of breaking a larger problem down into identically structured, smaller sub-problems. By solving for the left and right subtrees, the main problem naturally resolves itself.
* **Implicit Stack Utilization:** The recursive approach elegantly handles traversal state implicitly via the call stack, removing the need for a manually maintained queue or stack (as would be required in an iterative level-order approach).

---

## 🔗 Further Exploration

Once you've mastered calculating the size of a binary tree, consider practicing these related problems:
* **Height of Binary Tree**: Instead of counting total nodes, find the longest path from root to leaf.
* **Sum of Binary Tree**: Calculate the sum of all node values instead of counting them.
* **Count Leaves in Binary Tree**: Modify the logic to only count nodes that have no children.

---

## 📚 References

* **GeeksforGeeks Problem:** [Size of Binary Tree](https://www.geeksforgeeks.org/problems/size-of-binary-tree/1)
* **Topics:** `Tree`, `Data Structures`

---

## 👨‍💻 Author

Created and maintained by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

![Tree](https://img.shields.io/badge/-Tree-000000?style=flat-square&logo=git&logoColor=white)
![Data Structures](https://img.shields.io/badge/-Data%20Structures-0052CC?style=flat-square&logo=atlassian&logoColor=white)
![DFS](https://img.shields.io/badge/-DFS-323330?style=flat-square) ![Recursion](https://img.shields.io/badge/-Recursion-007ACC?style=flat-square)![C++](https://img.shields.io/badge/-C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)