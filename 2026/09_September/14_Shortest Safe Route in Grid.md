# 💣 Shortest Safe Route in Grid

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-358A1E?style=for-the-badge&logo=GeeksforGeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 50.58%](https://img.shields.io/badge/Accuracy-50.58%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📌 Problem Statement

Given a 2D matrix `mat[][]` of size `n × m`, where each cell is either `0` (**landmine**) or `1` (**safe**), find the minimum number of steps required to travel from any cell in the leftmost column to any cell in the rightmost column.

* You can move only in four directions: **Up**, **Down**, **Left**, and **Right**.
* A cell is **unsafe** if it contains a landmine or is directly adjacent (up, down, left, or right) to a landmine. All such cells must be avoided.
* Return `-1` if no safe path exists.

---

## 📖 Examples

### Example 1
```text
Input: mat[][] = [
  [1, 0, 1, 1, 1], 
  [1, 1, 1, 1, 1], 
  [1, 1, 1, 1, 1], 
  [1, 1, 1, 0, 1], 
  [1, 1, 1, 1, 0]
]
Output: 6
Explanation: The length of the shortest safe route from column 0 to column 4 avoiding landmines and their adjacent cells is 6.
```

<details>
<summary>📖 <b>Example 1 Breakdown</b></summary>

1. **Identify Landmines (0):** Found at `(0,1)`, `(3,3)`, and `(4,4)`.
2. **Mark Adjacent Cells Unsafe:**
   - Around `(0,1)`: `(0,0)`, `(0,2)`, `(1,1)` become unsafe.
   - Around `(3,3)`: `(2,3)`, `(4,3)`, `(3,2)`, `(3,4)` become unsafe.
   - Around `(4,4)`: `(3,4)`, `(4,3)` become unsafe.
3. **Valid Start Points (Col 0):** `(2,0)` and `(3,0)` are checked for safe entry.
4. **Shortest Safe Path:** Start at `(2,0) -> (2,1) -> (2,2) -> (1,2) -> (1,3) -> (1,4)`. Total steps = 6.
</details>

### Example 2
```text
Input: mat[][] = [
  [1, 1, 1, 1, 1], 
  [1, 1, 0, 1, 1], 
  [1, 1, 1, 1, 1]
]
Output: -1
Explanation: Landmine at (1,2) invalidates adjacent cells (0,2), (2,2), (1,1), (1,3), completely blocking any path from column 0 to column 4.
```

---

## 🔒 Constraints

> * `1 ≤ n, m ≤ 10^3`
> * `0 ≤ mat[i][j] ≤ 1`

---

## 💡 Solution Approach

### Multi-Source BFS with Matrix Preprocessing

```cpp
// Intuition: To find the shortest path in an unweighted grid from any cell in the first column to any cell in the last column, Multi-Source Breadth-First Search (BFS) is optimal. Before traversing, we must mark all landmines and their adjacent cells as unsafe to prevent stepping on or near a mine.
// Approach: Preprocess the matrix by creating a `safe` grid initialized to 1. For every landmine (cell with 0), mark it and its 4 adjacent neighbors as 0 in `safe`. Next, push all safe cells in the first column into a queue initialized with distance 1. Perform BFS level-by-level; as soon as a cell in the last column is reached, return its distance.
// Time Complexity: O(n * m) - Preprocessing takes O(n * m) time. Multi-source BFS visits each grid cell at most once, taking O(n * m) time.
// Space Complexity: O(n * m) - Auxiliary matrices `safe` and `visited` of size n x m, plus the BFS queue.

class Solution {
public:
    int shortestPath(vector<vector<int>> &mat) {
        int n = mat.size();
        int m = mat[0].size();

        // Step 1: Mark all unsafe cells
        // 1 means safe, 0 means unsafe
        vector<vector<int>> safe(n, vector<int>(m, 1));

        // Direction arrays for Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    safe[i][j] = 0; // The landmine itself is unsafe

                    // Mark 4 adjacent cells as unsafe
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];

                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            safe[ni][nj] = 0;
                        }
                    }
                }
            }
        }

        // Step 2: BFS from the first column
        // Queue stores {row, col, distance}
        queue<vector<int>> q; 
        vector<vector<int>> visited(n, vector<int>(m, 0));

        // Add all safe cells from the first column to our queue
        for (int i = 0; i < n; i++) {
            if (safe[i][0] == 1) {
                q.push({i, 0, 1}); // Starting distance is 1 (counting cells in the path)
                visited[i][0] = 1;
            }
        }

        while (!q.empty()) {
            vector<int> curr = q.front();
            q.pop();

            int r = curr[0];
            int c = curr[1];
            int dist = curr[2];

            // If we reached the last column, we found our shortest path!
            if (c == m - 1) {
                return dist;
            }

            // Check all 4 directions
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                // If the next cell is inside the grid, is safe, and hasn't been visited yet
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    if (safe[nr][nc] == 1 && visited[nr][nc] == 0) {
                        visited[nr][nc] = 1; // Mark as visited
                        q.push({nr, nc, dist + 1});
                    }
                }
            }
        }

        // If the queue empties and we never reached the last column
        return -1; 
    }
};

/*
* Dry Run
* 
* Input Matrix (3x3):
* [1, 0, 1]
* [1, 1, 1]
* [1, 1, 1]
*
* Step 1: Preprocess safe matrix
* Landmine found at (0,1).
* Unsafe cells: (0,1), (0,0), (0,2), (1,1).
* Computed `safe` Matrix:
* [0, 0, 0]
* [1, 0, 1]
* [1, 1, 1]
*
* Step 2: Initialize Queue with first column safe cells
* safe[1][0] == 1 -> push {1, 0, dist=1}, visited[1][0]=1
* safe[2][0] == 1 -> push {2, 0, dist=1}, visited[2][0]=1
* Queue: [{1, 0, 1}, {2, 0, 1}]
*
* Step 3: BFS Traversal
* Pop {1, 0, 1}: Valid neighbors evaluated -> None safe and unvisited.
* Pop {2, 0, 1}: Neighbor (2,1) is safe and unvisited.
* Push {2, 1, dist=2}, visited[2][1]=1. Queue: [{2, 1, 2}]
* Pop {2, 1, 2}: Neighbor (2,2) is safe and unvisited.
* Push {2, 2, dist=3}, visited[2][2]=1. Queue: [{2, 2, 3}]
* Pop {2, 2, 3}: Column c == 2 (m - 1). Last column reached!
* Output: 3
*/
```

---

## 🔑 Key Insights

* **Two-Phase Separation:** Separating the unsafe cell tagging phase from the pathfinding phase prevents accidentally using partially mutated state data during BFS traversal.
* **Multi-Source BFS Guarantee:** By pushing all valid starting points in column `0` into the queue simultaneously, BFS naturally guarantees finding the global shortest path in an unweighted grid.
* **Early Exit Strategy:** Because BFS processes nodes level-by-level in non-decreasing order of path length, the first time any node in column `m - 1` is popped, its distance is guaranteed to be minimal.

---

## 🧪 Further Exploration

* **Follow-up Question:** What if diagonal moves were also permitted? (Update direction vectors `dr` and `dc` to include 8 directions).
* **Related Problems:**
  * [Rotting Oranges](https://www.geeksforgeeks.org/problems/rotting-oranges2536/1)
  * [Nearest Cell Having 0 or 1](https://www.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1)
  * [Steps by Knight](https://www.geeksforgeeks.org/problems/steps-by-knight5927/1)

---

## 📚 References

* **GeeksforGeeks Problem Page:** [Find Shortest Safe Route in a Matrix](https://www.geeksforgeeks.org/problems/find-shortest-safe-route-in-a-matrix/1)

---

## 👤 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`bfs` `graph` `matrix` `grid-traversal` `geeksforgeeks` `cpp`
