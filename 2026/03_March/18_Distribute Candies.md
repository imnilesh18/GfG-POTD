# 🍬 Distribute Candies

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/distribute-candies-in-a-binary-tree/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-63.24%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
  </a>
</div>

<br>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given the `root` of a binary tree with `n` nodes, where each node contains a certain number of candies, and the total number of candies across all nodes is `n`. 

In one move, you can select any two **adjacent** nodes and transfer one candy from one node to the other. The transfer can occur between a parent and child in **either** direction.

The task is to determine the **minimum** number of moves required to ensure that every node in the tree has **exactly** one candy.

> **Note:** The testcases are framed such that it is always possible to achieve a configuration in which every node has exactly one candy, after some moves.

---

## 💡 Examples

### Example 1

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/912840/Web/Other/blobid0_1759751405.jpg" alt="Example 1 Visualization" />
</div>

```text
Input: root = [5, 0, 0, N, N, 0, 0]
Output: 6

Explanation:
- Move 1 candy from root to left child
- Move 1 candy from root to right child
- Move 1 candy from right child to root->right->left node
- Move 1 candy from root to right child
- Move 1 candy from right child to root->right->right node
- Move 1 candy from root to right child
So, total 6 moves required.
````

### Example 2

<div align="center">
<img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/912840/Web/Other/blobid1_1759751720.jpg" alt="Example 2 Visualization" />
</div>

```text
Input: root = [2, 0, 0, N, N, 3, 0]
Output: 4

Explanation:
- Move 1 candy from root to left child
- Move 1 candy from root->right->left node to root->right node
- Move 1 candy from root->right node to root->right->right node
- Move 1 candy from root->right->left node to root->right node
So, total 4 moves required.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

1.  We start balancing from the bottom (leaves) to the top (root).
2.  The bottom-most leaves `0(D)` and `0(E)` each need `1` candy, returning a balance of `-1` to their parent `0(C)`.
3.  To fix both children, `2` moves are recorded (candies flowing down). Node `C` itself is `0`, so it now needs `-3` total candies (`-1` for D, `-1` for E, `-1` for itself) from its parent `5(A)`.
4.  The left child `0(B)` needs `1` candy, adding `1` move and passing `-1` requirement to the root.
5.  The root `5(A)` pushes `1` candy left and `3` candies right. The total moves across all edges equals `abs(-1) + abs(-3) + abs(-1) + abs(-1) = 6`.

</details>

-----

## ⚙️ Constraints

  - $1 \le n \le 3 \times 10^3$
  - $0 \le Node \rightarrow data \le n$
  - The sum of all $Node \rightarrow data = n$

-----

## 🛠️ Solution Approaches

### Depth-First Search (Post-Order Traversal)

**Intuition:**
We can think of the problem as a flow of candies. Each node needs to end up with exactly one candy. A post-order traversal is perfect because to balance a node, we first need to know the state of its children (whether they have a surplus or a deficit of candies). The helper function returns the "balance" of candies for a subtree: positive means excess, negative means deficit, and zero means perfectly balanced.

```cpp
// Intuition: Think of candies flowing up and down the edges. Post-order traversal allows balancing children before their parents.
// Approach: Traverse the tree using DFS. At each node, calculate the net balance (left balance + right balance + node's data - 1). The moves needed at this node's edges equal the absolute sum of the left and right balances. Add this to the total moves.
// Time Complexity: O(N) where N is the number of nodes, as we visit each node exactly once.
// Space Complexity: O(H) where H is the height of the tree, representing the recursion stack space.

/*
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};
*/

class Solution {
  public:
    // Helper function to perform post-order traversal and calculate moves
    int distCandyUtil(Node* root, int& ans) {
        // Base case: a null node is perfectly balanced (needs 0 candies)
        if (root == nullptr) return 0;

        // Recursively find the candy balance for the left subtree
        int l = distCandyUtil(root->left, ans);

        // Recursively find the candy balance for the right subtree
        int r = distCandyUtil(root->right, ans);

        // The moves required are the absolute number of candies to be moved
        // from/to the left and right children to balance them.
        ans += abs(l) + abs(r);

        // Return the balance of the current subtree to its parent.
        // Formula: (current candies) + (balance from children) - (1 candy for this node)
        return root->data + l + r - 1;
    }

    // Main function to initiate the process
    int distCandy(Node* root) {
        int ans = 0;
        distCandyUtil(root, ans);
        return ans;
    }
};

/*
 *
 * Dry Run
 * Input: root = [5, 0, 0, N, N, 0, 0]
 * Tree:
 * 5 (A)
 * /     \
 * 0(B)    0(C)
 * /    \
 * 0(D)  0(E)
 *
 * 1. distCandyUtil(D, ans): returns D->data - 1 = 0 - 1 = -1. ans = 0.
 * 2. distCandyUtil(E, ans): returns E->data - 1 = 0 - 1 = -1. ans = 0.
 * 3. distCandyUtil(C, ans):
 * - l = distCandyUtil(D) = -1
 * - r = distCandyUtil(E) = -1
 * - ans += abs(-1) + abs(-1) = 2.
 * - returns C->data + l + r - 1 = 0 + (-1) + (-1) - 1 = -3.
 * 4. distCandyUtil(B, ans): returns B->data - 1 = 0 - 1 = -1. ans = 2.
 * 5. distCandyUtil(A, ans):
 * - l = distCandyUtil(B) = -1
 * - r = distCandyUtil(C) = -3
 * - ans += abs(-1) + abs(-3) = 2 + 4 = 6.
 * - returns A->data + l + r - 1 = 5 + (-1) + (-3) - 1 = 0.
 *
 * Final ans = 6.
 *
 */
```

-----

## 🧠 Key Insights

  - **Edge Flow Paradigm:** Instead of tracking exact paths of individual candies, treat each edge as a conduit. The number of candies passing through an edge is simply the absolute net balance of the entire subtree below that edge.
  - **Post-Order Necessity:** We must evaluate children before parents so the parent knows exactly how many candies to push down or pull up to satisfy its entire branch.

-----

## 🔍 Further Exploration

  - **Distribute Coins in Binary Tree (LeetCode 979):** The identically-structured problem on LeetCode for additional practice.
  - **Binary Tree Maximum Path Sum:** Explore more complex DP/DFS logic that traverses up through binary tree edges.

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Distribute Candies](https://www.geeksforgeeks.org/problems/distribute-candies-in-a-binary-tree/1)

-----

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**
