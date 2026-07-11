<div align="center">
  
# 🟧 Longest Possible Route in a Matrix with Hurdles
  
[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-possible-route-in-a-matrix-with-hurdles/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.0%25-brightgreen?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only** > This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a binary matrix `mat[][]` of size `n × m` containing values `0` and `1`, and four integers `xs`, `ys`, `xd`, and `yd` representing the source cell `(xs, ys)` and destination cell `(xd, yd)`, find the length of the **longest possible path** from the source cell to the destination cell. 

From any cell, you can move to its adjacent cells in the **up, down, left, and right** directions.

- `1` represents a traversable cell.
- `0` represents a blocked cell that cannot be visited.
- A cell can be visited **at most once** in a path.

If the destination cannot be reached from the source, return `-1`.

---

## 🛑 Constraints

- `1 ≤ n, m ≤ 10`
- `mat[i][j] == 0` or `mat[i][j] == 1`
- The source and destination cells are always inside the matrix.

---

## 💡 Examples

### Example 1
```text
Input: 
mat[][] = [
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 
  [1, 1, 0, 1, 1, 0, 1, 1, 0, 1],
  [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
]
xs = 0, ys = 0
xd = 1, yd = 7

Output: 24
```
> **Explanation:** The longest valid path from `(0, 0)` to `(1, 7)` without revisiting any cell has a length of `24`.

### Example 2
```text
Input: 
mat[][] = [
  [1, 0, 0, 1, 0],
  [0, 0, 0, 1, 0],
  [0, 1, 1, 0, 0]
]
xs = 0, ys = 3
xd = 2, yd = 2

Output: -1
```
> **Explanation:** The destination cell `(2, 2)` cannot be reached from the source cell `(0, 3)`, so the answer is `-1`.

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>

Consider a smaller grid `2 x 2`:
```text
mat = [
  [1, 1],
  [1, 1]
]
xs = 0, ys = 0, xd = 1, yd = 1
```

Paths from `(0, 0)` to `(1, 1)`:
1. `(0, 0) -> (0, 1) -> (1, 1)` (Length = 2)
2. `(0, 0) -> (1, 0) -> (1, 1)` (Length = 2)

Maximum length is `2`. Since we cannot revisit nodes, these are the only valid simple paths.

</details>

---

## 🛠️ Solution Approaches

### **Optimized Approach: Backtracking (DFS)**
**Intuition**: To find the *longest* path, we must explore every single valid path from the source to the destination and keep track of the maximum length found. Depth First Search (DFS) combined with Backtracking allows us to exhaustively explore all possible routes while temporarily marking cells as visited to prevent cycles.

```cpp
// Intuition: We need to find the longest path without revisiting cells. Since we must explore all possible simple paths from the source to the destination, Backtracking (DFS) is the most suitable approach.
// Approach: Start DFS from the source cell. If we reach the destination, update the maximum path length. Mark the current cell as visited by temporarily setting it to 0. Explore all 4 valid adjacent cells recursively. After returning from the recursion, backtrack by restoring the cell's value to 1 so it can be used in other paths.
// Time Complexity: O(4^(n*m)) in the worst case, as from each cell we can potentially move in 4 directions, exploring all simple paths.
// Space Complexity: O(n*m) for the maximum depth of the recursion stack.

class Solution {
    int max_len = -1;

    void dfs(vector<vector<int>>& mat, int x, int y, int xd, int yd, int cur_len) {
        // If destination is reached, update global maximum length
        if (x == xd && y == yd) {
            max_len = max(max_len, cur_len);
            return;
        }

        // Mark current cell as visited to prevent cycles in current path
        mat[x][y] = 0;

        // Direction arrays for Up, Down, Left, Right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        // Explore all 4 valid neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Ensure next cell is within bounds and traversable
            if (nx >= 0 && nx < mat.size() && ny >= 0 && ny < mat[0].size() && mat[nx][ny] == 1) {
                dfs(mat, nx, ny, xd, yd, cur_len + 1);
            }
        }

        // Backtrack: restore the cell state for exploring other potential paths
        mat[x][y] = 1;
    }

  public:
    int longestPath(vector<vector<int>>& mat, int xs, int ys, int xd, int yd) {
        // Edge case: Start or destination is a hurdle
        if (mat[xs][ys] == 0 || mat[xd][yd] == 0) {
            return -1;
        }

        max_len = -1; // Reset maximum length
        dfs(mat, xs, ys, xd, yd, 0);

        return max_len;
    }
};

/*
Dry Run
Input: mat = [[1, 1], [1, 1]], xs = 0, ys = 0, xd = 1, yd = 1

1. Start dfs at (0,0), cur_len = 0.
   Mark mat[0][0] = 0.
2. Explore right (0,1):
   a. Check valid -> Yes. mat[0][1] = 0. cur_len = 1.
   b. Explore down (1,1):
      i. Reached destination (xd=1, yd=1).
      ii. max_len = max(-1, 2) = 2.
      iii. Return.
   c. Backtrack: restore mat[0][1] = 1.
3. Explore down (1,0):
   a. Check valid -> Yes. mat[1][0] = 0. cur_len = 1.
   b. Explore right (1,1):
      i. Reached destination (xd=1, yd=1).
      ii. max_len = max(2, 2) = 2.
      iii. Return.
   c. Backtrack: restore mat[1][0] = 1.
4. Backtrack: restore mat[0][0] = 1.
5. End of DFS. Return max_len = 2.
*/
```

---

## 🧠 Key Insights
- **Why not BFS?** While BFS is excellent for finding the *shortest* path, finding the *longest* simple path in a graph is an NP-Hard problem. DFS with backtracking natively explores all paths and allows us to keep track of the maximum depth traversed.
- **In-place State Tracking**: Modifying `mat[x][y]` to `0` and reverting it to `1` elegantly saves the `O(N*M)` auxiliary space that a separate `visited` matrix would have cost.

---

## 🔍 Further Exploration
If you enjoyed this problem, you might want to try these related challenges:
- **Rat in a Maze Problem - I** (GeeksforGeeks)
- **Unique Paths III** (LeetCode 980)
- **Word Search** (LeetCode 79)

---

## 📚 References
- **Original Problem**: [GeeksforGeeks - Longest Possible Route in a Matrix with Hurdles](https://www.geeksforgeeks.org/problems/longest-possible-route-in-a-matrix-with-hurdles/1)
- **Topic Reference**: [Backtracking Algorithm](https://www.geeksforgeeks.org/backtracking-algorithms/)

---

## 👨‍💻 Author

**Nilesh** - GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`Matrix` `Backtracking` `Data Structures` `Algorithms` `GeeksForGeeks`