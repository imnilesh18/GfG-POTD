# 🟩 Preorder Traversal

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-358a1e?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Basic](https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge)
![Accuracy: 62.73%](https://img.shields.io/badge/Accuracy-62.73%25-blue?style=for-the-badge)
![Points: 1](https://img.shields.io/badge/Points-1-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/preorder-traversal/1) problem.

---

## 📝 Problem Statement

Given the **root** of a binary tree, your task is to return its **Preorder Traversal**.

> 💡 **Note:** A preorder traversal visits tree nodes in the following sequence:
> 1. Visit the **root node**.
> 2. Visit the **left subtree** (recursively).
> 3. Visit the **right subtree** (recursively).

---

## 📸 Examples

### Example 1
```text
Input: root = [1, 4, N, 4, 2]
       1
      /
     4
    / \
   4   2

Output: [1, 4, 4, 2]
Explanation: The preorder traversal visits root (1) -> left child (4) -> left child (4) -> right child (2).
```

### Example 2
```text
Input: root = [6, 3, 2, N, 1, 2, N]
       6
      / \
     3   2
      \ /
      1 2

Output: [6, 3, 1, 2, 2]
Explanation: The preorder traversal visits 6 -> 3 -> 1 -> 2 -> 2.
```

---

<details>
<summary>📖 <b>Example Breakdown (Step-by-Step Walkthrough)</b></summary>

<br>

Consider Example 1 Tree Structure:
```text
       1 (Root)
      /
     4
    / \
   4   2
```

1. Start at **Root (1)** $\rightarrow$ Visit & Process Node `1`. *(Result: `[1]`)*
2. Traverse to **Left Child (4)** $\rightarrow$ Visit & Process Node `4`. *(Result: `[1, 4]`)*
3. Traverse to **Left Child (4)** $\rightarrow$ Visit & Process Node `4`. *(Result: `[1, 4, 4]`)*
4. Node `4` has no left/right children $\rightarrow$ Backtrack to parent Node `4`.
5. Traverse to **Right Child (2)** $\rightarrow$ Visit & Process Node `2`. *(Result: `[1, 4, 4, 2]`)*
6. Traversal Complete. Output Array: `[1, 4, 4, 2]`.

</details>

---

## ⚙️ Constraints

> - $1 \le \text{Number of Nodes} \le 3 \times 10^4$
> - $0 \le \text{node->data} \le 10^5$

---

## 💡 Solution Approach

### 1. Recursive Depth-First Search (DFS)

#### Intuition
Preorder traversal naturally follows a Depth-First Search pattern. By processing the current node first and then recursively invoking the traversal on the left and right subtrees, we maintain the strict **Root $\rightarrow$ Left $\rightarrow$ Right** ordering required.

#### C++ Code

```cpp
// Intuition: Preorder traversal follows Root -> Left -> Right order. We process the current node first, then recursively traverse left and right subtrees.
// Approach: Depth-First Search (DFS) using a recursive helper function to visit nodes and collect values into a vector.
// Time Complexity: O(N) where N is the total number of nodes, as every node is visited exactly once.
// Space Complexity: O(H) auxiliary space due to the call stack, where H is the height of the tree (O(N) worst-case, O(log N) average).

/*
class Node
{
    int data;
    Node* left;
    Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
*/

class Solution {
  private:
    // Helper function to perform recursive preorder traversal
    void solve(Node* root, vector<int>& ans) {
        if (root == NULL) return; // Base case: empty subtree
        
        ans.push_back(root->data); // Step 1: Visit Root
        solve(root->left, ans);    // Step 2: Recurse Left Subtree
        solve(root->right, ans);   // Step 3: Recurse Right Subtree
    }

  public:
    vector<int> preOrder(Node* root) {
        vector<int> ans;
        solve(root, ans); // Start DFS traversal from root
        return ans;
    }
};

/*
*
* Dry Run
*
* Input Tree:
*       1
*      /
*     4
*    / \
*   4   2
*
* Execution Trace:
* 1. solve(1, ans) -> ans.push_back(1) -> ans = [1]
*    - Calls solve(1->left [4], ans)
* 2. solve(4, ans) -> ans.push_back(4) -> ans = [1, 4]
*    - Calls solve(4->left [4], ans)
* 3. solve(4, ans) -> ans.push_back(4) -> ans = [1, 4, 4]
*    - Calls solve(NULL), returns
*    - Calls solve(NULL), returns
*    - Returns to node 4
* 4. Back to parent node 4
*    - Calls solve(4->right [2], ans)
* 5. solve(2, ans) -> ans.push_back(2) -> ans = [1, 4, 4, 2]
*    - Calls solve(NULL), returns
*    - Calls solve(NULL), returns
*    - Returns to node 4
* 6. Returns to node 1
*    - Calls solve(1->right [NULL]), returns
* 7. Final Output: [1, 4, 4, 2]
*
*/
```

---

## 🔑 Key Insights

* **DFS Paradigm:** Preorder is a Depth-First Search strategy where node visitation happens before exploring either subtree.
* **Call Stack:** The maximum depth of the recursion corresponds to the tree height ($H$).
* **Reconstruction:** Preorder traversal combined with Inorder traversal can uniquely reconstruct a binary tree.

---

## 🔍 Further Exploration

Looking to solve similar tree problems? Try these GeeksforGeeks challenges:

* 🔗 [Inorder Traversal](https://www.geeksforgeeks.org/problems/inorder-traversal/1)
* 🔗 [Postorder Traversal](https://www.geeksforgeeks.org/problems/postorder-traversal/1)
* 🔗 [Level Order Traversal](https://www.geeksforgeeks.org/problems/level-order-traversal/1)
* 🔗 [Morris Preorder Traversal (O(1) Space)](https://www.geeksforgeeks.org/morris-traversal-for-preorder/)

---

## 📚 References

* **GeeksforGeeks Problem Page:** [Preorder Traversal](https://www.geeksforgeeks.org/problems/preorder-traversal/1)
* **Topics:** `Tree`, `Stack`, `Depth-First Search`

---

## 👤 Author

Crafted with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`![Tree](https://img.shields.io/badge/-Tree-007ACC?style=flat-square)`
`![Depth First Search](https://img.shields.io/badge/-DFS-green?style=flat-square)`
`![Binary Tree](https://img.shields.io/badge/-BinaryTree-blue?style=flat-square)`
`![C++](https://img.shields.io/badge/-C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)`
`![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks-358a1e?style=flat-square)`
