# 🌲 Minimum Absolute Difference In BST

<div align="center">
  <img src="https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksForGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-56.22%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

<div align="center">
  ⚠️ <b>Educational Use Only</b><br>
  This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given the root of a Binary Search Tree (BST) containing `n` (`n > 1`) nodes, find the **minimum absolute difference** between the values of any two different nodes in the tree.

Return the minimum absolute difference.

---

## 💡 Examples

```text
Input: root[] = [50, 30, 70, 20, N, 60, 80]
Output: 10
Explanation: There are no two nodes whose absolute difference is smaller than 10.
```

```text
Input: root[] = [60, 30, 90, 10]
Output: 20
Explanation: There are no two nodes whose absolute difference is smaller than 20.
```

<details>
<summary>📖 Example Breakdown</summary>

For the tree `[60, 30, 90, 10]`:
1. The inorder traversal (left, root, right) visits the nodes in sorted order: `10, 30, 60, 90`.
2. The differences between adjacent elements are:
   - `|30 - 10| = 20`
   - `|60 - 30| = 30`
   - `|90 - 60| = 30`
3. The minimum absolute difference is `20`.

</details>

---

## ⚠️ Constraints

* $2 \le \text{size of binary tree} \le 10^5$
* $0 \le \text{node.data} \le 10^6$

---

## 🚀 Solution Approaches

### Morris Inorder Traversal (Optimized Space)

The in-order traversal of a BST yields values in strictly increasing order, meaning the minimum absolute difference must be between two consecutive nodes in this sequence. Instead of storing the sequence or using a recursion stack ($O(h)$ space), we use **Morris Traversal**. This algorithm temporarily modifies the tree by creating threads (links) from in-order predecessors to their successive roots, allowing us to traverse the tree in $O(1)$ auxiliary space. 

```cpp
// Intuition: The in-order traversal of a BST yields node values in strictly increasing order. The minimum absolute difference must be between two adjacent nodes in this sorted order.
// Approach: Instead of using extra space for an array or a recursion stack, we use Morris Traversal. This allows us to traverse the tree in-order using O(1) space by creating temporary thread links from predecessors to current nodes, computing the difference with the previous node on the fly.
// Time Complexity: O(n), where n is the total number of nodes in the BST. Each node and edge is visited at most 3 times during the traversal.
// Space Complexity: O(1) auxiliary space, because we are solely utilizing the existing tree nodes (modifying and restoring links) and a few pointer variables.

/* Binary Tree Node Structure
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; 
*/

class Solution {
public:
    int absDiff(Node *root) {
        int minDiff = INT_MAX;
        Node* curr = root;
        Node* prev = nullptr; // Tracks the previously visited node in in-order

        while (curr != nullptr) {
            // Case 1: No left child, process current and move right
            if (curr->left == nullptr) {
                if (prev != nullptr) {
                    minDiff = std::min(minDiff, curr->data - prev->data);
                }
                prev = curr;
                curr = curr->right;
            } 
            // Case 2: Left child exists, find the inorder predecessor
            else {
                Node* predecessor = curr->left;
                
                // Go to the rightmost node in the left subtree
                while (predecessor->right != nullptr && predecessor->right != curr) {
                    predecessor = predecessor->right;
                }

                // Subcase A: Establish a temporary thread and move left
                if (predecessor->right == nullptr) {
                    predecessor->right = curr;
                    curr = curr->left;
                } 
                // Subcase B: Thread exists, left subtree is fully visited
                else {
                    predecessor->right = nullptr; // Restore original tree structure

                    // Process the current node
                    if (prev != nullptr) {
                        minDiff = std::min(minDiff, curr->data - prev->data);
                    }
                    prev = curr;
                    curr = curr->right;
                }
            }
        }

        return minDiff;
    }
};

/*
*
* Dry Run
*
* Input: root = [60, 30, 90, 10]
*
* Initial State: curr = 60, prev = nullptr, minDiff = INT_MAX
* 
* 1. curr = 60: Has left child (30). Predecessor is 30.
*    Predecessor's right is null. Thread 30->right = 60. curr = 30.
*
* 2. curr = 30: Has left child (10). Predecessor is 10.
*    Predecessor's right is null. Thread 10->right = 30. curr = 10.
* 
* 3. curr = 10: No left child.
*    Process 10. prev = nullptr, so skip difference.
*    prev = 10, curr = 10->right (which is 30 due to thread).
* 
* 4. curr = 30: Has left child. Predecessor is 10.
*    Predecessor's right == curr (10->right == 30).
*    Remove thread: 10->right = nullptr.
*    Process 30. prev = 10. minDiff = min(INT_MAX, 30 - 10) = 20.
*    prev = 30, curr = 30->right (which is 60 due to thread).
* 
* 5. curr = 60: Has left child. Predecessor is 30.
*    Predecessor's right == curr (30->right == 60).
*    Remove thread: 30->right = nullptr.
*    Process 60. prev = 30. minDiff = min(20, 60 - 30) = 20.
*    prev = 60, curr = 60->right (90).
*
* 6. curr = 90: No left child.
*    Process 90. prev = 60. minDiff = min(20, 90 - 60) = 20.
*    prev = 90, curr = 90->right (nullptr).
*
* curr is nullptr. Loop terminates.
* Return minDiff = 20.
*
*/
```

---

## 🧠 Key Insights

* **BST Property:** In-order traversal traverses elements in monotonic ascending order.
* **Adjacency is Key:** The minimum difference between any two numbers in a sorted array is guaranteed to be between two adjacent elements.
* **Morris Traversal Superpower:** It avoids the $O(h)$ auxiliary stack space typically required by recursion by temporarily linking the bottom-most leaves (predecessors) up to their respective roots. This results in an optimal $O(1)$ space footprint.

---

## 🔍 Further Exploration

* **Related Problems:**
  * Kth Smallest Element in a BST
  * Validate Binary Search Tree
  * Inorder Successor in BST
* **Concepts to Brush Up:**
  * Threaded Binary Trees
  * Amortized Time Complexity analysis of Morris Traversal.

---

## 🔗 References

* **Problem Link:** [Minimum Absolute Difference In BST on GeeksforGeeks](https://www.geeksforgeeks.org/problems/minimum-absolute-difference-in-bst-1665139652/1)
* **Morris Traversal Article:** [Inorder Tree Traversal without Recursion and without Stack](https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/)

---

## 👨‍💻 Author

**Nilesh Kumar**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BinarySearchTree` `#Tree` `#MorrisTraversal` `#SpaceOptimization` `#GeeksforGeeks` `#C++`