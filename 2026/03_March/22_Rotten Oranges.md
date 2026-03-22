# 🍊 Rotten Oranges

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/rotten-oranges2536/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-46.02%25-green?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)]()

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a matrix `mat[][]`, where each cell in the matrix can have values `0`, `1` or `2` which has the following meaning:
* **`0`** : Empty cell
* **`1`** : Cell has fresh oranges
* **`2`** : Cell has rotten oranges

Your task is to determine the **minimum time required** so that all the oranges become rotten. A rotten orange at index `(i, j)` can rot other fresh oranges at indexes `(i-1, j)`, `(i+1, j)`, `(i, j-1)`, `(i, j+1)` (up, down, left, and right) in a unit time.

**Note:** If it is impossible to rot every orange then simply return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[2, 1, 0, 2, 1], 
                  [1, 0, 1, 2, 1], 
                  [1, 0, 0, 2, 1]]
Output: 2
Explanation: 
Oranges at positions (0,0), (0,3), (1,3), and (2,3) will rot adjacent fresh oranges in successive time frames.
All fresh oranges become rotten after 2 units of time.
```

<img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/701754/Web/Other/blobid2_1773817347.jpg" alt="Explanation" />

### Example 2
```text
Input: mat[][] = [[2, 1, 0, 2, 1], 
                  [0, 0, 1, 2, 1], 
                  [1, 0, 0, 2, 1]]
Output: -1
Explanation: 
Oranges at positions (0,0), (0,3), (1,3), and (2,3) rot some fresh oranges, but the fresh orange at (2,0) can never be reached, so not all oranges can rot.
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>

**Initial State (Time = 0):**
```text
[2, 1, 0, 2, 1]
[1, 0, 1, 2, 1]
[1, 0, 0, 2, 1]
```
**Time = 1:** Rotten oranges spread to adjacent cells.
```text
[2, 2, 0, 2, 2]  -> (0,1) and (0,4) rot
[2, 0, 2, 2, 2]  -> (1,0), (1,2) and (1,4) rot
[1, 0, 0, 2, 2]  -> (2,4) rots
```
**Time = 2:** The newly rotten oranges spread to remaining fresh oranges.
```text
[2, 2, 0, 2, 2]
[2, 0, 2, 2, 2]
[2, 0, 0, 2, 2]  -> (2,0) rots
```
All oranges are now rotten. Total time = `2`.
</details>

---

## 🛑 Constraints

> - `1 ≤ mat.size() ≤ 500`
> - `1 ≤ mat[0].size() ≤ 500`
> - `mat[i][j] ∈ {0, 1, 2}`

---

## 🛠️ Solution Approach

### Depth First Search (DFS) with State Tracking

```cpp
// Intuition: We can determine the minimum time to rot all oranges by simulating the rotting process. By tracking the shortest time it takes for any rotten orange to reach a fresh orange using a 2D distance matrix, we avoid redundant paths.
// Approach: Initialize a 2D distance array with infinity. Iterate through the grid, and for every rotten orange found, trigger a DFS. During DFS, update the cell's rotting time. If a cell's previously recorded rotting time is less than or equal to the current time, stop exploring to prevent infinite loops. Finally, verify all fresh oranges; if any still holds infinity, return -1. Otherwise, return the maximum time found.
// Time Complexity: O((N * M)^2) in the worst case, as DFS might revisit cells if a shorter path is found later. Effectively heavily bounded by pruning (time >= dist[i][j]).
// Space Complexity: O(N * M) auxiliary space for the distance matrix and recursion stack depth.

class Solution {
public:
    // DFS to update minimum rot time for each cell
    void dfs(vector<vector<int>>& mat, int i, int j, int time, vector<vector<int>>& dist) {
        // Base case: Out of bounds or cell is empty
        if (i < 0 || i >= mat.size() || j < 0 || j >= mat[0].size() || mat[i][j] == 0) {
            return;
        }

        // Pruning: Stop if current path is slower or equal to an already discovered path
        if (time >= dist[i][j]) {
            return;
        }

        // Update the minimum time required for this cell
        dist[i][j] = time;

        // Traverse 4 directions
        dfs(mat, i + 1, j, time + 1, dist); // Down
        dfs(mat, i - 1, j, time + 1, dist); // Up
        dfs(mat, i, j + 1, time + 1, dist); // Right
        dfs(mat, i, j - 1, time + 1, dist); // Left
    }

    int orangesRot(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        // Distance matrix tracking minimum time to rot (initialized to infinity)
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        // Step 1: Start DFS from every initially rotten orange
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 2) {
                    // Rotten orange exists at time 0
                    dfs(mat, i, j, 0, dist);
                }
            }
        }

        // Step 2: Validate all originally fresh oranges
        int minTime = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    // Fresh orange remained untouched
                    if (dist[i][j] == INT_MAX) {
                        return -1; 
                    }
                    // Extract the maximum of the minimum times
                    minTime = max(minTime, dist[i][j]);
                }
            }
        }
        
        return minTime;
    }
};

/*
*
* Dry Run
*
Input:
mat = [[2, 1], 
       [1, 1]]

Initialization:
dist = [[INT_MAX, INT_MAX], 
        [INT_MAX, INT_MAX]]

Step 1: Traverse the grid. Find mat[0][0] == 2. Call dfs(mat, 0, 0, 0, dist).

DFS Execution starting at (0,0), time = 0:
- Cell (0,0): update dist[0][0] = 0.
- Call Down (1,0), time = 1: update dist[1][0] = 1.
   - From (1,0), call Right (1,1), time = 2: update dist[1][1] = 2.
- Call Right (0,1) from (0,0), time = 1: update dist[0][1] = 1.
   - From (0,1), call Down (1,1), time = 2: 2 is not < dist[1][1] (which is 2), so it prunes/returns.

After DFS completes:
dist = [[0, 1], 
        [1, 2]]

Step 2: Check all fresh oranges (originally 1).
- mat[0][1] is 1, dist is 1. Max time = 1.
- mat[1][0] is 1, dist is 1. Max time = 1.
- mat[1][1] is 1, dist is 2. Max time = 2.

No fresh oranges have INT_MAX. Return max time which is 2.
*
*/
```

---

## 🧠 Key Insights

1. **State Relaxation:** Although Multi-Source Breadth-First Search (BFS) is the standard and often more optimal approach for shortest-time multi-source unweighted graph problems, DFS can still be used. We simply treat it like Dijkstra's relaxation step—updating a cell's rotting time only if we find a faster route.
2. **Pruning is Essential:** The condition `if (time >= dist[i][j])` is critical. It acts as both a "visited" set and an optimization. Without it, the recursive calls would bounce back and forth between cells infinitely.
3. **Disjoint Components Check:** In the second pass over the grid, checking `dist[i][j] == INT_MAX` reliably identifies any fresh orange completely isolated from rotten ones, returning `-1` automatically.

---

## 🚀 Further Exploration

If you enjoyed this problem, you should definitely check out:
- **01 Matrix (Nearest Zero)** - A similar multi-source shortest path problem.
- **Flood Fill** - Understanding basic grid traversal and region coloring.
- **Solving this with BFS** - Try implementing a Queue-based Multi-Source BFS. It generally yields a faster runtime bound strictly to `O(N * M)`.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Rotten Oranges](https://www.geeksforgeeks.org/problems/rotten-oranges2536/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)** ---

## 🏷️ Tags

`#Matrix` `#Graph` `#DFS` `#BreadthFirstSearch` `#GeeksForGeeks` `#DataStructures`