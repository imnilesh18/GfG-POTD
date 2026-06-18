# 🟢 Coverage of all Zeros in a Binary Matrix

<div align="center">
    
[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/coverage-of-all-zeros-in-a-binary-matrix4024/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-55.68%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a binary matrix `mat[][]` containing only `0`s and `1`s, find the total coverage of all `0`'s. 

The coverage of a particular `0` cell is defined by checking `1`'s in its four directions (left, right, up, and down). For each direction, if there is at least one `1` anywhere between the `0` and the boundary of the matrix, the coverage increases by one.

Return the sum of the coverage values for all `0` cells in the matrix.

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[1, 1, 1, 0],
                  [1, 0, 0, 1]]
Output: 8
Explanation: 
Coverage of first zero is 2. 
Coverages of other two zeros is 3. 
Total coverage = 2 + 3 + 3 = 8.

```

### Example 2

```text
Input: mat[][] = [[0, 1, 0],
                  [0, 1, 1],
                  [0, 0, 0]]
Output: 6
Explanation: Total Coverage is 1 + 2 + 1 + 0 + 1 + 1 = 6

```

### Example 3

```text
Input: mat[][] = [[0, 1]]
Output: 1
Explanation: There are only 1 coverage. Therefore answer for this test case is 1.

```

Given the matrix:

```
[1, 1, 1, 0]
[1, 0, 0, 1]

```

Let's analyze each `0` in the matrix:

1. **At (0, 3):** - Left: `1` is present (Coverage +1)
* Down: `1` is present at (1,3) (Coverage +1)
* Up/Right: Out of bounds
* *Total for this zero = 2*


2. **At (1, 1):**
* Up: `1` is present at (0,1) (Coverage +1)
* Left: `1` is present at (1,0) (Coverage +1)
* Right: `1` is present at (1,3) (Coverage +1)
* Down: Out of bounds
* *Total for this zero = 3*


3. **At (1, 2):**
* Up: `1` is present at (0,2) (Coverage +1)
* Left: `1` is present at (1,0) (Coverage +1)
* Right: `1` is present at (1,3) (Coverage +1)
* Down: Out of bounds
* *Total for this zero = 3*



**Total Matrix Coverage = 2 + 3 + 3 = 8**

---

## ⚠️ Constraints

> * `1 ≤ matrix.size(), matrix[0].size() ≤ 100`
> * Elements in `mat[][]` are either `0` or `1`.
> 
> 

---

## 🚀 Solution Approaches

### Directional Traversal (Optimized)

This approach elegantly simulates searching in all 4 cardinal directions without writing redundant, messy `if-else` blocks by utilizing direction arrays.

```cpp
// Intuition: To find the coverage of all 0s, we need to check if there is at least one '1' in all four directions for every '0' present in the matrix. Using direction arrays provides a clean way to simulate this outward search.
// Approach: Iterate through every cell in the matrix. When a '0' is encountered, use a 4-direction array (dr, dc) to scan up, down, left, and right. In each direction, use a while loop to keep moving until we either hit a '1' (increment coverage and break) or reach the matrix boundary.
// Time Complexity: O(n * m * (n + m)) - In the worst case, for each 0, we might scan its entire row and column. Given the constraints (n, m <= 100), this easily executes well within time limits.
// Space Complexity: O(1) - We only use a few variables for tracking coverage and directions, requiring no extra auxiliary space.

class Solution {
  public:
    int findCoverage(vector<vector<int>>& mat) {
        // Step 1: Initialize dimensions and total coverage counter
        int n = mat.size();
        int m = mat[0].size();
        int totalCoverage = 0;
        
        // Directions array for Up, Down, Left, Right respectively
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Step 2: Iterate over every cell in the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                // Process only when current cell is 0
                if (mat[i][j] == 0) {
                    
                    // Check all 4 directions radially
                    for (int k = 0; k < 4; k++) {
                        int r = i + dr[k];
                        int c = j + dc[k];
                        
                        // Traverse in the current direction until boundary is hit
                        while (r >= 0 && r < n && c >= 0 && c < m) {
                            
                            // If a 1 is found, increment coverage and stop searching this direction
                            if (mat[r][c] == 1) {
                                totalCoverage++;
                                break; 
                            }
                            
                            // Move to the next cell in the same direction
                            r += dr[k];
                            c += dc[k];
                        }
                    }
                }
            }
        }
        
        return totalCoverage;
    }
};

/*
*
* Dry Run
*
* Input: mat = [[0, 1]]
* n = 1, m = 2
* totalCoverage = 0
* dr = {-1, 1, 0, 0}, dc = {0, 0, -1, 1} representing Up, Down, Left, Right
*
* i = 0, j = 0
* mat[0][0] is 0
* - Check up (k=0): r=-1, out of bounds, loop does not execute
* - Check down (k=1): r=1, out of bounds, loop does not execute
* - Check left (k=2): c=-1, out of bounds, loop does not execute
* - Check right (k=3): r=0, c=1, mat[0][1] is 1, totalCoverage becomes 1, loop breaks
* * i = 0, j = 1
* mat[0][1] is 1, skip processing
*
* Final totalCoverage returned is 1
*
*/

```

---

## 🧠 Key Insights

* **Directional Arrays:** Storing directions in `dr` and `dc` arrays (`{-1,1,0,0}` and `{0,0,-1,1}`) is a standard and robust trick to simplify 2D matrix traversal codes and avoid excessive conditional branches.
* **Short-Circuiting:** The `break` statement inside the `while` loop ensures that once the closest `1` in a given direction is found, the loop stops, effectively optimizing runtime and satisfying the coverage rules.

---

## 🔗 Further Exploration

If you enjoyed this problem, here are some related concepts and questions to explore:

* **Matrix Traversal Problems:** Problems involving BFS/DFS on grids.
* **Related GFG Problem:** *Find the number of islands*, *Rotting Oranges*.
* Practice using direction arrays for graph/grid problems—they serve as fundamental building blocks for harder pathfinding tasks.

---

## 📚 References

* **Original Problem:** [GeeksforGeeks - Coverage of all Zeros in a Binary Matrix](https://www.geeksforgeeks.org/problems/coverage-of-all-zeros-in-a-binary-matrix4024/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Matrix` `#DataStructures` `#Algorithms` `#GeeksForGeeks` `#Cpp`