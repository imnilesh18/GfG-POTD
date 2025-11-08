# 🪙 Number of paths in a matrix with k coins

| **Platform** | **Difficulty** | **Accuracy** | **Points** | **License** |
| :----------: | :------------: | :----------: | :--------: | :---------: |
| [![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-2A73CC?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/number-of-paths-in-a-matrix-with-k-coins2728/1) | ![](https://img.shields.io/badge/Difficulty-Medium-yellow.svg) | ![](https://img.shields.io/badge/Accuracy-16.96%25-red.svg) | ![](https://img.shields.io/badge/Points-4-blue.svg) | ![](https://img.shields.io/badge/License-MIT-green.svg) |

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📜 Problem Statement

You are given a matrix `mat[][]` of size $N \times M$, where each of its cells contains some coins. **Count** the number of ways to collect **exactly $k$ coins** while moving from the **top left** cell of the matrix to the **bottom right** cell.

From a cell $(i, j)$, you can only move to cell $(i+1, j)$ (Down) or $(i, j+1)$ (Right).

> **Note:** It is guaranteed that the answer will not exceed 32-bit integer limits.

---

## 📝 Examples

<details>
<summary>📖 Example Breakdown</summary>

**Input:** `k = 12`, `mat = [[1, 2, 3], [4, 6, 5], [3, 2, 1]]`

We need paths from $(0,0)$ to $(2,2)$ that sum to exactly 12.
Two valid paths are:
1.  $(0,0) \rightarrow (0,1) \rightarrow (1,1) \rightarrow (1,2) \rightarrow (2,2)$
    * Values: $1 + 2 + 6 + 5 + \text{wait... this isn't the provided explanation path}$.
    * Let's re-read the GFG explanation paths: $(1 + 2 + 6 + 2 + 1)$ and $(1 + 2 + 3 + 5 + 1)$.
    * Path 1: $(0,0)[1] \rightarrow (0,1)[2] \rightarrow (1,1)[6] \rightarrow (2,1)[2] \rightarrow (2,2)[1]$. Sum $= 12$.
    * Path 2: $(0,0)[1] \rightarrow (0,1)[2] \rightarrow (0,2)[3] \rightarrow (1,2)[5] \rightarrow (2,2)[1]$. Sum $= 12$.

**Output:** `2`

</details>

```cpp
// Example 1
Input: k = 12, mat[] = [[1, 2, 3],
                        [4, 6, 5],
                        [3, 2, 1]]
Output: 2
Explanation: There are 2 possible paths with exactly 12 coins, (1 + 2 + 6 + 2 + 1) and (1 + 2 + 3 + 5 + 1).

// Example 2
Input: k = 16, mat[] = [[1, 2, 3],
                        [4, 6, 5],
                        [9, 8, 7]]
Output: 0
Explanation: There are no possible paths that lead to sum = 16.
````

-----

## ⚠️ Constraints

  * $1 \le k \le 100$
  * $1 \le n, m \le 100$
  * $0 \le mat[i][j] \le 200$

-----

## 🧠 Solution Approaches

The problem asks for the total number of specific paths. Since we can only move down or right, and we have a target sum, this suggests a recursive approach. Because subproblems (reaching a specific cell with a specific remaining sum) overlap, we use **Dynamic Programming (Memoization)**.

### Optimized Approach (Memoization)

We define a state `dp[i][j][rem_k]` representing the number of ways to reach the bottom-right cell from `(i, j)` with `rem_k` coins left to collect.

```cpp
// Intuition: Use recursion to explore all paths (down and right). Since many paths reach the same cell with the same 'k' remaining, memoize the results to avoid redundant calculations.
// Approach: Recursive DFS with a 3D DP table [row][col][k] to store path counts for each state.
// Time Complexity: O(N * M * K) where N, M are matrix dimensions and K is the target sum. Each state is computed once.
// Space Complexity: O(N * M * K) for the 3D memoization table, plus O(N + M) for recursion stack depth.
class Solution {
  public:
    // Recursive function with memoization
    int pathCountRec(vector<vector<int>>& mat, int i, int j, int k,
                     vector<vector<vector<int>>>& dp) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Base case: Out of bounds
        if (i >= n || j >= m) return 0;
        
        // Base case: Sum exceeded (k became negative)
        if (k < 0) return 0;
        
        // Base case: Reached destination. Check if remaining k matches current cell value
        if (i == n - 1 && j == m - 1)
            return (k == mat[i][j]);
        
        // If already computed, return stored value
        if (dp[i][j][k] != -1)
            return dp[i][j][k];
        
        // Recursive step: Explore down and right moves, reducing k by current cell's value
        int down = pathCountRec(mat, i + 1, j, k - mat[i][j], dp);
        int right = pathCountRec(mat, i, j + 1, k - mat[i][j], dp);
        
        // Memoize and return total paths from this state
        return dp[i][j][k] = down + right;
    }
    
    int numberOfPath(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Initialize 3D DP table with -1
        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(m, vector<int>(k + 1, -1))
        );
        
        // Start recursion from top-left (0,0) with full target k
        return pathCountRec(mat, 0, 0, k, dp);
    }
};

/*
*
* Dry Run
* Input: mat = [[1, 2], [3, 1]], k = 4
* Start: pathCountRec(0, 0, 4) -> mat[0][0] is 1. Need 4-1 = 3 more.
* Move Down: pathCountRec(1, 0, 3) -> mat[1][0] is 3. Need 3-3 = 0 more.
* Move Down: Out of bounds -> returns 0
* Move Right: pathCountRec(1, 1, 0) -> Destination. mat[1][1] is 1. Need 0 == 1? False -> returns 0
* Result for (1,0,3) is 0 + 0 = 0
* Move Right: pathCountRec(0, 1, 3) -> mat[0][1] is 2. Need 3-2 = 1 more.
* Move Down: pathCountRec(1, 1, 1) -> Destination. mat[1][1] is 1. Need 1 == 1? True -> returns 1
* Move Right: Out of bounds -> returns 0
* Result for (0,1,3) is 1 + 0 = 1
* Total for (0,0,4) = Down(0) + Right(1) = 1
* Final Output: 1
*
*/
```

-----

## 🔑 Key Insights

  * **3D State:** A standard 2D DP `dp[i][j]` is insufficient because reaching cell `(i,j)` with 5 coins left is different from reaching it with 10 coins left. The state must include `k`.
  * **Base Case Precision:** The check `k < 0` is a crucial pruning step. The final destination check must ensure exactly `k` coins remain *including* the final cell, so we check `return (k == mat[i][j])`.
  * **Constraints Matter:** $K \le 100$ and $N, M \le 100$ make $O(N \cdot M \cdot K) \approx 10^6$ operations, which easily passes within typical time limits (usually $\approx 10^8$ ops/sec).

-----

## 🚀 Further Exploration

  * **Variant:** What if values can be negative? (The `k < 0` pruning might need adjustment if later cells could increase the sum back up, though coins usually imply positive values).
  * **Similar Problems:**
      * [Unique Paths](https://www.geeksforgeeks.org/problems/number-of-unique-paths5339/1)
      * [Minimum Path Sum](https://www.google.com/search?q=https://www.geeksforgeeks.org/problems/minimum-path-sum-in-a-grid/1)
      * [Path with Maximum Gold](https://leetcode.com/problems/path-with-maximum-gold/)

-----

## 🔗 References

  * [GFG Problem Link](https://www.geeksforgeeks.org/problems/number-of-paths-in-a-matrix-with-k-coins2728/1)

-----

## 🧑‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

-----

## ⚖️ License

This project is licensed under the MIT License. See the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.
