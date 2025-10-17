# 🌳 BST to Greater Sum Tree

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/bst-to-greater-sum-tree/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-66.73%25-brightgreen.svg" alt="Accuracy: 66.73%">
  <img src="https://img.shields.io/badge/Points-4-blue.svg" alt="Points: 4">
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT">
  </a>
</p>

---

### ⚠️ Educational Use Only

This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/bst-to-greater-sum-tree/1).

---

## 🎯 Problem Statement

Given the **root** of a **BST** with unique node values, transform it into a **greater sum tree** where each node contains the sum of all nodes **greater** than that node.

---

## 📖 Examples

### Example 1

```
Input:
root = [11, 2, 29, 1, 7, 15, 40, N, N, N, N, N, N, 35, N]

      11
     /  \
    2    29
   / \   / \
  1   7 15  40
           /
          35

Output: [119, 137, 75, 139, 130, 104, 0, N, N, N, N, N, N, 40, N]

      119
     /   \
   137    75
   / \    / \
 139 130 104  0
            /
           40

Explanation:
Every node is replaced with the sum of nodes greater than itself.
```

### Example 2

```
Input:
root = [2, 1, 6, N, N, 3, 7]

      2
     / \
    1   6
       / \
      3   7

Output: [16, 18, 7, N, N, 13, 0]

      16
     /  \
    18   7
        / \
       13  0

Explanation:
Every node is replaced with the sum of nodes greater than itself.
```

<details>
<summary>📖 Example 2 Breakdown</summary>

Let's walk through the transformation for `root = [2, 1, 6, N, N, 3, 7]`.

1.  **Goal**: For each node, find the sum of all nodes with values greater than it and replace the node's value with this sum.
2.  **Order of Traversal**: The most efficient way to do this is to process nodes from largest to smallest. In a BST, a **reverse in-order traversal (Right-Root-Left)** achieves this.
3.  **Process**: We'll keep a running `sum` of the values of nodes we have visited.

    * **Start at root (2). Go right to (6). Go right to (7).**
    * **Node 7 (Largest):**
        * Nodes greater than 7: None. Sum = 0.
        * Update node 7 to `0`.
        * Our running sum of visited nodes is now `7`.
    * **Backtrack to Node 6:**
        * Nodes greater than 6: Only {7}. Sum = 7.
        * Update node 6 to `7`.
        * Our running sum is now `7 (from before) + 6 = 13`.
    * **Go left from 6 to Node 3:**
        * Nodes greater than 3: {6, 7}. Sum = 13.
        * Update node 3 to `13`.
        * Our running sum is now `13 + 3 = 16`.
    * **Backtrack to root Node 2:**
        * Nodes greater than 2: {3, 6, 7}. Sum = 16.
        * Update node 2 to `16`.
        * Our running sum is now `16 + 2 = 18`.
    * **Go left from 2 to Node 1 (Smallest):**
        * Nodes greater than 1: {2, 3, 6, 7}. Sum = 18.
        * Update node 1 to `18`.
        * Our running sum is now `18 + 1 = 19`.

4.  **Final Tree**: The updated values are: `1 -> 18`, `2 -> 16`, `3 -> 13`, `6 -> 7`, `7 -> 0`. This matches the output.

</details>

---

## ⚠️ Constraints

* `1 ≤ node->data ≤ 3*10^4`
* `1 ≤ number of nodes ≤ 3*10^4`

---

## 💡 Solution Approaches

### Optimized Approach: Reverse In-order Traversal

The core idea is to traverse the tree in a way that we visit nodes in descending order of their values. For a Binary Search Tree (BST), a **reverse in-order traversal (Right, Root, Left)** accomplishes this perfectly.

As we traverse, we can maintain a cumulative sum of all the node values visited so far. For any given node, this cumulative sum (before adding the current node's value) represents the sum of all nodes greater than it.

```cpp
// Intuition: To find the sum of all nodes greater than the current node, we need to process nodes from largest to smallest. A reverse in-order traversal (Right-Root-Left) on a BST visits nodes in descending order. We can maintain a running sum of visited nodes to easily calculate the required value for each node.
// Approach:
// 1. We use a helper function that performs a reverse in-order traversal.
// 2. A variable 'sum' is passed by reference to keep track of the cumulative sum of nodes visited so far (from largest to current).
// 3. First, recurse on the right subtree to visit all larger nodes.
// 4. At the current node, we update the cumulative sum by adding its value. The new value for the node is then (new cumulative sum - current node's original value).
// 5. Finally, recurse on the left subtree to visit smaller nodes.
// Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
// Space Complexity: O(H), where H is the height of the tree, due to the recursion stack. In the worst case (a skewed tree), it's O(N).

/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};*/

class Solution {
  public:
    // Helper function to update the tree using reverse in-order traversal
    void updateTree(Node* root, int& sum) {
        // Base case: if the node is null, return.
        if (root == nullptr) {
            return;
        }
    
        // 1. Traverse the right subtree first (visits larger values).
        updateTree(root->right, sum);
    
        // 2. Update the cumulative sum with the current node's data.
        sum += root->data;
        // 3. The new value is the sum of all greater nodes, which is the current sum minus its own value.
        root->data = sum - root->data;
    
        // 4. Traverse the left subtree (visits smaller values).
        updateTree(root->left, sum);
    }
    
    // Main function to transform the tree.
    void transformTree(Node* root) {
      
        // Initialize the cumulative sum to 0.
        int sum = 0; 
        // Start the reverse in-order traversal.
        updateTree(root, sum);
    }
};

/*
*
* Dry Run (Example 2: root = [2, 1, 6, N, N, 3, 7])
*
* Initial call: transformTree(root=2) -> calls updateTree(root=2, sum=0)
*
* updateTree(2, sum=0):
* -> updateTree(6, sum=0)  // Go right
* -> updateTree(7, sum=0)  // Go right
* -> updateTree(nullptr, sum=0) // Right of 7, returns
* // Process Node 7:
* sum = 0 + 7 = 7
* Node 7 data = 7 - 7 = 0
* -> updateTree(nullptr, sum=7) // Left of 7, returns
* // Return to Node 6
* // Process Node 6:
* sum = 7 + 6 = 13
* Node 6 data = 13 - 6 = 7
* -> updateTree(3, sum=13) // Go left
* -> updateTree(nullptr, sum=13) // Right of 3, returns
* // Process Node 3:
* sum = 13 + 3 = 16
* Node 3 data = 16 - 3 = 13
* -> updateTree(nullptr, sum=16) // Left of 3, returns
* // Return to Node 6, then to Node 2
* // Process Node 2:
* sum = 16 + 2 = 18
* Node 2 data = 18 - 2 = 16
* -> updateTree(1, sum=18) // Go left
* -> updateTree(nullptr, sum=18) // Right of 1, returns
* // Process Node 1:
* sum = 18 + 1 = 19
* Node 1 data = 19 - 1 = 18
* -> updateTree(nullptr, sum=19) // Left of 1, returns
* // Return to Node 2, then to transformTree
*
* Final Tree State:
* - Node 7 -> 0
* - Node 3 -> 13
* - Node 6 -> 7
* - Node 1 -> 18
* - Node 2 -> 16
*/
```

---

## 🔑 Key Insights

* The properties of a BST are crucial. An **in-order traversal** visits nodes in ascending order, while a **reverse in-order traversal** visits them in descending order.
* By using a reverse in-order traversal, we ensure that when we are at any node `curr`, we have already processed all nodes with values greater than `curr`.
* Passing the `sum` variable by reference is an efficient way to maintain a single, shared state across all recursive calls without using global variables. This allows us to accumulate the sum of larger nodes correctly.

---

## 🚀 Further Exploration

* [Convert BST to a Min-Heap](https://www.geeksforgeeks.org/convert-bst-min-heap/)
* [Binary Tree to BST](https://www.geeksforgeeks.org/problems/binary-tree-to-bst/1)
* [Convert a normal BST to a Balanced BST](https://www.geeksforgeeks.org/problems/normal-bst-to-balanced-bst/1)
* What would change if you needed to convert it to a "lesser sum tree" (sum of all nodes smaller than the current node)?

---

## 📚 References

* [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/bst-to-greater-sum-tree/1)
* [In-order Traversal of a Binary Tree](https://www.geeksforgeeks.org/inorder-traversal-of-binary-tree/)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p>
  <a href="https://github.com/imnilesh18/gfg-potd/tree/main/10_October/17_BST%20to%20greater%20sum%20tree.cpp"><img alt="C++" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"></a>
  <a href="#"><img alt="GeeksforGeeks" src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white"></a>
  <a href="#"><img alt="BST" src="https://img.shields.io/badge/BST-2088FF?style=for-the-badge"></a>
  <a href="#"><img alt="Tree Traversal" src="https://img.shields.io/badge/Tree%20Traversal-FF6600?style=for-the-badge"></a>
</p>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](https://opensource.org/licenses/MIT) file for details.

**Reminder:** The solutions and code are for educational purposes only. Always try to solve the problem on your own first!