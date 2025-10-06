# ♞ The Knight's Tour Problem

[![GFG](https://img.shields.io/badge/GeeksforGeeks-29620A?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-60.38%25-green.svg?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1)
[![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1).

---

## Problem Statement

You are given an integer `n`. There is an `n x n` chessboard with a Knight starting at the top-left corner `(0, 0)`. Your task is to determine a valid **Knight's Tour**, where the Knight visits every square exactly once, following the standard movement rules of a chess Knight (two steps in one direction and one step perpendicular). For example, if a Knight is placed at cell (2, 2), in one move it can move to any of the following cells: (4, 3), (4, 1), (0, 3), (0, 1), (3, 4), (3, 0), (1, 4), and (1, 0).

You have to return the order in which each cell is visited. If a solution exists, return the sequence of numbers (starting from 0) representing the order of visited squares. If no solution is possible, return an empty list.

**Note:** You can return any valid ordering. If it is correct, the driver code will print `true`; otherwise, it will print `false`.

---

## Examples

<details>
<summary><b>📖 Example Breakdown</b></summary>

### Example 1: `n = 5`

**Input:** `n = 5`

**Output:**

```
[[0, 11, 2, 17, 20],
 [3, 16, 19, 12, 7],
 [10, 1, 6, 21, 18],
 [15, 4, 23, 8, 13],
 [24, 9, 14, 5, 22]]
```

**Explanation:** A possible Knight's Tour in a 5x5 chessboard is given above, where each number represents the step at which the Knight visits that cell, starting from (0, 0) as step 0.

### Example 2: `n = 4`

**Input:** `n = 4`

**Output:** `[]`

**Explanation:** For `n = 4`, it is not possible to have a valid Knight's Tour, so you have to return an empty list.

</details>

---

## Constraints

- `1 ≤ n ≤ 6`

---

## Solution Approaches

### Backtracking Approach

The core idea is to use a backtracking algorithm to explore all possible paths for the Knight. We start at `(0, 0)` and recursively try all 8 possible moves. If a move is valid (within the board and not yet visited), we mark the square and recurse. If the recursive call doesn't lead to a solution, we backtrack by un-marking the square.

#### C++ Solution

```cpp
// Intuition: The problem asks for a path that visits every square on a chessboard exactly once, which is a classic backtracking problem. We can explore paths recursively, and if a path leads to a dead end, we backtrack and try another.
// Approach:
// 1. Initialize an n x n board with -1 to indicate that no squares have been visited.
// 2. Start the tour from the top-left corner (0, 0) and mark it as step 0.
// 3. Use a recursive utility function `knightTourUtil` that takes the current position (x, y), the current step number, the board size n, and the board itself.
// 4. The base case for the recursion is when the step number equals n*n, meaning all squares have been visited. In this case, a solution is found.
// 5. In the recursive function, iterate through all 8 possible moves of a knight.
// 6. For each move, check if the new position is "safe" (within the board and not yet visited).
// 7. If the move is safe, mark the new square with the current step number and make a recursive call for the next step from the new position.
// 8. If the recursive call returns true, it means a solution has been found, so propagate this true value up the call stack.
// 9. If the recursive call returns false, it means this move did not lead to a solution, so backtrack by resetting the square to -1 and try the next move.
// 10. If all 8 moves are tried and none lead to a solution, return false.
// Time Complexity: O(8^(n^2)), as from each of the n*n cells, we have 8 choices.
// Space Complexity: O(n^2) for the board and the recursion stack.

class Solution {
public:
    // Arrays to represent the 8 possible moves of a knight from a position (x, y)
    // dx for change in x-coordinate, dy for change in y-coordinate
    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    // Utility function to check if a move to (x, y) is valid
    bool isSafe(int x, int y, int n, vector<vector<int>> &board) {
        // A move is safe if:
        // 1. The new position is within the board boundaries (0 to n-1).
        // 2. The square has not been visited yet (marked as -1).
        return (x >= 0 && y >= 0 && x < n &&
                y < n && board[x][y] == -1);
    }

    // Recursive backtracking function to find the Knight's Tour
    bool knightTourUtil(int x, int y, int step, int n, vector<vector<int>> &board) {

        // Base case: If all squares are visited, the tour is complete.
        // The 'step' variable is the count of visited squares. When it equals n*n, we're done.
        if (step == n * n) {
            return true;
        }

        // Try all 8 possible moves from the current position (x, y)
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i]; // Calculate the next x-coordinate
            int ny = y + dy[i]; // Calculate the next y-coordinate

            // If the next move is valid
            if (isSafe(nx, ny, n, board)) {
                // Make the move: mark the square with the current step number
                board[nx][ny] = step;

                // Recur for the next step from the new position
                if (knightTourUtil(nx, ny, step + 1, n, board)) {
                    // If the recursive call finds a solution, propagate 'true' up
                    return true;
                }

                // If the move doesn't lead to a solution, backtrack:
                // Un-mark the square (reset to -1) and try the next move in the loop
                board[nx][ny] = -1;
            }
        }

        // If no move from the current position leads to a solution, return false
        return false;
    }

    // Main function to initiate the Knight's Tour
    vector<vector<int>> knightTour(int n) {
        // Initialize the n x n board with -1 to mark all squares as unvisited
        vector<vector<int>> board(n, vector<int>(n, -1));

        // The Knight starts at the top-left corner (0, 0). This is step 0.
        board[0][0] = 0;

        // Start the backtracking process from (0, 0) for the next step (step 1)
        if (knightTourUtil(0, 0, 1, n, board)) {
            // If the utility function returns true, a solution was found. Return the board.
            return board;
        }

        // **CORRECTION**: If no solution is found, return an empty vector as required.
        return {};
    }
};

/*
*
* Dry Run (n = 3)
*
* Initial board:
* [[0, -1, -1],
* [-1, -1, -1],
* [-1, -1, -1]]
*
* Start at (0, 0), step = 1.
* Possible moves from (0,0): (2,1), (1,2)
* Try move to (2,1): board[2][1] = 1.
* New board:
* [[0, -1, -1],
* [-1, -1, -1],
* [-1, 1, -1]]
*
* From (2,1), step = 2.
* Possible moves: (0,2), (1,3) - invalid, (3,3) - invalid, (4,2) - invalid, (4,0) - invalid, (3,-1) - invalid, (1,-1) - invalid, (0,0) - visited.
* Try move to (0,2): board[0][2] = 2.
* ... and so on. The algorithm will explore paths, and if it hits a dead end, it will backtrack.
* For n=3, no solution exists, so the function will eventually return an empty vector.
*/
```

---

## Key Insights

- **Backtracking is essential** for this type of problem, where we need to explore a sequence of choices and can determine that a path is incorrect partway through.
- The problem has a **high time complexity** due to the large number of possible paths (branching factor of 8). For small `n`, it's feasible, but it becomes impractical for larger boards.
- The solution might not be unique; any valid tour is an acceptable answer.

---

## Further Exploration

- **Warnsdorff's Rule:** A heuristic for finding a knight's tour that often works well in practice. The rule is to always move to the square from which the knight will have the fewest onward moves.
- **Closed vs. Open Tours:** A closed tour is one where the knight's final move lands it on a square that is one knight's move away from the starting square. An open tour is any other valid tour.
- **Larger `n`:** For larger values of `n`, more advanced algorithms or heuristics are needed to find a solution in a reasonable amount of time.

---

## References

- [GeeksforGeeks Problem: The Knight's Tour Problem](https://www.geeksforgeeks.org/problems/the-knights-tour-problem/1)
- [Wikipedia: Knight's Tour](https://en.wikipedia.org/wiki/Knight%27s_tour)

---

## Author

- [imnilesh18](https://github.com/imnilesh18)

---

## Tags

`backtracking` `recursion` `matrix` `geeksforgeeks` `gfg-potd`

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder: The solutions are for educational purposes. Always try to solve problems on your own first!**
