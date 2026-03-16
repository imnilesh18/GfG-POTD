# 🌳 K Sum Paths

<p align="left">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-44.73%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</p>

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the `root` of a binary tree and an integer `k`, determine the number of **downward-only** paths where the sum of the node values in the path equals `k`.

**Note:** A path can start and end at any node within the tree but must always move **downward** (from parent to child).

---

## 💡 Examples

### Example 1

**Input:** `root = [8, 4, 5, 3, 2, N, 2, 3, -2, N, 1]`, `k = 7`

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700575/Web/Other/blobid0_1738924888.webp" alt="Tree Example 1" />
</div>

**Output:** `3`

**Explanation:** The following paths sum to `k`:

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700575/Web/Other/blobid0_1722330388.jpg" alt="Tree Example 1 Output" />
</div>

### Example 2

**Input:** `root = [1, 2, 3]`, `k = 3`

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700575/Web/Other/blobid0_1739181818.jpg" alt="Tree Example 2" />
</div>

**Output:** `2`

<details>
<summary><b>📖 Example Breakdown</b></summary>

**Explanation:**
For the tree `[1, 2, 3]` and target `k = 3`:
- Path 1: Starts at root `1` and goes left to `2`. Sum = `1 + 2 = 3`.
- Path 2: Starts at node `3` itself. Wait, looking at the graph and output, the path from root `1` to `3` is not 3, but the single node `3` itself forms a valid sub-path since it equals `k`. (Wait, from the image provided in the actual problem, path 1 -> 2 is one, and node 3 is another).
- Total valid paths = 2.

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700575/Web/Other/blobid1_1739181850.jpg" alt="Tree Example 2 Breakdown" />
</div>

</details>

---

## ⚠️ Constraints

> - `1 ≤ number of nodes ≤ 10^4`
> - `-100 ≤ node value ≤ 100`
> - `-10^9 ≤ k ≤ 10^9`

---

## 🚀 Solution

### Optimized Approach: Depth First Search (DFS) with Prefix Sum

```cpp
// Intuition: To find paths summing to 'k', we can use the prefix sum technique combined with DFS. By tracking the cumulative sum from the root to the current node, we can determine if a sub-path equals 'k' by checking if (current_sum - k) was seen earlier in the same path.
// Approach: Traverse the tree using DFS while maintaining a running sum. Use a hashmap to store the frequencies of prefix sums encountered on the current path. If (current_sum - k) exists in the map, add its frequency to the total count. After visiting a node's subtrees, backtrack by removing its prefix sum from the map to avoid affecting other branches.
// Time Complexity: O(N) where N is the number of nodes. We visit each node exactly once, and hashmap lookups/insertions are O(1) on average.
// Space Complexity: O(N) in the worst case (skewed tree) for both the recursion stack and the hashmap storing prefix sums.
class Solution {
public:
    int fill(Node* root, int k, int currSum, unordered_map<int, int>& prefixSum) {
        if (!root) {
            return 0;    // Base case: reached the end of a branch.
        }

        currSum += root->data;   // Update current cumulative sum with the current node's value.

        // Count the number of valid paths ending at the current node.
        int count = prefixSum[currSum - k];

        // Increment the frequency of the current cumulative sum.
        prefixSum[currSum]++;

        // Recursively count paths in the left and right subtrees.
        count += fill(root->left, k, currSum, prefixSum);
        count += fill(root->right, k, currSum, prefixSum);

        // Backtrack: Decrement the frequency to remove the current node's effect.
        prefixSum[currSum]--;

        return count;
    }

    // countAllPaths: Returns the total number of downward paths with sum equal to k.
    int countAllPaths(Node* root, int k) {
        unordered_map<int, int> prefixSum;

        prefixSum[0] = 1;   // Initialize with sum 0 to handle paths that equal k from the root.
        return fill(root, k, 0, prefixSum);
    }
};

/*
Dry Run
Tree: [1, 2, 3], k = 3
Initialize prefixSum map with {0: 1}.
Start at root (1): currSum = 1. target = 1 - 3 = -2 (not in map). prefixSum = {0:1, 1:1}. count = 0.
Go left to (2): currSum = 1 + 2 = 3. target = 3 - 3 = 0. map has 0 with frequency 1. count = 0 + 1 = 1.
Add 3 to map: prefixSum = {0:1, 1:1, 3:1}. Left and right children of 2 are NULL (return 0).
Backtrack at (2): prefixSum = {0:1, 1:1, 3:0}.
Go right from root to (3): currSum = 1 + 3 = 4. target = 4 - 3 = 1. map has 1 with frequency 1. count = 1 + 1 = 2.
Add 4 to map: prefixSum = {0:1, 1:1, 3:0, 4:1}. Left and right children of 3 are NULL.
Backtrack at (3): prefixSum = {0:1, 1:1, 3:0, 4:0}.
Backtrack at root (1): clean up effect of node 1.
Total paths found: 2.
*/
```

---

## 🧠 Key Insights

- **Prefix Sum + Hashing:** This is a classic 1D array problem (Subarray Sum Equals K) seamlessly adapted for trees. Instead of checking sub-arrays, we are checking continuous sub-paths.
- **Backtracking is Critical:** Trees branch out. A path sum seen on the left sub-tree should **not** influence the right sub-tree. Decrementing the frequency in the hashmap during the backtracking phase inherently prevents this cross-branch contamination.
- **Base Map Initialization:** Always initialize `prefixSum[0] = 1`. This elegantly handles cases where a path starting straight from the root perfectly equals `k`.

---

## 🔍 Further Exploration

- [Path Sum III (LeetCode 437)](https://leetcode.com/problems/path-sum-iii/) - The exact same problem on LeetCode.
- [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) - The 1D array equivalent of this tree problem.

---

## 🔗 References

- **Original Problem:** [K Sum Paths on GeeksforGeeks](https://www.geeksforgeeks.org/problems/k-sum-paths/1)

---

## 👤 Author

**Nilesh**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Tree` `DFS` `Prefix-Sum` `Hash-Map` `Backtracking` `GeeksforGeeks`