# 🌳 Maximum path sum

| <a href="https://www.geeksforgeeks.org/problems/maximum-path-sum-from-any-node/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" /></a> |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |

| **Difficulty** | **Accuracy** | **Points** | **License** |
| :------------: | :----------: | :--------: | :---------: |
|     Medium     |    42.92%    |     4      |     MIT     |

<br>

> **Educational Use Only**: This repository and its content are intended solely for educational purposes. The solutions provided are for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem of the day.

<br>

## **Problem Statement**

Given the `root` of a binary tree, your task is to find the **maximum path sum**. The path may start and end at any node in the tree.

---

### **Examples**

<details>
<summary><b>Example 1</b></summary>

<br>

**Input:**

```
root = [10, 2, 10, 20, 1, null, -25, null, null, null, null, 3, 4]
```

**Output:**

```
42
```

**Explanation:**
The max path sum is `20 + 2 + 10 + 10 = 42`.

<div align="center">
    <img src="https://media.geeksforgeeks.org/wp-content/uploads/20210203120127/Screenshot20210203at120054PM.png" alt="Example 1" width="300"/>
</div>

</details>

<details>
<summary><b>Example 2</b></summary>

<br>

**Input:**

```
root = [-17, 11, 4, 20, -2, 10]
```

**Output:**

```
31
```

**Explanation:**
The max path sum is `20 + 11 = 31`.

</details>

---

### **Constraints**

- `1 ≤ number of nodes ≤ 10^3`
- `-10^4 ≤ node->data ≤ 10^4`

---

## **Solution Approach**

### **Optimized Approach (Recursive DFS)**

The core idea is to recursively calculate the maximum path sum for each node. For any given node, there are four possibilities for the maximum path sum that involves it:

1. The node itself.
2. The node plus the maximum path from its left child.
3. The node plus the maximum path from its right child.
4. The node plus the maximum paths from both its left and right children (forming a "V" shape).

A recursive function `solve(root)` will return the maximum path sum starting from `root` and going downwards (either left or right). We use a global variable `maxSum` to keep track of the overall maximum path sum found so far, which can be a path that doesn't necessarily start or end at the root of the tree.

<br>

### C++ Code

```cpp
// Intuition:
// The problem asks for the maximum path sum in a binary tree, where a path can start and end at any node.
// This suggests a traversal of the tree, likely a post-order traversal (DFS), to process children before the parent.
// For each node, we need to consider two main possibilities:
// 1. A path that goes "through" the current node, connecting its left and right subtrees.
// 2. A path that starts at the current node and extends into one of its subtrees (left or right).
// The function should return the maximum path sum that can be extended upwards to its parent, while a global or reference variable will track the overall maximum path sum found anywhere in the tree.

// Approach:
// We use a recursive function, `solve(root)`, which returns the maximum path sum starting from the `root` and extending downwards.
// A global variable `maxSum` is used to store the maximum path sum found so far across the entire tree.
// 1. Base Case: If `root` is null, the path sum is 0.
// 2. Recursively call `solve` for the left (`lh`) and right (`rh`) children.
// 3. For the current node, calculate four potential maximum path sums:
//    a. `sumThroughRoot`: The path that connects the left and right children through the current node (`lh + rh + root->data`).
//    b. `maxChildPath`: The path that includes the current node and the better of its two children's paths (`max(lh, rh) + root->data`).
//    c. `singleNode`: The path that consists of only the current node (`root->data`).
// 4. Update `maxSum` with the maximum of `maxSum`, `sumThroughRoot`, `maxChildPath`, and `singleNode`. This step is crucial because the overall maximum path might be a "V" shaped path that cannot be extended upwards.
// 5. The function must return the maximum path sum that can be extended to the parent node. This can only be a path that includes the current node and at most one of its children, or just the node itself. Therefore, we return `max(maxChildPath, singleNode)`.
// 6. The main function `findMaxSum` initializes `maxSum` to a very small number (`INT_MIN`) and kicks off the recursion.

// Time Complexity: O(N), where N is the number of nodes in the binary tree. We visit each node exactly once.
// Space Complexity: O(H), where H is the height of the tree. This is due to the recursion stack space, which in the worst case (a skewed tree) can be O(N).

class Solution {
 public:
  int maxSum;  // Global variable to store the maximum path sum found so far.

  int solve(Node* root) {
    if (!root) {
      return 0;  // Base case: if the node is null, the path sum is 0.
    }

    // Recursively find the max path sum in the left and right subtrees.
    int lh = solve(root->left);
    int rh = solve(root->right);

    // Case 1: Path goes through the current root, connecting left and right
    // subtrees.
    int sumThroughRoot = lh + rh + root->data;

    // Case 2: Path includes the root and the best path from either the left or
    // right child.
    int maxChildPath = max(lh, rh) + root->data;

    // Case 3: The path is just the current node itself.
    int singleNode = root->data;

    // Update the overall maximum sum with the best possibility found at the
    // current node. The overall max path could be one that is contained within
    // the subtree of the current node and doesn't extend upwards.
    maxSum = max({maxSum, sumThroughRoot, maxChildPath, singleNode});

    // Return the maximum path sum that can be extended to the parent node.
    // This can only be a path starting from the current node and going down one
    // side, or just the node itself.
    return max(maxChildPath, singleNode);
  }

  // Function to return maximum path sum from any node in a tree.
  int findMaxSum(Node* root) {
    maxSum = INT_MIN;  // Initialize maxSum to the smallest possible integer.

    solve(root);  // Start the recursive process from the root.

    return maxSum;  // Return the final computed maximum path sum.
  }

  /*
   * Dry Run:
   *
   * Let's trace with the first example: root = [10, 2, 10, 20, 1, N, -25, N, N,
   N, N, 3, 4]
   *
   * 1. findMaxSum(10) is called. maxSum = INT_MIN.
   * 2. solve(10) is called.
   * - It calls solve(2) for the left child.
   * - It calls solve(20) for its left child.
   * - solve(20) calls solve(NULL) for both children, gets lh=0, rh=0.
   * - sumThroughRoot = 0 + 0 + 20 = 20
   * - maxChildPath = max(0, 0) + 20 = 20
   * - singleNode = 20
   * - maxSum becomes max(INT_MIN, 20, 20, 20) = 20.
   * - Returns max(20, 20) = 20.
   * - Now for node 2, lh = 20 (from solve(20)).
   * - It calls solve(1) for its right child.
   * - solve(1) gets lh=0, rh=0.
   * - maxSum remains 20.
   * - Returns 1.
   * - Back at node 2: lh=20, rh=1.
   * - sumThroughRoot = 20 + 1 + 2 = 23
   * - maxChildPath = max(20, 1) + 2 = 22
   * - singleNode = 2
   * - maxSum becomes max(20, 23, 22, 2) = 23.
   * - Returns max(22, 2) = 22.
   * - Back at node 10: lh = 22 (from solve(2)).
   * - It calls solve(10) for the right child.
   * - It calls solve(-25) for its right child.
   * - It calls solve(3) and solve(4).
   * - solve(3) returns 3, solve(4) returns 4.
   * - For node -25: lh=3, rh=4.
   * - sumThroughRoot = 3 + 4 - 25 = -18
   * - maxChildPath = max(3, 4) - 25 = -21
   * - singleNode = -25
   * - maxSum (23) is not updated.
   * - Returns max(-21, -25) = -21.
   * - Back at the second node 10: lh=0, rh=-21.
   * - sumThroughRoot = 0 - 21 + 10 = -11
   * - maxChildPath = max(0, -21) + 10 = 10
   * - singleNode = 10
   * - maxSum (23) is not updated.
   * - Returns max(10, 10) = 10.
   * - Finally, at the root node 10: lh=22, rh=10.
   * - sumThroughRoot = 22 + 10 + 10 = 42
   * - maxChildPath = max(22, 10) + 10 = 32
   * - singleNode = 10
   * - maxSum becomes max(23, 42, 32, 10) = 42.
   * - Returns max(32, 10) = 32.
   *
   * 3. The recursion finishes. findMaxSum returns maxSum, which is 42.
   */
};
```

---

## **Key Insights**

The key to this problem is understanding that for any node, the maximum path sum could either pass through it (connecting its left and right subtrees) or be a path that starts at that node and goes down one of its subtrees. The recursive function cleverly handles this by returning the value of the path that can be extended upwards, while a global variable tracks the maximum path sum found at any point in the tree, which might not be extensible.

---

## **Further Exploration**

- [Diameter of a Binary Tree](https://www.geeksforgeeks.org/problems/diameter-of-binary-tree/1)
- [Binary Tree to DLL](https://www.geeksforgeeks.org/problems/binary-tree-to-dll/1)
- [Lowest Common Ancestor in a Binary Tree](https://www.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-binary-tree/1)

---

## **References**

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/maximum-path-sum-from-any-node/1)
- [Maximum Path Sum in a Binary Tree (Article)](https://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/)

---

## **Author**

<a href="https://github.com/imnilesh18"><img src="https://img.shields.io/badge/imnilesh18-000000?style=for-the-badge&logo=github&logoColor=white" /></a>

---

## **Tags**

`Binary Tree` `DFS` `Recursion` `GeeksforGeeks`

---

## **License**

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> [!NOTE]
> This is an educational repository. The solutions are provided for learning and practice. They are not intended for use in any commercial product or service. All problem statements and test cases are from GeeksforGeeks.
