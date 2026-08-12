<div align="center">
  <h1>🧗‍♂️ Adventure in a Maze</h1>
  <p>
    <a href="https://www.geeksforgeeks.org/problems/adventure-in-a-maze2051/1"><img src="https://img.shields.io/badge/-GeeksforGeeks-2F8D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks"></a>
    <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty">
    <img src="https://img.shields.io/badge/Accuracy-39.96%25-green?style=for-the-badge" alt="Accuracy">
    <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points">
    <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License"></a>
  </p>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org) problem.

---

## 📜 Problem Statement

Given a maze represented as an $n \times n$ grid, `grid[][]`, using 0-based indexing. Each cell contains one of the values 1, 2, or 3, which determines the direction(s) you are allowed to move from that cell:
*   **1** - you may move **Right** only.
*   **2** - you may move **Down** only.
*   **3** - you may move **Right or Down** (both directions are available).

You start at the top-left cell `(0, 0)` (the Entry) and must reach the bottom-right cell `(n-1, n-1)` (the Exit), following the movement rule of each cell you pass through. You are never allowed to move outside the boundaries of the grid.

The **Adventure** of a path is the sum of the values of all cells visited along that path (including both the entry and exit cells).

Find the **total number of distinct valid paths** from Entry to Exit, and among all such paths, the **maximum possible Adventure**. Return the answer as `[totalPaths, maxAdventure]`.

*Note: Return `totalPaths` modulo $10^9 + 7$, `maxAdventure` needs no modulo, as it stays small regardless of grid size.*

---

## 💡 Examples

### Example 1

```text
Input: grid[][] = [[3, 2], [1, 3]]
Output: [2, 8]
```

<details>
<summary>📖 Example Breakdown</summary>

There are 2 valid paths from `[0, 0]` to `[1, 1]`:
*   **Path 1:** `[0, 0]` -> `[0, 1]` -> `[1, 1]`, values 3 + 2 + 3 = **8**
*   **Path 2:** `[0, 0]` -> `[1, 0]` -> `[1, 1]`, values 3 + 1 + 3 = **7**

The maximum Adventure among these is **8**, so the output is `[2, 8]`.
</details>

### Example 2

```text
Input: grid[][] = [[1, 1, 3, 2, 1], [3, 2, 2, 1, 2], [1, 3, 3, 1, 3], [1, 2, 3, 1, 2], [1, 1, 1, 3, 1]]
Output: [4, 18]
Explanation: There are 4 valid paths from Entry to Exit, with total Adventures 18, 17, 17, and 16 respectively. The maximum among these is 18, so the output is [4, 18].
```

---

## 🚫 Constraints

> *   **$1 \le n \le 100$**
> *   Expected Time Complexity: $O(n^2)$
> *   Expected Auxiliary Space: $O(n^2)$ *(Note: The provided solution optimizes this to $O(n)$)*

---

## 💻 Solution Approaches

### Space-Optimized Bottom-Up Dynamic Programming

We can model this as a DP problem where we calculate the result for a given cell based on the cells immediately to its Right and Bottom. By evaluating the grid backwards from the Exit `(n-1, n-1)` to the Entry `(0, 0)`, we can build up the number of valid paths and the maximum adventure score. To save memory, instead of maintaining a full 2D table, we only maintain the "current" row and the "next" row below it.

```cpp
// Intuition: The problem requires counting paths and maximizing the sum in a grid with directional constraints. Since cell transitions only go Right or Down, computing from bottom-right to top-left ensures subproblems are solved first.
// Approach: Iterate backwards through the matrix. For every cell, evaluate if it can move Right (add path counts from `j+1` and max adventure) and/or Down (add path counts from `i+1` and max adventure). Modulo arithmetic is applied strictly to path counts. Keep only 1D arrays for the current and bottom rows to optimize space to O(N).
// Time Complexity: O(n^2) because we visit every cell in the n x n grid exactly once.
// Space Complexity: O(n) because we only store two rows (current and next) instead of a full n x n DP matrix.
class Solution {
  public:
    vector<int> findWays(vector<vector<int>> &grid)
    {
        const int MOD = 1e9 + 7;
        int n = grid.size();
    
        // Arrays to store the data of the "next" row below (i + 1)
        vector<int> nextWays(n, 0);
    
        // Initialize as unreachable (-1)
        vector<int> nextAdv(n, -1);
    
        // Iterate backwards from the bottom row to the top row
        for (int i = n - 1; i >= 0; i--)
        {
            vector<int> currWays(n, 0); // Paths from current row cells
            vector<int> currAdv(n, -1); // Max adventure from current row cells
    
            for (int j = n - 1; j >= 0; j--)
            {
                // Base Case: Bottom-right cell (The Exit)
                if (i == n - 1 && j == n - 1)
                {
                    currWays[j] = 1;
                    currAdv[j] = grid[i][j];
                    continue; // Base case established, move to next cell
                }
    
                long long totalWays = 0;
                int maxAdventure = -1;
                int cellValue = grid[i][j];
    
                // Option 1: Move Right (Valid for cell values 1 and 3)
                if (cellValue == 1 || cellValue == 3)
                {
                    // Check if right neighbor is within boundaries and reachable
                    if (j + 1 < n && currAdv[j + 1] != -1)
                    {
                        totalWays = (totalWays + currWays[j + 1]) % MOD;
                        maxAdventure = max(maxAdventure, grid[i][j] + currAdv[j + 1]);
                    }
                }
    
                // Option 2: Move Down (Valid for cell values 2 and 3)
                if (cellValue == 2 || cellValue == 3)
                {
    
                    // Check if bottom neighbor is within boundaries and reachable
                    if (i + 1 < n && nextAdv[j] != -1)
                    {
                        totalWays = (totalWays + nextWays[j]) % MOD;
                        maxAdventure = max(maxAdventure, grid[i][j] + nextAdv[j]);
                    }
                }
    
                currWays[j] = totalWays; // Assign computed paths
                currAdv[j] = maxAdventure; // Remains -1 if no valid path exists
            }
    
            // Move row states upwards efficiently using std::move
            nextWays = move(currWays);
            nextAdv = move(currAdv);
        }
    
        // Results are aggregated back at the entry point (0, 0)
        int finalPaths = nextWays[0];
        int finalAdv = (nextAdv[0] == -1) ? 0 : nextAdv[0]; // If unreachable, adventure is 0
    
        return {finalPaths, finalAdv};
    }
};

/*
Dry Run

Input: grid = [[3, 2], [1, 3]]
n = 2, MOD = 10^9 + 7

Initial Arrays:
nextWays = [0, 0]
nextAdv = [-1, -1]

Row i = 1 (Bottom Row):
j = 1 (Exit): Base case -> currWays[1] = 1, currAdv[1] = 3
j = 0: Value is 1 (Right only). Looks at (1, 1). Reachable!
currWays[0] = currWays[1] = 1
currAdv[0] = 1 + 3 = 4
Update for next row: nextWays = [1, 1], nextAdv = [4, 3]

Row i = 0 (Top Row):
j = 1: Value is 2 (Down only). Looks at (1, 1). Reachable!
currWays[1] = nextWays[1] = 1
currAdv[1] = 2 + 3 = 5
j = 0 (Entry): Value is 3 (Both).
Looks Right (0, 1): paths = 1, adv = 3 + 5 = 8
Looks Down (1, 0): paths += 1 (total 2), adv = max(8, 3 + 4) = 8
currWays[0] = 2, currAdv[0] = 8
Update for final results: nextWays = [2, 1], nextAdv = [8, 5]

Final Output: nextWays[0] = 2, nextAdv[0] = 8
Return: [2, 8]
*/
```

---

## 🧠 Key Insights

*   **Bottom-Up Advantage:** Starting from the destination allows us to know strictly whether a path to the exit exists before aggregating values upwards. If a cell evaluates to `-1` max adventure, it means it is a dead end.
*   **State Reduction:** A classic DP matrix for this problem would take $O(n^2)$ space. By observing that row `i` only ever checks row `i` (for Right moves) and row `i+1` (for Down moves), we safely reduce memory to just two 1D arrays of size $n$.
*   **Modular Arithmetic:** Paths can grow exponentially. Applying modulo arithmetic at each addition `(totalWays + validNeighbor) % MOD` prevents integer overflow issues while adhering to problem constraints.

---

## 🔍 Further Exploration

*   [Rat in a Maze Problem - I](https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1)
*   [Unique Paths](https://leetcode.com/problems/unique-paths/)
*   [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

---

## 🔗 References

*   **GeeksforGeeks Problem:** [Adventure in a Maze](https://www.geeksforgeeks.org/problems/adventure-in-a-maze2051/1)

---

## 👨‍💻 Author

*   GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Dynamic Programming` `#Matrix` `#GeeksforGeeks` `#Algorithms` `#C++`