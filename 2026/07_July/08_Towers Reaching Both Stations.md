# 🗼 Towers Reaching Both Stations

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/geeks-island--170646/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-60.27%25-green?style=for-the-badge" alt="Accuracy: 60.27%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a matrix `mat[][]` of size `n x m`, where `mat[i][j]` represents the signal strength of a communication tower. Two control stations monitor the network:
- **Station P** covers the **top** and **left** boundaries of the grid.
- **Station Q** covers the **bottom** and **right** boundaries of the grid.

A signal can propagate from a tower to one of its neighbouring towers in the four directions (North, South, East, and West) **only if** the neighbouring tower has a signal strength **less than or equal to** that of the current tower.

Determine the number of towers `(x, y)` from which a signal can eventually reach **both** Station P and Station Q. Any tower located on a boundary covered by a station can transmit directly to that station.

---

## ⚙️ Constraints

> - $1 \le n, m \le 10^3$
> - $1 \le mat[i][j] \le 10^3$

---

## 💡 Examples

### Example 1

```text
Input: mat[][] = [[1, 2, 2, 3, 5], 
                  [3, 2, 3, 4, 4], 
                  [2, 4, 5, 3, 1], 
                  [6, 7, 1, 4, 5], 
                  [5, 1, 1, 2, 4]]
Output: 7

Explanation: 
(0, 4) & (4, 0) are part of both P & Q 
(1, 3) reaches P using (1,3)->(0,3) and Q using (1,3)->(1,4)
(1, 4) reaches P using (1,4)->(1,3)->(1,2)->(0,2) and it is on Q
(2, 2) reaches P using (2,2)->(2,1)->(2,0) and Q using (2,2)->(2,3)->(2,4)
(3, 0) is on P and reaches Q using (3,0)->(4,0)
(3, 1) reaches P using (3,1)->(3,0) and Q using (3,1)->(4,1)
```

### Example 2

```text
Input: mat[][] = [[2, 2], 
                  [2, 2]]
Output: 4

Explanation: All cells allow signals to propagate to both the stations.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
<br>

Consider **Example 2**: `mat[][] = [[2, 2], [2, 2]]`

1. **Station P** represents the top row `(0,0), (0,1)` and left column `(0,0), (1,0)`.
2. **Station Q** represents the bottom row `(1,0), (1,1)` and right column `(0,1), (1,1)`.
3. Since all elements are equal (`2`), a signal can flow anywhere. 
4. If a signal originates from `(0,0)`, it is directly on Station P, and it can flow to `(1,0)` or `(0,1)` which are directly on Station Q.
5. Consequently, signals from every single tower in this grid can reach both boundaries. Thus, the total count is `4`.

</details>

---

## 🚀 Solution Approach

### Optimized Graph Traversal (Reverse Flow DFS)

Trying to run a depth-first search from every single cell to check if it reaches both stations would lead to a Time Limit Exceeded (TLE) error, operating at $O((N \times M)^2)$. 

Instead, we use a **reverse thinking approach**. A signal naturally flows from a higher (or equal) tower to a lower (or equal) tower. If we reverse this logic and start from the boundary stations (which are our target destinations), we can climb "up" the grid. We perform DFS/BFS from the boundaries and only move to neighboring towers that have a signal strength **greater than or equal to** the current tower.

```cpp
// Intuition: Instead of checking paths from each cell to the stations, it is much more efficient to reverse the flow. By starting from the boundaries (stations) and moving inwards, we can find all reachable cells. Since water/signals flow from higher to lower/equal, reverse flow means we move to cells with greater or equal heights.
// Approach: 
// 1. Create two 2D boolean arrays `visP` and `visQ` to track cells that can reach Station P and Station Q.
// 2. Perform DFS from the top and left boundaries to populate `visP`.
// 3. Perform DFS from the bottom and right boundaries to populate `visQ`.
// 4. Traverse the grid and count cells where both `visP[i][j]` and `visQ[i][j]` are true.
// Time Complexity: O(N * M) where N is the number of rows and M is the number of columns. Each cell is visited at most once per station.
// Space Complexity: O(N * M) for the visited arrays and the recursion stack.

class Solution {
  private:
    // Helper function to perform DFS and mark reachable towers
    void dfs(int r, int c, vector<vector<int>>& mat, vector<vector<bool>>& vis) {
        vis[r][c] = true; // Mark current cell as visited
        int n = mat.size();
        int m = mat[0].size();
        
        // Direction arrays for moving Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Explore all 4 adjacent directions
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // Move if within bounds, unvisited, and neighbor's height >= current height (reverse flow)
            if(nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && mat[nr][nc] >= mat[r][c]) {
                dfs(nr, nc, mat, vis);
            }
        }
    }
    
  public:
    int countCoordinates(vector<vector<int>>& mat) {
        int n = mat.size();
        if(n == 0) return 0;
        int m = mat[0].size();
        
        // Visited arrays for both stations
        vector<vector<bool>> visP(n, vector<bool>(m, false));
        vector<vector<bool>> visQ(n, vector<bool>(m, false));
        
        // Station P is connected to the top and left boundaries
        for(int i = 0; i < n; i++) {
            if(!visP[i][0]) dfs(i, 0, mat, visP); // Left boundary
        }
        for(int j = 0; j < m; j++) {
            if(!visP[0][j]) dfs(0, j, mat, visP); // Top boundary
        }
        
        // Station Q is connected to the bottom and right boundaries
        for(int i = 0; i < n; i++) {
            if(!visQ[i][m-1]) dfs(i, m-1, mat, visQ); // Right boundary
        }
        for(int j = 0; j < m; j++) {
            if(!visQ[n-1][j]) dfs(n-1, j, mat, visQ); // Bottom boundary
        }
        
        // Count towers that can reach both stations
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(visP[i][j] && visQ[i][j]) {
                    count++;
                }
            }
        }
        
        return count;
    }
};

/*
* Dry Run
* Input: mat = [[2, 2], [2, 2]]
* * Step 1: Initialize visP and visQ as 2x2 false grids.
* Step 2: DFS for Station P (Top and Left boundaries)
* - Start at (0,0): mat[0][0]=2. Mark visP[0][0]=T. Neighbors (0,1) and (1,0) have val 2 >= 2. 
* Visit (0,1) -> visP[0][1]=T. Visit (1,0) -> visP[1][0]=T. Visit (1,1) -> visP[1][1]=T.
* - End result for visP: All cells are true.
* Step 3: DFS for Station Q (Bottom and Right boundaries)
* - Start at (1,1): mat[1][1]=2. Mark visQ[1][1]=T. Neighbors (0,1) and (1,0) have val 2 >= 2.
* Visit (0,1) -> visQ[0][1]=T. Visit (1,0) -> visQ[1][0]=T. Visit (0,0) -> visQ[0][0]=T.
* - End result for visQ: All cells are true.
* Step 4: Count intersections
* - All 4 cells have both visP and visQ as true.
* Output: 4
*/
```

---

## 🔑 Key Insights

- **Reverse Engineering the Problem:** Instead of looking for a path from a cell to the ocean/station, start from the ocean/station and find which cells can be reached by climbing "uphill".
- **Boundary Optimization:** Using DFS/BFS from boundary edges efficiently prevents calculating overlapping paths multiple times, vastly improving the performance from $O((NM)^2)$ to $O(NM)$.
- **Independent Validation:** Separating the concerns (creating separate boolean grids for Station P and Station Q) simplifies the logic to a basic `visP[i][j] && visQ[i][j]` check at the end.

---

## 🔭 Further Exploration

If you enjoyed this problem, you might want to try these related challenges:
- **Pacific Atlantic Water Flow** (LeetCode equivalent of this exact logic)
- **Rotting Oranges** (Using multi-source BFS on a grid)
- **Number of Islands** (Classic grid DFS/BFS)

---

## 🔗 References

- **GeeksforGeeks Problem:** [Towers Reaching Both Stations](https://www.geeksforgeeks.org/problems/geeks-island--170646/1)

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#DFS` `#Matrix` `#Graph-Traversal` `#GeeksforGeeks` `#C++`