# 🟥 Longest Increasing Path in a Matrix

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/longest-increasing-path-in-a-matrix/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty: Hard" />
  <img src="https://img.shields.io/badge/Accuracy-44.5%25-blue?style=for-the-badge" alt="Accuracy: 44.5%" />
  <img src="https://img.shields.io/badge/Points-8-orange?style=for-the-badge" alt="Points: 8" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a matrix with `n` rows and `m` columns. Your task is to find the length of the longest path in the matrix with the following constraints:

1. The values in the path must be **strictly increasing**. For example, if a path of length `k` has values `a1, a2, a3, .... ak`, then for every `i` from `[2, k]` this condition must hold: `ai > ai-1`.
2. No cell should be revisited in the path.
3. From each cell, you can move in any of the four directions: **left, right, up, or down**.
4. You are not allowed to move diagonally or move outside the boundary.

---

## 💡 Examples

```text
Input: n = 3, m = 3, matrix[][] = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
Output: 5
Explanation: One such path is 1 -> 2 -> 3 -> 6 -> 9, where each number is strictly greater than the previous.

```

```text
Input: n = 3, m = 3, matrix[][] = [[3, 4, 5], [6, 2, 6], [2, 2, 1]]
Output: 4
Explanation: One of the longest increasing paths is 3 -> 4 -> 5 -> 6.

```

Consider the first example:

```
1  2  3
4  5  6
7  8  9

```

If we start at `1` (0,0), our possible valid moves (strictly increasing) are to `2` (Right) or `4` (Down).
If we trace the path through `1 -> 2 -> 3`, from `3` the only valid increasing adjacent cell is `6` (Down). From `6`, the valid cell is `9` (Down).
This gives the path `1 -> 2 -> 3 -> 6 -> 9`, which has a total length of `5`.

---

## 🚀 Constraints

* `1 <= n, m <= 1000`
* `0 <= matrix[i][j] <= 2^30`

---

## 🧠 Solution Approaches

### Depth-First Search (DFS) with Memoization

Exploring every path from every cell using a basic DFS would lead to massive time complexity due to overlapping subproblems (computing the longest path from the same cell multiple times). We optimize this using **Memoization**. We create a `dp` table to cache the longest path length starting from any given cell. If a cell has already been processed, we simply retrieve its cached result.

```cpp
// Intuition: A standard DFS explores all paths, leading to exponential time complexity due to overlapping subproblems. By storing (memoizing) the longest path starting from each cell, we avoid redundant calculations and process each cell exactly once.
// Approach:
// 1. Initialize a 2D dp array with -1 to cache the longest path lengths for each cell.
// 2. Iterate through every cell in the matrix and start a DFS if not already computed.
// 3. In DFS, check all 4 adjacent directions. If a neighbor is strictly greater, recursively find its longest path.
// 4. Update the current cell's maximum path length (1 + max of valid neighbors) and store it in dp.
// 5. Keep track of the overall maximum path length found across all cells and return it.
// Time Complexity: O(n * m) - Each cell is visited and its result is computed only once due to memoization.
// Space Complexity: O(n * m) - Auxiliary space is required for the dp table and the recursion stack.

class Solution {
public:
    // Direction vectors for moving Up, Down, Left, Right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<int>>& dp, int n, int m) {
        // Return the cached result if already computed
        if (dp[x][y] != -1) {
            return dp[x][y];
        }

        int maxLength = 1;

        // Explore all 4 valid directions
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // Check boundaries and ensure the strictly increasing condition
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] > matrix[x][y]) {
                maxLength = max(maxLength, 1 + dfs(nx, ny, matrix, dp, n, m));
            }
        }

        // Cache the max path length for this cell and return
        return dp[x][y] = maxLength;
    }

    int longIncPath(vector<vector<int>> &matrix, int n, int m) {
        if (n == 0 || m == 0) return 0;

        // dp[i][j] stores the longest increasing path starting from cell (i, j)
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int maxPath = 0;

        // Try starting the DFS from every cell in the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maxPath = max(maxPath, dfs(i, j, matrix, dp, n, m));
            }
        }

        return maxPath;
    }
};

/*
*
* Dry Run
* Input: matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]], n = 3, m = 3
*
* 1. Initialize dp table of 3x3 with -1. maxPath = 0.
* 2. Start looping i=0, j=0. matrix[0][0] = 1.
* 3. dfs(0, 0) starts:
*    -> Explores right (0,1): matrix[0][1] = 2 (2 > 1). Calls dfs(0,1).
*    -> dfs(0,1) explores right (0,2): matrix[0][2] = 3. Calls dfs(0,2).
*    -> dfs(0,2) explores down (1,2): matrix[1][2] = 6. Calls dfs(1,2).
*    -> dfs(1,2) explores down (2,2): matrix[2][2] = 9. Calls dfs(2,2).
*    -> dfs(2,2) has no strictly greater neighbors. Returns 1. dp[2][2] = 1.
*    -> dfs(1,2) gets max 1+1=2. dp[1][2] = 2.
*    -> dfs(0,2) gets max 1+2=3. dp[0][2] = 3.
*    -> dfs(0,1) gets max 1+3=4. dp[0][1] = 4.
*    -> dfs(0,0) gets max 1+4=5. dp[0][0] = 5.
* 4. maxPath updates to 5.
* 5. Other cells will directly return cached values or compute shorter paths since they hit already-computed cells.
* 6. Final returned maxPath is 5.
*
*/

```

---

## 🔑 Key Insights

* **Graph Traversal Analogy:** The matrix can be viewed as a Directed Acyclic Graph (DAG) where directed edges exist between adjacent cells if one is strictly greater than the other.
* **Eliminating Redundancy:** Since the problem asks for strictly increasing paths, cycles are impossible. This property guarantees our memoization will safely compute the longest path without getting caught in infinite loops, allowing us to drop the `visited` array typically required for DFS in matrices.

---

## 🔭 Further Exploration

* Number of Paths in a Matrix with Obstacles
* Longest Decreasing Subsequence
* Find the shortest path in a matrix with conditions

---

## 🔗 References

* **Original Problem:** [Longest Increasing Path in a Matrix (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/longest-increasing-path-in-a-matrix/1)

---

## ✍️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `Dynamic Programming`
* `Depth-First Search (DFS)`
* `Memoization`
* `Matrix`
* `GeeksforGeeks`