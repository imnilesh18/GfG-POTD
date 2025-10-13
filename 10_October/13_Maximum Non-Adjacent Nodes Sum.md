# 🌳 Maximum Non-Adjacent Nodes Sum

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-55.35%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)

</div>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximum-sum-of-non-adjacent-nodes/1).

---

## Problem Statement

Given the `root` of a binary tree with integer values. Your task is to select a **subset of nodes** such that the sum of their values is **maximized**, with the condition that no two selected nodes are directly connected. This means if a node is included in the subset, neither its `parent` nor its `children` can be included.

---

## Examples

Here are a couple of examples to illustrate the problem:

**Example 1:**

```
Input: root = [11, 1, 2]
Output: 11
Explanation: The maximum sum is obtained by selecting the node 11.
```

**Example 2:**

```
Input: root = [1, 2, 3, 4, N, 5, 6]
Output: 16
Explanation: The maximum sum is obtained by selecting the nodes 1, 4, 5, and 6, which are not directly connected. Their total sum is 16.
```

<details>
<summary>📖 Example 2 Breakdown</summary>
Let's walk through the tree `[1, 2, 3, 4, N, 5, 6]`:

```
      1
     / \
    2   3
   /   / \
  4   5   6
```

We have two main choices at the root `(1)`:

1.  **Include Node 1:** If we take node `1`, we cannot take its children `2` and `3`. The next nodes we can take are the grandchildren: `4`, `5`, and `6`.
    - Sum = `1 + 4 + 5 + 6 = 16`.
2.  **Exclude Node 1:** If we don't take node `1`, we are free to take the best possible sum from the left subtree (rooted at `2`) and the right subtree (rooted at `3`).
    - **Left Subtree (rooted at 2):** We can either take `2` (sum=2) or its child `4` (sum=4). We choose `4`.
    - **Right Subtree (rooted at 3):** We can either take `3` (sum=3) or its children `5` and `6` (sum=11). We choose `5` and `6`.
    - Total Sum = (from left) `4` + (from right) `11` = `15`.

Comparing the two scenarios, the maximum sum is **16**.

</details>

---

## Constraints

<div align="center">

`1 ≤ number of nodes ≤ 10^4`
`1 ≤ node.data ≤ 10^5`

</div>

---

## Solution Approaches

This problem has optimal substructure and overlapping subproblems, making it a perfect candidate for **Dynamic Programming on Trees**. For each node, we decide whether to include it in our sum or exclude it.

### Optimized Approach (DP with Post-Order Traversal)

The intuition is to make a decision at each node based on the optimal decisions from its children. We can use a post-order traversal to bubble up the results from the leaves.

For each node, we calculate two values:

1.  `sum_including_node`: The maximum sum for the subtree rooted at this node, **including** the node's value. This means we must exclude its immediate children.
2.  `sum_excluding_node`: The maximum sum for the subtree rooted at this node, **excluding** the node's value. This means we are free to take the best possible sum from its left and right children (they can either be included or excluded in their own subtrees).

The final answer is the maximum of these two values for the root of the entire tree.

#### C++ Code

```cpp
// Intuition: For each node, we have two choices: either include it in the sum (and skip its children) or exclude it (and take the maximum possible sum from its children). This decision can be made optimally by returning both possibilities from the children to the parent during a post-order traversal.
// Approach: We use a helper function `maxSumHelper` that performs a post-order traversal. It returns a pair for each node: {sum_if_included, sum_if_excluded}.
// - To calculate sum_if_included for the current node: `node->data + left_child.sum_if_excluded + right_child.sum_if_excluded`.
// - To calculate sum_if_excluded for the current node: `max(left_child.sum_if_included, left_child.sum_if_excluded) + max(right_child.sum_if_included, right_child.sum_if_excluded)`.
// The final answer is the max of the two values returned for the root.
// Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
// Space Complexity: O(H), where H is the height of the tree, due to the recursion stack. In the worst case (a skewed tree), this can be O(N).

class Solution {
  public:
    // Helper function returns a pair: {max sum including root, max sum excluding root}
    pair<int, int> maxSumHelper(Node* root) {
        if (root == nullptr) {
            // Base case: An empty node contributes 0 to both sums.
            return {0, 0};
        }

        // Recursively get sums from left and right children
        pair<int, int> sum1 = maxSumHelper(root->left);
        pair<int, int> sum2 = maxSumHelper(root->right);
        pair<int, int> sum;

        // Case 1: This node is included.
        // We must exclude its immediate children. So, we take the 'excluded' sums from children.
        sum.first = sum1.second + sum2.second + root->data;

        // Case 2: This node is excluded.
        // We can take the best possible sum from children (either including or excluding them).
        sum.second = max(sum1.first, sum1.second) + max(sum2.first, sum2.second);

        return sum;
    }

    // Main function to get the maximum sum
    int getMaxSum(Node* root) {
        pair<int, int> res = maxSumHelper(root);
        // The final answer is the maximum of including or excluding the root node.
        return max(res.first, res.second);
    }
};

/*
*
* Dry Run
* Let's trace with the tree: [1, 2, 3, 4, N, 5, 6]
* 1
* / \
* 2   3
* /   / \
* 4   5   6
*
* 1. maxSumHelper(4): Returns {4, 0}
* 2. maxSumHelper(nullptr) [right of 2]: Returns {0, 0}
* 3. maxSumHelper(2):
* - Children are 4 and nullptr.
* - sum1 = {4, 0}, sum2 = {0, 0}
* - sum.first (include 2): 2 + 0 (exclude 4) + 0 (exclude nullptr) = 2
* - sum.second (exclude 2): max(4, 0) + max(0, 0) = 4
* - Returns {2, 4}
*
* 4. maxSumHelper(5): Returns {5, 0}
* 5. maxSumHelper(6): Returns {6, 0}
* 6. maxSumHelper(3):
* - Children are 5 and 6.
* - sum1 = {5, 0}, sum2 = {6, 0}
* - sum.first (include 3): 3 + 0 (exclude 5) + 0 (exclude 6) = 3
* - sum.second (exclude 3): max(5, 0) + max(6, 0) = 11
* - Returns {3, 11}
*
* 7. maxSumHelper(1):
* - Children are 2 and 3.
* - sum1 = {2, 4}, sum2 = {3, 11}
* - sum.first (include 1): 1 + 4 (exclude 2) + 11 (exclude 3) = 16
* - sum.second (exclude 1): max(2, 4) + max(3, 11) = 4 + 11 = 15
* - Returns {16, 15}
*
* 8. getMaxSum(root):
* - Receives {16, 15} from maxSumHelper(1).
* - Returns max(16, 15) = 16.
*
*/
```

---

## Key Insights

The problem is a variation of the classic "House Robber" problem applied to a binary tree. The key insight is that the decision for a parent node depends only on the results of its immediate children, not the entire structure below them. By having each recursive call return the two optimal choices (include vs. exclude), we provide the parent with all the necessary information to make its own optimal choice, leading to a linear time solution.

---

## Further Exploration

If you enjoyed this problem, consider exploring these related challenges:

- **LeetCode 337: House Robber III:** This is the same problem on a different platform.
- **[GFG] Maximum path sum from any node:** Find the path with the maximum sum between any two nodes in a binary tree.
- **[GFG] Diameter of a Binary Tree:** Another classic problem that uses a similar post-order traversal technique to pass information up the tree.

---

## References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/maximum-sum-of-non-adjacent-nodes/1)
- [House Robber Problem Pattern](https://leetcode.com/tag/house-robber/)

---

## Author

Created by [imnilesh18](https://github.com/imnilesh18).

---

## Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic%20Programming-4a148c?style=for-the-badge)
![Tree](https://img.shields.io/badge/Tree-228B22?style=for-the-badge)
![Binary Tree](https://img.shields.io/badge/Binary%20Tree-228B22?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

**A gentle reminder:** The solutions and explanations in this repository are for educational purposes only. It is strongly recommended to attempt the problem on your own before referring to these solutions.
