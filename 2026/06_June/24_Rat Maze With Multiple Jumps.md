# 🐀 Rat Maze With Multiple Jumps

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/rat-maze-with-multiple-jumps3852/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-38.46%25-green?style=for-the-badge" alt="Accuracy: 38.46%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Given a matrix `mat[][]` of size `n × n`, where `mat[i][j]` represents the maximum number of steps a rat can jump either forward (right) or downward from that cell, find a path for the rat to reach from the top-left cell `(0, 0)` to the bottom-right cell `(n - 1, n - 1)`. 

A cell containing `0` is blocked and cannot be used in the path. It is guaranteed that the destination cell `mat[n-1][n-1]` is not `0`.

Return an `n × n` matrix where `1` represents the cells included in the path and `0` represents the remaining cells. If no valid path exists, return `[[-1]]`.

**Note:** If multiple valid paths exist, choose the path with the **shortest possible jumps first**. For the same jump length, moving **forward (right)** should be preferred over moving **downward**.

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[2, 1, 0, 0], [3, 0, 0, 1], [0, 1, 0, 1], [0, 0, 0, 1]]
Output: 
[[1, 0, 0, 0], 
 [1, 0, 0, 1], 
 [0, 0, 0, 1], 
 [0, 0, 0, 1]]
Explanation: 
The rat starts from cell (0, 0) which contains value 2, so it can jump at most 2 steps either right or downward. 
Steps:
-> Moves downward to (1, 0) which contains value 3.
-> Jumps 3 steps right to reach (1, 3).
-> Moves downward through (2, 3) and reaches the destination cell (3, 3).
```

### Example 2
```text
Input: mat[][] = [[2, 1, 0, 0], [2, 0, 0, 1], [0, 1, 0, 1], [0, 0, 0, 1]]
Output: [[-1]]
Explanation: 
The rat starts at (0, 0) with value 2, but every possible path from there eventually reaches a cell containing 0. Since no sequence of jumps can reach the destination cell (3, 3), no valid path exists and the output is [[-1]].
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

Let's trace **Example 1**:
1. Start at `(0, 0)`. The allowed max jump is `2`.
2. Following the rules (shortest jump first, right before down), we try:
   - `Jump 1 Right` to `(0, 1)`. The value here is `1`. From `(0, 1)`, paths (Right to `(0, 2)` or Down to `(1, 1)`) lead to `0`s (dead ends). We backtrack.
   - `Jump 1 Down` to `(1, 0)`. The value here is `3`. 
3. From `(1, 0)` with max jump `3`, we try:
   - `Jump 1` (Right/Down) -> Dead ends (`0`s).
   - `Jump 2` (Right/Down) -> Dead ends (`0`s).
   - `Jump 3 Right` to `(1, 3)`. The value is `1`. This path is valid!
4. From `(1, 3)`, `Jump 1 Down` leads to `(2, 3)` (Value `1`).
5. From `(2, 3)`, `Jump 1 Down` leads to `(3, 3)`, our destination!
6. Path found successfully!

</details>

---

## ⚙️ Constraints

- `1 ≤ n ≤ 50`
- `0 ≤ mat[i][j] ≤ 20`

---

## 🛠️ Solution Approaches

### Optimized Backtracking (DFS with Dead-End Pruning)

A standard Backtracking (DFS) approach explores all possible paths systematically. However, it can revisit the same dead-end cells repeatedly from different paths, leading to an exponential worst-case time complexity (Time Limit Exceeded). We optimize this by incorporating **memoization/pruning**: when a cell completely fails to yield a valid path to the destination, we mark the cell itself as a dead-end (`mat[r][c] = 0`). This ensures we never waste time exploring that same useless cell again.

```cpp
// Intuition: We need to find a valid path prioritizing shorter jumps and rightward movement. A standard DFS can revisit the same dead-end cell multiple times from different paths, causing a Time Limit Exceeded (TLE). We can optimize this by marking failed cells as dead-ends.
// Approach: Start at (0,0). Recursively try jumping 1 to mat[r][c] steps, trying right before down. If a path leads to the destination, mark and return true. CRITICAL OPTIMIZATION: If all options from a cell fail, unmark it from the path AND set mat[r][c] = 0 to prevent future redundant visits to this dead-end.
// Time Complexity: O(n^2 * max_jump). Since we never re-evaluate a dead-end cell, each cell is processed at most once, bringing the worst-case time down drastically.
// Space Complexity: O(n^2) for the auxiliary result matrix and O(n) for the recursion call stack.

class Solution {
private:
    bool solve(int r, int c, vector<vector<int>>& mat, vector<vector<int>>& ans, int n) {
        // Reached destination cell successfully
        if (r == n - 1 && c == n - 1) {
            ans[r][c] = 1;
            return true;
        }
        
        // Return false if out of bounds or cell is a blocked/dead-end path
        if (r >= n || c >= n || mat[r][c] == 0) {
            return false;
        }
        
        // Mark current cell as part of our potential path
        ans[r][c] = 1;
        
        // Try all jump lengths starting from shortest (1) to max allowed (mat[r][c])
        for (int step = 1; step <= mat[r][c]; ++step) {
            // Priority 1: Try jumping forward (Right)
            if (c + step < n && solve(r, c + step, mat, ans, n)) {
                return true;
            }
            // Priority 2: Try jumping downward
            if (r + step < n && solve(r + step, c, mat, ans, n)) {
                return true;
            }
        }
        
        // Backtrack: Unmark the cell from the answer path
        ans[r][c] = 0;
        
        // OPTIMIZATION: Mark this cell as a dead end so we don't revisit it
        // This instantly prevents TLE on large matrices
        mat[r][c] = 0; 
        
        return false;
    }

public:
    vector<vector<int>> shortestDist(vector<vector<int>>& mat) {
        int n = mat.size();
        
        // Initialize an n x n answer matrix with 0s
        vector<vector<int>> ans(n, vector<int>(n, 0));
        
        // If a valid path is found, return the marked answer matrix
        if (solve(0, 0, mat, ans, n)) {
            return ans;
        }
        
        // If no path is found, return [[-1]]
        return {{-1}};
    }
};

/*
*
* Dry Run
*
* Input: mat = [[2, 1, 0, 0], [3, 0, 0, 1], [0, 1, 0, 1], [0, 0, 0, 1]]
* Start solve(0, 0): ans[0][0] = 1
* Try Right 1 -> solve(0, 1): ans[0][1] = 1
* Try Right 1 -> solve(0, 2): mat is 0, returns false
* Try Down 1 -> solve(1, 1): mat is 0, returns false
* Both fail. Backtrack: ans[0][1] = 0. 
* OPTIMIZATION: mat[0][1] = 0. (Now it's permanently a dead-end)
* Try Down 1 -> solve(1, 0): ans[1][0] = 1
* ... (continues testing right and down)
* Try Right 3 -> solve(1, 3): ans[1][3] = 1
* Try Down 1 -> solve(2, 3): ans[2][3] = 1
* Try Down 1 -> solve(3, 3): Destination! Returns true.
* Path bubbles up true. Final ans matrix returned!
*
*/
```

---

## 🧠 Key Insights

- **Strict Traversal Order**: The problem statement subtly dictates the exact order of the loops. The outer loop must iterate through `step` sizes sequentially starting from `1`. Inside, `right` must be called before `down`. This guarantees the first valid path found is automatically the one satisfying the shortest jump constraints.
- **Dead-End Pruning**: Standard backtracking would TLE because it wastes time repeatedly exploring paths from cells that have already been proven to be dead-ends. Modifying `mat[r][c] = 0` upon failure effectively memoizes the result, ensuring `O(N^2)` bound on cell visitations.

---

## 🚀 Further Exploration

Want to solve more problems like this? Check out:
- [Rat in a Maze Problem - I](https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1)
- [N-Queen Problem](https://www.geeksforgeeks.org/problems/n-queen-problem0315/1)
- [Word Search](https://www.geeksforgeeks.org/problems/word-search/1)

---

## 🔗 References

- **GeeksforGeeks Problem:** [Rat Maze With Multiple Jumps](https://www.geeksforgeeks.org/problems/rat-maze-with-multiple-jumps3852/1)
- **Concept Reference:** [Backtracking Algorithms (GeeksforGeeks)](https://www.geeksforgeeks.org/backtracking-algorithms/)

---

## 👨‍💻 Author

Developed and maintained by **[imnilesh18](https://github.com/imnilesh18)**.  
Follow for more DSA solutions and software development projects!

---

## 🏷️ Tags

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Backtracking](https://img.shields.io/badge/Backtracking-FF6F00?style=for-the-badge&logo=algo&logoColor=white)
![Matrix](https://img.shields.io/badge/Matrix-4B0082?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)