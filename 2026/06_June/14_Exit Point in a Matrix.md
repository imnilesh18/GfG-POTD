# 🚪 Exit Point in a Matrix

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/exit-point-in-a-matrix0905/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-E4A12B?style=for-the-badge)](#)
[![Accuracy: 50.0%](https://img.shields.io/badge/Accuracy-50.0%25-17A2B8?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-007BFF?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a matrix `mat[][]` of size `n x m` consisting of `0`s and `1`s. You start at the top-left cell `(0, 0)` and initially move in the left-to-right direction (i.e., towards the right).

While traversing the matrix, you must follow these rules:
1. If the current cell contains `0`, continue moving in the same direction.
2. If the current cell contains `1`, change your direction to the right (clockwise turn), and update the cell value to `0`.

You continue this process until you move outside the boundaries of the matrix. Your task is to determine the coordinates (row and column index) of the cell from which you exit the matrix.

---

## 💡 Examples

### Example 1:

```text
Input: mat[][] = [[0, 1, 0],
                  [0, 1, 1], 
                  [0, 0, 0]]
Output: [1, 0]
```

<details>
<summary>📖 Example Breakdown</summary>

1. Enter the matrix at `(0, 0)` moving **Right**.
2. Move towards `(0, 1)`. A `1` is encountered.
3. Change cell `(0, 1)` to `0`. Turn right (clockwise) to face **Down**.
4. Move towards `(1, 1)`. Another `1` is encountered.
5. Change cell `(1, 1)` to `0`. Turn right (clockwise) to face **Left**.
6. Move towards `(1, 0)`. A `0` is encountered. Keep facing **Left**.
7. Move towards `(1, -1)`. This crosses the boundary!
8. The last valid cell was `[1, 0]`. Exit point reached.
</details>

### Example 2:

```text
Input: mat[][] = [[0, 0]]
Output: [0, 1]
Explanation: 
- Enter the matrix at cell (0, 0) facing Right.
- Since the cell contains 0, we continue moving in the same direction.
- We reach cell (0, 1), which also contains a 0.
- We continue moving in the same direction and exit the matrix from cell [0, 1].
```

---

## ⚠️ Constraints

> - `1 <= n, m <= 100`
> - `mat[i][j]` is either `0` or `1`.
> - **Expected Time Complexity:** `O(n * m)`
> - **Expected Auxiliary Space:** `O(1)`

---

## 🚀 Solution Approaches

### Optimized Approach (Simulation)

**Brief Summary:**
This problem can be effectively solved by simulating the path exactly as described. We track our current position and direction. Whenever we hit a `1`, we change our direction 90 degrees clockwise and flip the `1` to `0`. By keeping track of our "previous" valid coordinates before making a move, we instantly know our exit point the moment our current coordinates fall out of the matrix bounds.

```cpp
// Intuition: We can directly simulate the movement through the matrix step by step. By maintaining a direction variable and updating it whenever we hit a 1, we just track our last valid coordinates before stepping out of bounds.
// Approach: Use a direction variable (0: Right, 1: Down, 2: Left, 3: Up). Loop while the current cell is within matrix boundaries. Store the current position as the exit point. If the current cell is 1, change it to 0 and turn 90 degrees right (dir = (dir + 1) % 4). Then, move to the next cell based on the current direction. When the loop terminates, return the stored exit point.
// Time Complexity: O(n * m) since each cell's 1 is converted to 0 upon visit, ensuring we don't get stuck in loops and visit cells a limited number of times.
// Space Complexity: O(1) because we only use a few integer variables for coordinates and direction without any extra auxiliary data structures.

class Solution {
  public:
    vector<int> exitPoint(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Direction Map: 0: Right, 1: Down, 2: Left, 3: Up
        int dir = 0; 
        
        // Current position trackers
        int row = 0, col = 0;
        
        // Variables to store the last valid coordinates before exiting
        int prevRow = 0, prevCol = 0;
        
        // Traverse until we go out of bounds
        while (row >= 0 && row < n && col >= 0 && col < m) {
            // Save current valid cell as the potential exit point
            prevRow = row;
            prevCol = col;
            
            // Handle direction change if cell contains a 1
            if (mat[row][col] == 1) {
                mat[row][col] = 0;   // Update cell to 0
                dir = (dir + 1) % 4; // Turn 90 degrees right (clockwise)
            }
            
            // Move forward one step in the current direction
            if (dir == 0) col++;         // Moving Right
            else if (dir == 1) row++;    // Moving Down
            else if (dir == 2) col--;    // Moving Left
            else row--;                  // Moving Up
        }
        
        // Return the last valid coordinates recorded
        return {prevRow, prevCol};
    }
};

/*
*
* Dry Run
*
* Input: mat = [[0, 1, 0], [0, 1, 1], [0, 0, 0]]
* Initial state: row = 0, col = 0, dir = 0 (Right)
*
* Step 1:
* Current cell (0,0) is 0. No direction change. Move Right.
* Next cell: row = 0, col = 1
*
* Step 2:
* Current cell (0,1) is 1. Change cell to 0. Turn Down (dir = 1). Move Down.
* Next cell: row = 1, col = 1
*
* Step 3:
* Current cell (1,1) is 1. Change cell to 0. Turn Left (dir = 2). Move Left.
* Next cell: row = 1, col = 0
*
* Step 4:
* Current cell (1,0) is 0. No direction change. Move Left.
* Next cell: row = 1, col = -1
*
* Step 5:
* Out of bounds detected (col < 0). Loop breaks.
* Last valid saved coordinates: prevRow = 1, prevCol = 0.
* Output: [1, 0]
*
*/
```

---

## 🧠 Key Insights

* **Modulus Arithmetic for Direction:** Representing directions as `0, 1, 2, 3` allows us to easily compute a 90-degree clockwise turn using `dir = (dir + 1) % 4`. This completely avoids complex, nested `if-else` blocks for direction changes.
* **In-place State Modification:** By flipping `1`s to `0`s as we visit them, we permanently remove obstacles from the grid. This naturally guarantees that we won't get stuck in an infinite loop; eventually, the grid will consist entirely of `0`s, forcing us to march straight to a boundary.
* **Trailing Pointers:** Using `prevRow` and `prevCol` to trail the main traversal variables (`row`, `col`) is an elegant way to capture the exit point without needing complex out-of-bounds boundary checks inside the movement logic.

---

## 🔗 Further Exploration

Want to practice more matrix simulation problems? Check these out:
* [Spiral Matrix](https://www.geeksforgeeks.org/problems/spirally-traversing-a-matrix-1587115621/1)
* [Rotate Matrix by 90 Degrees](https://www.geeksforgeeks.org/problems/rotate-by-90-degree-1587115621/1)
* [Boundary Traversal of matrix](https://www.geeksforgeeks.org/problems/boundary-traversal-of-matrix-1587115620/1)

---

## 📚 References

* **GFG Problem Link:** [Exit Point in a Matrix](https://www.geeksforgeeks.org/problems/exit-point-in-a-matrix0905/1)

---

## 👨‍💻 Author

**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Matrix` `#Simulation` `#Array` `#GeeksforGeeks` `#Samsung` `#C++`
