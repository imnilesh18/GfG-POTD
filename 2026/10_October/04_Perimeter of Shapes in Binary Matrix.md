# 🟩 Perimeter of Shapes in Binary Matrix

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-perimeter-of-shapes/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-43a047?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-72.98%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a binary matrix `mat[][]` of size `n × m`, where each cell contains either `0` or `1`, find the total perimeter of all figures formed by cells containing `1`s.[cite: 1] Two cells are considered adjacent if they share a common side.[cite: 1]

A single cell containing `1` has a perimeter of 4, whereas two adjacent cells containing `1` (i.e., `11`) together have a perimeter of 6.[cite: 1]

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[0,1,0,0,0], [1,1,1,0,0], [1,0,0,0,0]]
Output: 12
Explanation: The five cells form a single figure. Hence, the perimeter of the figure is 12.
```
*Source:[cite: 1]*

### Example 2
```text
Input: mat[][] = [[1,0], [1,1]]
Output: 8
Explanation: The two adjacent cells share one common side. Hence, the perimeter of the figure is 6.
```
*Source:[cite: 1]*

<details>
<summary>📖 <b>Example Breakdown (Example 2)</b></summary>

- We start scanning the `2x2` matrix.
- **Cell (0,0)** is `1`. It touches the boundary on the Top and Left (2 edges), touches a `0` on the Right (1 edge), and touches a `1` on the Bottom (0 edges). Perimeter increases by **3**.
- **Cell (0,1)** is `0`. We skip it.
- **Cell (1,0)** is `1`. It touches the boundary on the Bottom and Left (2 edges), a `1` on Top (0 edges), and a `1` on the Right (0 edges). Perimeter increases by **2** (Total = 5).
- **Cell (1,1)** is `1`. It touches a `0` on Top (1 edge), boundary on Bottom and Right (2 edges), and a `1` on the Left (0 edges). Perimeter increases by **3** (Total = 8).
- Final perimeter is **8**.

</details>

---

## ⚙️ Constraints

> - `1 ≤ n, m ≤ 1000`[cite: 1]
> - **Expected Time Complexity:** `O(n * m)`[cite: 1]
> - **Expected Auxiliary Space:** `O(1)`[cite: 1]

---

## 🚀 Solution Approaches

### 1. Matrix Traversal & Neighbor Checking (Optimized)

**Intuition:** 
Every `1` in the matrix naturally contributes exactly 4 to the perimeter. However, if a `1` is directly adjacent to another `1`, the shared edge is hidden and does not count towards the outer perimeter. Instead of mathematically subtracting shared edges, we can directly count the exposed edges: an edge is exposed *only* if the neighboring cell in that direction is out of bounds or contains a `0`.

```cpp
// Intuition: An edge of a '1' cell contributes to the perimeter only if it touches a boundary or a '0'.
// Approach: Iterate through each matrix cell. When a '1' is found, check its 4 adjacent neighbors (Top, Bottom, Left, Right). Increment the perimeter for each neighbor that is a '0' or out of bounds.
// Time Complexity: O(n * m) because we visit every cell in the n x m matrix exactly once.
// Space Complexity: O(1) as we only use a few primitive variables for iteration and tracking the perimeter.

class Solution {
  public:
    int findPerimeter(vector<vector<int>> &mat) {
        int n = mat.size();
        if (n == 0) return 0; // Handle empty matrix edge case
        int m = mat[0].size();

        int perimeter = 0;

        // Traverse row by row
        for (int i = 0; i < n; i++) {
            // Traverse column by column
            for (int j = 0; j < m; j++) {
                
                // Only process cells that are part of the figure
                if (mat[i][j] == 1) {
                    
                    // Check Top: increment if boundary or '0'
                    if (i == 0 || mat[i - 1][j] == 0) perimeter++;

                    // Check Bottom: increment if boundary or '0'
                    if (i == n - 1 || mat[i + 1][j] == 0) perimeter++;

                    // Check Left: increment if boundary or '0'
                    if (j == 0 || mat[i][j - 1] == 0) perimeter++;

                    // Check Right: increment if boundary or '0'
                    if (j == m - 1 || mat[i][j + 1] == 0) perimeter++;
                }
            }
        }

        return perimeter;
    }
};

/*
*
* Dry Run
*
* Input: mat = [[1,0], [1,1]]
* 
* i = 0, j = 0 (1): Top is bounds (+1), Bottom is 1 (+0), Left is bounds (+1), Right is 0 (+1). Perimeter = 3.
* i = 0, j = 1 (0): Ignored.
* i = 1, j = 0 (1): Top is 1 (+0), Bottom is bounds (+1), Left is bounds (+1), Right is 1 (+0). Perimeter = 5.
* i = 1, j = 1 (1): Top is 0 (+1), Bottom is bounds (+1), Left is 1 (+0), Right is bounds (+1). Perimeter = 8.
* 
* Output: 8
*
*/
```

---

## 🧠 Key Insights
- **Boundary Handling:** Using `||` (logical OR) leverages short-circuit evaluation. By placing `i == 0` before checking `mat[i - 1][j]`, we guarantee no out-of-bounds `IndexOutOfBounds` exceptions occur.
- **Independence of Order:** Because we verify the perimeter segment cell-by-cell without modifying the matrix, the traversal order (row-major vs column-major) does not affect the correctness of the algorithm.

---

## 🔍 Further Exploration
- **Island Perimeter (LeetCode):** A highly similar algorithmic challenge often asked in graph/matrix technique interviews.
- **Number of Islands:** Explores similar neighbor-checking mechanics but utilizes DFS/BFS to count disconnected components.

---

## 🔗 References
- **GeeksforGeeks Problem:** [Perimeter of Shapes in Binary Matrix](https://www.geeksforgeeks.org/problems/find-perimeter-of-shapes/1)[cite: 1]

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#matrix` `#geometric` `#cpp` `#geeksforgeeks` `#array`