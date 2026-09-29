# ♘ Steps by Knight

<p align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-37.32%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</p>

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a square chessboard of size `n × n`, the initial position `knightPos` and target position `targetPos` of a Knight are given. Find the **minimum number of moves** required for the Knight to reach `targetPos`.

A Knight moves in an **L-shape**, covering 2 cells in one direction and 1 cell perpendicular to it. From `(x, y)`, it can move to:
`(x ± 2, y ± 1)` and `(x ± 1, y ± 2)`

This gives at most 8 possible moves.

> **Note:** The positions are given using **1-based indexing**.

---

## 💡 Examples

### Example 1
```text
Input: n = 3, knightPos[] = [3, 3], targetPos[]= [1, 2]
Output: 1
Explanation: Knight takes 1 step to reach from (3, 3) to (1, 2).
```

### Example 2
```text
Input: n = 6, knightPos[] = [1, 3], targetPos[] = [5, 1]
Output: 2
Explanation: The Knight takes 2 steps to reach from (1, 3) to (5, 0): 
(1, 3) -> (3, 2) -> (5, 1)  
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>
Let's analyze Example 2 step-by-step:

1. **Initial Position**: `(1, 3)`
2. **Target Position**: `(5, 1)`
3. **Move 1**: The knight moves 2 units down and 1 unit left to reach `(3, 2)`.
4. **Move 2**: The knight moves 2 units down and 1 unit left again to reach the target `(5, 1)`.
5. Minimum steps required = 2.
</details>

---

## ⚠️ Constraints

> - `1 ≤ n ≤ 1000`
> - `knightPos.size() == 2`
> - `targetPos.size() == 2`
> - `1 ≤ knightPos[i], targetPos[i] ≤ n`

---

## 🛠️ Solution Approach

### Breadth-First Search (BFS)
Finding the "minimum steps" or "shortest path" in an unweighted grid is a classic Graph problem perfectly suited for **Breadth-First Search (BFS)**. BFS explores all reachable nodes level by level, ensuring that the first time we reach the target node, we have done so in the minimum possible steps.

```cpp
// Intuition: To find the shortest path in an unweighted grid, Breadth-First Search (BFS) is the optimal approach as it guarantees finding the target in minimum steps.
// Approach: Convert 1-based indexing to 0-based. Initialize a queue to perform BFS storing coordinates and step count. Track visited cells to avoid infinite loops. Process 8 possible knight moves level-by-level until the target is reached.
// Time Complexity: O(n^2), as in the worst case, every cell of the n x n board is visited exactly once.
// Space Complexity: O(n^2), auxiliary space required for the visited matrix and the BFS queue.

class Solution {
  public:
    int minStepToReachTarget(vector<int>& knightPos,
                             vector<int>& targetPos, int n) {

        // Convert 1-based indexing to 0-based indexing
        int x = knightPos[0] - 1;
        int y = knightPos[1] - 1;
        int tx = targetPos[0] - 1;
        int ty = targetPos[1] - 1;

        // All 8 possible Knight moves
        int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
        int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

        // Queue stores position and number of steps
        queue<pair<pair<int, int>, int>> q;

        // Mark visited cells to avoid redundant processing
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // Start BFS from the initial position
        q.push({{x, y}, 0});
        visited[x][y] = true;

        while (!q.empty()) {
            // Extract current coordinates and step count
            int x = q.front().first.first;
            int y = q.front().first.second;
            int steps = q.front().second;

            q.pop();

            // If target is reached, return the steps
            if (x == tx && y == ty)
                return steps;

            // Try all 8 possible Knight moves
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                // Check if the new position is valid and unvisited
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    !visited[nx][ny]) {

                    visited[nx][ny] = true;

                    // Add the new position with updated steps
                    q.push({{nx, ny}, steps + 1});
                }
            }
        }

        // Return -1 if unreachable (not possible on a valid open board)
        return -1;
    }
};

/*
*
* Dry Run
* Input: n = 3, knightPos = [3, 3], targetPos = [1, 2]
* 
* Setup (0-based): 
* Start: (2, 2) | Target: (0, 1)
* Queue: [ { {2, 2}, 0 } ]
* Visited: [2][2] = true
* 
* Step 0:
* Pop: { {2, 2}, 0 }. Current = (2,2). Is Target? No.
* Explore 8 directions from (2, 2):
* - Move (-2, -1) results in valid coords: (0, 1)
* - (0, 1) is unvisited. Mark visited[0][1] = true
* Queue becomes: [ { {0, 1}, 1 } ]
* 
* Step 1:
* Pop: { {0, 1}, 1 }. Current = (0, 1). Is Target? Yes!
* Return steps: 1
* 
* Final Output: 1
*
*/
```

---

## 🧠 Key Insights
- **Why BFS?** Since all knight moves have an equal "weight" (1 step), BFS guarantees that the first time we encounter the destination, it is via the shortest path. Depth-First Search (DFS) would wander aimlessly and require exhaustively checking all paths.
- **State Tracking:** Using a 2D boolean `visited` array is crucial. A chessboard has `N^2` cells, but a knight's move tree expands factorially ($8^d$). Avoiding re-visitation keeps the time bound to $O(N^2)$.
- **1-Based to 0-Based:** Matrix boundary conditions `(0 to N-1)` are easier to write and less error-prone when using 0-based indexing.

---

## 🔍 Further Exploration
Want to practice similar Graph and BFS logic? Check out these related problems:
1. **Rotten Oranges** (Classic multi-source BFS)
2. **Word Ladder** (BFS for shortest transformation sequence)
3. **Knight Probability in Chessboard** (DP / Graph variations on Knight moves)

---

## 🔗 References
- **GeeksforGeeks Problem:** [Steps by Knight](https://www.geeksforgeeks.org/problems/steps-by-knight5927/1)

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`Graph` `BFS` `Queue` `Shortest Path` `GeeksforGeeks` `C++`