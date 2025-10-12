# 🍬 Distribute Candies in a Binary Tree

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-29620F?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-63.24%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/distribute-candies-in-a-binary-tree/1).

---

## Problem Statement

You are given the **root** of a binary tree with **n** nodes, where each node contains a certain number of candies, and the total number of candies across all nodes is **n**. In one move, you can select any two **adjacent** nodes and transfer one candy from one node to the other. The transfer can occur between a parent and child in **either** direction.

The task is to determine the **minimum** number of moves required to ensure that every node in the tree has **exactly** one candy.

**Note:** The testcases are framed such that it is always possible to achieve a configuration in which every node has exactly one candy, after some moves.

---

## Examples

### Example 1:

```
Input: root = [5, 0, 0, N, N, 0, 0]
Output: 6
Explanation:
Move 1 candy from root to left child
Move 1 candy from root to right child
Move 1 candy from right child to root->right->left node
Move 1 candy from root to right child
Move 1 candy from right child to root->right->right node
Move 1 candy from root to right child
so, total 6 moves required.
```

<details>
<summary>📖 Example Breakdown</summary>

Let's trace the flow for `root = [5, 0, 0, N, N, 0, 0]`.

The tree structure is:

```
      5
     / \
    0   0
       / \
      0   0
```

1.  **Post-Order Traversal:** We start from the leaves. The bottom-left `0` needs 1 candy. Its parent (the right child `0`) gives it one. **Moves = 1**. The parent now has -1 candies.
2.  The bottom-right `0` needs 1 candy. Its parent (the right child `0`) gives it one. **Moves = 1+1=2**. The parent now has -2 candies.
3.  The right child `0` now needs 3 candies (1 for itself and 2 for its children). It gets them from the root. **Moves = 2+3=5**. The root now has `5-3 = 2` candies.
4.  The left child `0` needs 1 candy. It gets it from the root. **Moves = 5+1=6**. The root now has `2-1=1` candy.
5.  The tree is now balanced, and every node has exactly one candy. Total moves = **6**.

</details>

### Example 2:

```
Input: root = [2, 0, 0, N, N, 3, 0]
Output: 4
Explanation:
Move 1 candy from root to left child
Move 1 candy from root->right->left node to root->right node
Move 1 candy from root->right node to root->right->right node
Move 1 candy from root->right->left node to root->right node
so, total 4 moves required.
```

---

## Constraints

<div align="center">

`1 ≤ n ≤ 3*10^3`
`0 ≤ Node->data ≤ n`
`The sum of all Node->data = n`

</div>

---

## Solution Approaches

### 🧠 Optimized Approach (Post-Order Traversal)

The core idea is to use a post-order traversal (DFS) to calculate the "candy balance" for each subtree. For any node, the number of moves is the sum of moves needed to balance its left and right subtrees.

- A **positive balance** from a child means it has excess candies to give to its parent.
- A **negative balance** means it needs candies from its parent.

The function returns the balance of the current subtree, and the total moves are accumulated in a reference variable.

#### C++ Solution

```cpp
// Intuition:
// We can think of the problem as a flow of candies. Each node needs to end up with one candy.
// A post-order traversal is perfect because to balance a node, we first need to know the state
// of its children (whether they have a surplus or deficit of candies).
// The helper function returns the "balance" of candies for a subtree:
// - Positive value: The subtree has excess candies to give away.
// - Negative value: The subtree needs candies from its parent.
// - Zero: The subtree is perfectly balanced.

// Approach:
// 1. Define a helper function `distCandyUtil` that performs a post-order traversal (DFS).
// 2. This function takes the current node and a reference to the total moves (`ans`) as arguments.
// 3. Base Case: If the node is null, it's balanced and requires 0 moves, so return 0.
// 4. Recursively call for the left and right children to get their candy balances (`l` and `r`).
// 5. The number of moves required for the current node is the sum of absolute balances of its children (`abs(l) + abs(r)`).
//    This is because `abs(l)` candies must move between the current node and its left child, and `abs(r)` for the right child.
// 6. Add these moves to the total `ans`.
// 7. Calculate the balance for the current node's subtree: `root->data + l + r - 1`. This is the number of candies the
//    current node has, plus the net candies from its children, minus the one candy it keeps for itself.
// 8. Return this balance to the parent call.

// Time Complexity: O(N), where N is the number of nodes in the tree. We visit each node exactly once.
// Space Complexity: O(H), where H is the height of the tree. This is for the recursion stack space. In the worst case (a skewed tree), it can be O(N).

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
        // Base case: a null node is balanced
        if (root == nullptr)
            return 0;

        // Recursively find the candy balance for the left subtree
        int l = distCandyUtil(root->left, ans);

        // Recursively find the candy balance for the right subtree
        int r = distCandyUtil(root->right, ans);

        // The moves required are the absolute number of candies to be moved
        // from/to the left and right children to balance them.
        ans += abs(l) + abs(r);

        // Return the balance of the current subtree to its parent.
        // (current candies + balance from children - 1 candy for this node)
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
* / \
* 0(B) 0(C)
* / \
* 0(D) 0(E)
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

---

## Key Insights 💡

- **Post-Order is Key**: The problem has a dependency structure where a parent node cannot be "balanced" until its children are. This naturally leads to a post-order traversal solution.
- **Concept of Balance**: The idea of returning a "balance" or "debt/surplus" from each recursive call is powerful. It simplifies the logic by allowing each node to only care about its immediate children, not the entire subtree structure below them. The total moves are simply the sum of all these local transactions.

---

## Further Exploration

- [Burning Tree](https://www.geeksforgeeks.org/problems/burning-tree/1)
- [Lowest Common Ancestor in a Binary Tree](https://www.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-binary-tree/1)
- [Maximum Path Sum between 2 Special Nodes](https://www.geeksforgeeks.org/problems/maximum-path-sum-between-2-special-nodes/1)

---

## References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/distribute-candies-in-a-binary-tree/1)

---

## Author

<div align="center">

[imnilesh18](https://github.com/imnilesh18)

</div>

---

## Tags

<div align="center">

![Binary Tree](https://img.shields.io/badge/Binary%20Tree-2A8B9D?style=for-the-badge)
![DFS](https://img.shields.io/badge/DFS-4B8BBE?style=for-the-badge)
![Post-Order Traversal](https://img.shields.io/badge/Post--Order-9CC4E4?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GFG-29620F?style=for-the-badge)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

</div>

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Note**: This is for educational purposes only. All problem statements and examples are from GeeksforGeeks.
