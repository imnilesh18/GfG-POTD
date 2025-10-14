# BST k-th Smallest in BST 🌳

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-43.53%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/find-k-th-smallest-element-in-bst/1).

---

## 📝 Problem Statement

Given the **root** of a Binary Search Tree (BST) and an integer **k**, the task is to find the **k-th smallest element** in the BST. If there is no k-th smallest element present, return **-1**.

### Constraints:

- `1 ≤ number of nodes, k ≤ 10^4`
- `1 ≤ node->data ≤ 10^4`

---

## 🧪 Examples

Here are a couple of examples to illustrate the problem:

<details>
<summary><strong>Example 1</strong></summary>

```
Input:
root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14]
k = 3

Output: 10
```

**Explanation:** The inorder traversal of the BST is `4, 8, 10, 12, 14, 20, 22`. The 3rd smallest element is `10`.

</details>

<details>
<summary><strong>Example 2</strong></summary>

```
Input:
root = [2, 1, 3]
k = 5

Output: -1
```

**Explanation:** There is no 5th smallest element as the BST only contains 3 nodes.

</details>

---

## 💡 Solution Approaches

### Optimized Approach: Inorder Traversal

The core idea is to leverage the property of a BST that an **inorder traversal** visits the nodes in ascending order. We can perform an inorder traversal and keep a counter to find the k-th element.

```cpp
// Intuition: The inorder traversal of a BST visits nodes in ascending order.
// We can traverse the tree and decrement k at each node until k becomes 0,
// at which point the current node is the k-th smallest.

// Approach:
// 1. Define a helper function for inorder traversal that takes the root, a reference to k, and a reference to the result.
// 2. In the helper function, first traverse the left subtree.
// 3. After returning from the left subtree, process the current node:
//    a. Decrement k.
//    b. If k becomes 0, this is the k-th smallest element. Store its data in the result and return.
// 4. If the k-th element is not yet found, traverse the right subtree.
// 5. The main function initializes the result to -1 and calls the inorder helper.

// Time Complexity: O(N) in the worst case, where N is the number of nodes, as we might need to visit all nodes.
// In the average case, it's O(H + k) where H is the height of the tree.
// Space Complexity: O(H) for the recursion stack, where H is the height of the tree.

class Solution {
public:
    // Helper function to perform inorder traversal
    void inorder(Node* root, int& k, int& result) {
        if (!root) { // Base case: if the node is null, return
            return;
        }

        // 1. Traverse the left subtree
        inorder(root->left, k, result);

        // If k is already 0, it means we found our element in the left subtree
        if (k == 0) {
            return;
        }

        // 2. Process the current node
        k--; // Decrement k as we visit a node
        if (k == 0) { // If k is now 0, this is the k-th smallest element
            result = root->data;
            return;
        }

        // 3. Traverse the right subtree
        inorder(root->right, k, result);
    }

    // Main function to find the k-th smallest element
    int kthSmallest(Node* root, int k) {
        int result = -1; // Initialize result to -1
        inorder(root, k, result); // Start the inorder traversal
        return result;
    }
};

/*
*
* Dry Run
*
* Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], k = 3
*
* 1. kthSmallest(root=20, k=3) is called. result = -1.
* 2. inorder(root=20, k=3, result=-1)
* 3.  -> inorder(root=8, k=3, result=-1)
* 4.    -> inorder(root=4, k=3, result=-1)
* 5.      -> Left of 4 is null. Return.
* 6.      -> Process node 4: k becomes 2.
* 7.      -> Right of 4 is null. Return.
* 8.    -> Process node 8: k becomes 1.
* 9.    -> inorder(root=12, k=1, result=-1)
* 10.     -> inorder(root=10, k=1, result=-1)
* 11.       -> Left of 10 is null. Return.
* 12.       -> Process node 10: k becomes 0. result is set to 10. Return.
* 13.     -> k is 0, so we immediately return.
* 14.   -> k is 0, so we immediately return.
* 15. -> k is 0, so we immediately return.
* 16. The final result is 10.
*
*/
```

---

## 🎯 Key Insights

- The fundamental property of a Binary Search Tree (BST) is that an **inorder traversal** (Left-Root-Right) processes the nodes in their natural sorted order.
- This allows us to find the k-th smallest element by simply stopping the traversal after visiting `k` nodes.
- Using a reference for `k` (`int& k`) is crucial for efficiency. It ensures that the value of `k` is updated across recursive calls, allowing for early termination once the element is found.

---

## 🚀 Further Exploration

- **Find the k-th largest element in a BST.** (Hint: Think about a reverse inorder traversal).
- **Convert BST to a sorted doubly linked list in-place.**
- [GeeksforGeeks: Find K-th largest element in BST](https://www.geeksforgeeks.org/problems/kth-largest-element-in-bst/1)
- [GeeksforGeeks: Predecessor and Successor](https://www.geeksforgeeks.org/problems/predecessor-and-successor/1)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - k-th Smallest in BST](https://www.geeksforgeeks.org/problems/find-k-th-smallest-element-in-bst/1)
- **Inorder Traversal:** [Wikipedia](https://en.wikipedia.org/wiki/Tree_traversal#In-order)

---

## 🧑‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`binary-search-tree` `tree` `inorder-traversal` `geeksforgeeks` `recursion`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions in this repository are for educational and reference purposes. We encourage you to try solving the problems on your own first to maximize your learning.
