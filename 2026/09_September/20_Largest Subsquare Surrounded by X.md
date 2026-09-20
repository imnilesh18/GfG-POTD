# 🔲 Largest Subsquare Surrounded by X

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.31%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

<div align="center">

```text
  Matrix Grid Visualisation (Submatrix 3x3)
  -----------------------------------------
     (0,0) [X]  [X]  [X]  [O]
     (1,0) [X]  [O]  [X]  [X]
     (2,0) [X]  [X]  [X]  [O]
     (3,0) [X]  [O]  [X]  [X]

  Top-Left (0,0) to Bottom-Right (2,2) forms a 3x3 square
  where all 4 outer boundaries consist strictly of 'X'!
```

</div>

---

## 📝 Problem Statement

Given a square matrix `mat[][]` of size $n \times n$, where each cell contains either `'X'` or `'O'`, find the size of the **largest square submatrix** whose boundary is completely surrounded by `'X'`. 

The cells inside the submatrix can contain either `'X'` or `'O'`. Only the four outer sides of the submatrix must contain `'X'`.

Return the **side length** of the largest such square submatrix.

> **Note:** A square of size `1` is valid if its only cell is `'X'`. If no such square submatrix exists, return `0`.

---

## 📋 Examples

### Example 1
```text
Input: mat[][] = [
  ['X', 'X', 'X', 'O'],
  ['X', 'O', 'X', 'X'],
  ['X', 'X', 'X', 'O'],
  ['X', 'O', 'X', 'X']
]
Output: 3
Explanation: The square submatrix starting at (0,0) and ending at (2,2) is the largest submatrix surrounded by 'X'. Therefore, the side length is 3.
```

### Example 2
```text
Input: mat[][] = [
  ['X', 'X'],
  ['X', 'X']
]
Output: 2
Explanation: The largest square submatrix surrounded by 'X' is the whole input matrix, giving a side length of 2.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

<br>

Consider Example 1 with matrix size $4 \times 4$:

1. **Cell (2, 2)** ends a potential submatrix spanning from `(0, 0)` to `(2, 2)`.
2. **Top Boundary:** Cells `(0,0)`, `(0,1)`, `(0,2)` are all `'X'`.
3. **Bottom Boundary:** Cells `(2,0)`, `(2,1)`, `(2,2)` are all `'X'`.
4. **Left Boundary:** Cells `(0,0)`, `(1,0)`, `(2,0)` are all `'X'`.
5. **Right Boundary:** Cells `(0,2)`, `(1,2)`, `(2,2)` are all `'X'`.
6. Inner cell `(1,1)` contains `'O'`, but boundary condition is completely satisfied!
7. The maximum length of this valid boundary square is **3**.

</details>

---

## 🔒 Constraints

> - $1 \le n, \text{mat.size()}, \text{mat}[i].size() \le 1000$
> - $\text{mat}[i][j] \in \{'X', 'O'\}$
> - **Expected Time Complexity:** $\mathcal{O}(n^3)$
> - **Expected Auxiliary Space:** $\mathcal{O}(n^2)$

---

## 💡 Solution Approach

### Precomputation & Dynamic Boundary Verification

Checking every possible square submatrix naively takes $\mathcal{O}(n^4)$ time because validating four boundaries of length $L$ takes $\mathcal{O}(L)$ time per check.

To optimize this to $\mathcal{O}(n^3)$:
1. **Precompute Boundary Strengths:** Maintain two 2D matrices, `hor[i][j]` and `ver[i][j]`.
   - `hor[i][j]`: Stores the count of contiguous `'X'` cells ending at `(i, j)` horizontally to the left.
   - `ver[i][j]`: Stores the count of contiguous `'X'` cells ending at `(i, j)` vertically above.
2. **Evaluate Bottom-Right Corner:** Treat every cell `(i, j)` as the bottom-right corner of a potential square.
3. **Determine Max Feasible Side:** The maximum possible side length `len` at `(i, j)` is constrained by `min(hor[i][j], ver[i][j])`.
4. **Fast Boundary Validation ($\mathcal{O}(1)$):** A square of side length `len` ending at `(i, j)` is valid if:
   - Top edge has at least `len` contiguous `'X'`s: `hor[i - len + 1][j] >= len`
   - Left edge has at least `len` contiguous `'X'`s: `ver[i][j - len + 1] >= len`

```cpp
// Intuition: To find the largest square surrounded by 'X', we can precompute the contiguous 'X's in horizontal and vertical directions for each cell. This allows us to quickly verify if the edges of a potential square are valid in O(1) time per edge check.
// Approach: Build two 2D DP matrices `hor` and `ver`. Iterate through all cells treating each as a bottom-right corner, finding the maximum valid square size by validating top and left edges.
// Time Complexity: O(n^3) - We traverse the matrix O(n^2), and for each cell, we may check up to `n` possible square sizes.
// Space Complexity: O(n^2) - We use two auxiliary matrices of size n x n to store the contiguous counts.

class Solution {
  public:
    int largestSubsquare(vector<vector<char>> &mat) {
        // Precompute horizontal and vertical contiguous 'X' counts
        int n = mat.size();
        if (n == 0) return 0;
        
        vector<vector<int>> hor(n, vector<int>(n, 0));
        vector<vector<int>> ver(n, vector<int>(n, 0));
        
        // Fill hor and ver arrays
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 'X') {
                    hor[i][j] = (j == 0) ? 1 : hor[i][j - 1] + 1;
                    ver[i][j] = (i == 0) ? 1 : ver[i - 1][j] + 1;
                }
            }
        }
        
        int max_size = 0;
        
        // Check every cell as bottom-right corner
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                // Potential max size at (i, j)
                int len = min(hor[i][j], ver[i][j]);
                
                // Find largest valid square ending at (i, j)
                while (len > max_size) {
                    // Check top and left edges of the potential square
                    if (hor[i - len + 1][j] >= len && ver[i][j - len + 1] >= len) {
                        max_size = len;
                        break;
                    }
                    len--;
                }
            }
        }
        
        return max_size;
    }
};

/*
*
* Dry Run
*
* Input:
* mat = 
* X X X O
* X O X X
* X X X O
* X O X X
*
* Precomputation (hor):
* 1 2 3 0
* 1 0 1 2
* 1 2 3 0
* 1 0 1 2
*
* Precomputation (ver):
* 1 1 1 0
* 2 0 2 1
* 3 1 3 0
* 4 0 4 1
*
* Start checking from bottom-right (3,3):
*
* Cell (3,3): 
* min(hor[3][3], ver[3][3]) = min(2, 1) = 1
* len = 1
* Top/Left edges valid? Yes.
* max_size = 1
*
* Cell (3,2): 
* min(hor[3][2], ver[3][2]) = min(1, 4) = 1 (not > max_size, skip inner loop)
*
* Skip ahead to Cell (2,2): 
* min(hor[2][2], ver[2][2]) = min(3, 3) = 3
* len = 3
* Check top edge: hor[2 - 3 + 1][2] = hor[0][2] = 3 >= 3 (Valid)
* Check left edge: ver[2][2 - 3 + 1] = ver[2][0] = 3 >= 3 (Valid)
* Both edges are valid.
* max_size becomes 3.
*
* Remaining cells cannot produce a square > 3 since max_size is already 3 and remaining indices won't allow len > 3.
* Return max_size = 3.
*
*/
```

---

## 🔑 Key Insights

- **2D Continuous Prefix Counting:** Precomputing continuous lengths converts an $\mathcal{O}(L)$ edge boundary check into an $\mathcal{O}(1)$ dynamic lookup.
- **Corner Anchor Strategy:** Using each cell as a **bottom-right corner** implicitly anchors the bottom and right edges using `hor[i][j]` and `ver[i][j]`, leaving only top (`hor[i-len+1][j]`) and left (`ver[i][j-len+1]`) edges to verify.
- **Loop Pruning:** Skipping the inner loop whenever `len <= max_size` significantly reduces real-world operations.

---

## 🔎 Further Exploration

- [Maximum Size Square Sub-Matrix with All 1s](https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/)
- [Maximal Rectangle in Binary Matrix](https://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/)
- [Number of Submatrices with All Ones](https://www.geeksforgeeks.org/count-number-of-submatrices-with-all-1s/)

---

## 🔗 References

- **GeeksforGeeks Problem Page:** [Largest Subsquare Surrounded by X](https://www.geeksforgeeks.org/problems/largest-subsquare-surrounded-by-x0558/1)

---

## 👤 Author

Crafted with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

- `matrix`
- `dynamic-programming`
- `precomputation`
- `cpp`
- `geeksforgeeks`