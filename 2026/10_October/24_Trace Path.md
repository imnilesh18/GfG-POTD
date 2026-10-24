# 🚶‍♂️ Trace Path

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) 
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge) 
![Accuracy](https://img.shields.io/badge/Accuracy-50.66%25-blue?style=for-the-badge) 
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge) 
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

<div align="center">

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

## 📝 Problem Statement

Given a rectangular grid with `n` rows and `m` columns, and a string `s` representing a sequence of movement commands.  Geek can start from any cell of the grid and follows all the commands in `s` in the same order. 

The string `s` consists only of the characters `L`, `R`, `D`, and `U`, where: 
*   **L:** Move one cell left, from `(i, j)` to `(i, j - 1)`. 
*   **R:** Move one cell right, from `(i, j)` to `(i, j + 1)`. 
*   **D:** Move one cell up, from `(i, j)` to `(i - 1, j)`. 
*   **U:** Move one cell down, from `(i, j)` to `(i + 1, j)`. 

Determine whether there exists at least one starting cell such that Geek remains within the grid while following all the commands in `s`. 

## 💡 Examples

```text
Input: n = 1, m = 1, s = "R" 
Output: false 
Explanation: There is only one cell (1, 1). So Geek can only start from (1, 1). On taking right(R) Geek moves to (1, 2), which is out of grid. Therefore, there is no cell from where Geek can start and remain inside the grid after tracing the route. 
```

```text
Input: n = 2, m = 3, s = "LLRU" 
Output: true 
Explanation: One possible cell is (1, 3). (1, 3) -> (1, 2) -> (1, 1) -> (1, 2) -> (2, 2). Thus, there is a cell from where if Geek starts, it remains inside the grid throughout tracing the route. 
```

<details>
<summary><b>📖 Example Breakdown (n = 2, m = 3, s = "LLRU")</b></summary>

Instead of guessing the start point, imagine starting at a generic origin `(0,0)`. 
1. `L`: move left to `(0, -1)`. Max horizontal span is now 1.
2. `L`: move left to `(0, -2)`. Max horizontal span is now 2.
3. `R`: move right to `(0, -1)`. 
4. `U`: move down to `(1, -1)`. Max vertical span is now 1.

The total horizontal span required is `2` (which is `< 3`), and the total vertical span required is `1` (which is `< 2`). Because the maximum required spans fit within the grid dimensions, the path is valid!
</details>

## ⚙️ Constraints

> - `1 ≤ n, m, s.size() ≤ 10^4` 
> - `s` consists only of the characters `L`, `R`, `D` and `U`. 

## 🧠 Solution Approach

### Optimized Boundary Tracking
**Brief Intuition:** Instead of checking every possible starting cell (which would be inefficient), we can simulate the path starting from an arbitrary `(0, 0)` origin. By keeping track of the minimum and maximum coordinates reached on both axes, we can calculate the total "span" or "bounding box" the path requires. If at any point this bounding box exceeds the grid's dimensions (`n` and `m`), it's impossible for the path to fit, regardless of the starting position.

```cpp
// Intuition: To check if a path fits inside an n x m grid, simulate the path from a generic origin (0,0). By tracking the maximum bounds reached in all 4 directions, we can determine the minimum required grid size for the path.
// Approach: 
// 1. Initialize coordinates (x, y) to (0, 0) and tracking variables for the minimum and maximum extremes reached on both axes.
// 2. Iterate through each character in the string 's' and update (x, y) accordingly (L: y--, R: y++, D: x--, U: x++).
// 3. Update the boundary extremes (min_x, max_x, min_y, max_y) after every move.
// 4. Calculate the current required grid span: (max_x - min_x) for rows and (max_y - min_y) for columns.
// 5. If the required span equals or exceeds the given grid dimensions (n or m) at any point, return 0 (false).
// 6. If the loop completes without exceeding the bounds, the path fits, so return 1 (true).
// Time Complexity: O(|s|) where |s| is the length of the string, because we process the movement string exactly once. 
// Space Complexity: O(1) as we are only using a constant number of integer variables to track bounds and coordinates. 

class Solution {
public:
    int isPossible(int n, int m, string s) {
        // Track the current relative coordinates
        int x = 0, y = 0;
        
        // Track the maximum and minimum displacements
        int min_x = 0, max_x = 0;
        int min_y = 0, max_y = 0;
        
        for (char c : s) {
            // Update relative coordinates based on direction
            if (c == 'L') {
                y--;
            } else if (c == 'R') {
                y++;
            } else if (c == 'D') {
                x--;
            } else if (c == 'U') {
                x++;
            }
            
            // Update the maximum boundaries reached so far
            min_x = min(min_x, x);
            max_x = max(max_x, x);
            min_y = min(min_y, y);
            max_y = max(max_y, y);
            
            // If the required span exceeds the grid dimensions at any point, path fails
            if (max_x - min_x >= n || max_y - min_y >= m) {
                return 0;
            }
        }
        
        // Path fits entirely within the bounds
        return 1;
    }
};

/*
*
* Dry Run
* Input: n = 2, m = 3, s = "LLRU"
* Initialization: x=0, y=0, min_x=0, max_x=0, min_y=0, max_y=0
* 
* Char 'L': y=-1. min_y=-1. Span Y (max_y - min_y) = 0 - (-1) = 1 (< 3). Span X = 0 (< 2).
* Char 'L': y=-2. min_y=-2. Span Y (max_y - min_y) = 0 - (-2) = 2 (< 3). Span X = 0 (< 2).
* Char 'R': y=-1. Bounds unchanged. Span Y = 2 (< 3). Span X = 0 (< 2).
* Char 'U': x=1. max_x=1. Span X (max_x - min_x) = 1 - 0 = 1 (< 2). Span Y = 2 (< 3).
* 
* Loop completes without spans reaching 'n' or 'm'.
* Output: 1 (True)
*
*/
```

## 🗝️ Key Insights

*   **Relative Tracking:** We don't need to actually find the exact starting coordinate. Because the grid is rigid and the path is sequential, tracking the overall maximum height and width of the path's bounding box is perfectly sufficient. 
*   **Early Exit:** By checking the span inside the loop `(max_x - min_x >= n || max_y - min_y >= m)`, we optimize the execution time—halting immediately the moment the path becomes too large, rather than waiting for the entire string to finish processing.

## 🚀 Further Exploration

*   Consider how you would modify this code if you *were* required to output all valid starting coordinates `(row, col)`. (Hint: The valid starting bounds for rows would be `[ -min_x, (n - 1) - max_x ]`).

## 🔗 References

*   **Problem Link:** [Trace Path on GeeksforGeeks](https://www.geeksforgeeks.org/problems/trace-path3840/1) 

## 🧑‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

## 🏷️ Tags

`Matrix`  `String` `Simulation` `GeeksforGeeks`