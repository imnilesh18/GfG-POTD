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

### Backtracking (Depth First Search)

We systematically traverse the matrix starting from `(0, 0)`. At each valid cell, we attempt every possible jump size from `1` up to the value of the cell. For each jump size, we always attempt moving **Right** before moving **Down** to adhere to the exact problem requirements. If an attempted move leads to a dead end (a cell with `0`), we backtrack and explore the next possible option. 

```cpp
// Intuition: We need to find a valid path to the bottom-right corner using variable jump lengths. By utilizing Backtracking (DFS), we can systematically explore paths prioritizing shorter jumps and rightward movement as strictly required.
// Approach: Start at (0,0). For the current cell, recursively try jumping 1 to mat[r][c] steps. For each step size, first try moving right, then down. If a move leads to the destination (n-1, n-1), mark it and return true. If all options from a cell fail, backtrack by unmarking the cell and returning false.
// Time Complexity: O(n * n * (max element of mat)). In the worst case, the DFS explores paths bounded by the matrix dimensions and the maximum allowed jumps at each cell.
// Space Complexity: O(n * n) for the auxiliary result matrix and O(n) for the recursion call stack, making overall extra space effectively O(n^2).

class Solution {
private:
    bool solve(int r, int c, vector<vector<int>>& mat, vector<vector<int>>& ans, int n) {
        // Reached destination cell successfully
        if (r == n - 1 && c == n - 1) {
            ans[r][c] = 1;
            return true;
        }
        
        // Return false if out of bounds or cell is a blocked path
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
        
        // Backtrack: Unmark the cell if no valid path exists from here
        ans[r][c] = 0;
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

Dry Run:
Input: mat = [[2, 1, 0, 0], [3, 0, 0, 1], [0, 1, 0, 1], [0, 0, 0, 1]]
n = 4
Start solve(0, 0):
ans[0][0] = 1. mat[0][0] = 2.
  step = 1:
    Try right -> solve(0, 1). mat[0][1] = 1.
      ans[0][1] = 1. step = 1:
        Try right -> solve(0, 2). mat[0][2] = 0. Returns false.
        Try down -> solve(1, 1). mat[1][1] = 0. Returns false.
      ans[0][1] = 0 (Backtrack). Returns false.
    Try down -> solve(1, 0). mat[1][0] = 3.
      ans[1][0] = 1.
      step = 1:
        Try right -> solve(1, 1). mat[1][1] = 0. Returns false.
        Try down -> solve(2, 0). mat[2][0] = 0. Returns false.
      step = 2:
        Try right -> solve(1, 2). mat[1][2] = 0. Returns false.
        Try down -> solve(3, 0). mat[3][0] = 0. Returns false.
      step = 3:
        Try right -> solve(1, 3). mat[1][3] = 1.
          ans[1][3] = 1. step = 1:
            Try down -> solve(2, 3). mat[2][3] = 1.
              ans[2][3] = 1. step = 1:
                Try down -> solve(3, 3). Destination reached! Returns true.
              Returns true.
          Returns true.
      Returns true.
Returns true.

Final ans matrix matches the expected output!
*/
```

---

## 🧠 Key Insights

- **Strict Traversal Order**: The problem statement subtly dictates the exact order of the loops. The outer loop must iterate through `step` sizes sequentially starting from `1`. Inside, `right` must be called before `down`. This guarantees the first valid path found is automatically the one satisfying the shortest jump constraints.
- **Backtracking Mechanics**: Marking the `ans` matrix actively serves to store the current path history. If all recursive possibilities from a given cell return `false`, we must unmark `ans[r][c] = 0` to "clean up" our tracks.

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