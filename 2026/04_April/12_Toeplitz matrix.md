# 🟩 Toeplitz Matrix

<div align="center">
  
[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/toeplitz-matrix/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-49.05%25-orange?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](LICENSE)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

A **Toeplitz matrix** (also known as a diagonal-constant matrix) is a matrix in which every descending diagonal from left to right contains the same element.

Given a rectangular matrix `mat`, determine whether it is a Toeplitz matrix or not.

Implement the function `isToeplitz(mat)` that returns:
- `true` if the matrix is a Toeplitz matrix
- `false` otherwise

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[6, 7, 8],
                  [4, 6, 7],
                  [1, 4, 6]]
Output: true
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

The matrix is Toeplitz because every diagonal from top-left to bottom-right has the same elements. 
- The main diagonal is `6 → 6 → 6`.
- The diagonal above it is `7 → 7`.
- The diagonal below it is `4 → 4`.
- Other corner elements like `8` and `1` stand alone.

Since all diagonals follow this pattern, the matrix is Toeplitz, so the output is `true`.
</details>

### Example 2
```text
Input: mat[][] = [[6, 3, 8],
                  [4, 9, 7],
                  [1, 4, 6]]
Output: false
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

The primary diagonal elements of the given matrix are `[6, 9, 6]`. As the diagonal elements are not the same, the given matrix is not a Toeplitz Matrix.
</details>

---

## 🔒 Constraints

- `1 ≤ mat.size(), mat[0].size() ≤ 40`
- `0 ≤ mat[i][j] ≤ 100`

---

## 🚀 Solution Approach

### 🔹 Optimal Approach (Single Pass Iteration)

The most efficient way to solve this is to realize that if every element is equal to its top-left neighbor, then every diagonal will consist of the exact same elements. We can start our loops from the second row (`i=1`) and second column (`j=1`) and compare each `mat[i][j]` to `mat[i-1][j-1]`.

```cpp
// Intuition: A Toeplitz matrix requires every descending diagonal from left to right to have the same elements. This implies that any element at index (i, j) must be equal to the element at (i-1, j-1). We can verify the matrix by simply checking this condition for all valid (i, j).
// Approach: Traverse the matrix starting from the second row (i = 1) and the second column (j = 1). Compare the current element mat[i][j] with its top-left neighbor mat[i-1][j-1]. If a mismatch is found, return false immediately. If the entire matrix is traversed without mismatches, return true.
// Time Complexity: O(n * m), where n is the number of rows and m is the number of columns. We visit each element of the matrix exactly once.
// Space Complexity: O(1), as we only use constant extra space for variables and do not require any additional data structures.

class Solution {
  public:
    // Function to check whether given
    // matrix is a toeplitz matrix or not
    bool isToeplitz(vector<vector<int>> &mat) {
        int n = mat.size(), m = mat[0].size();
    
        // Iterate from the second row and second column
        // to check the diagonally above element of each cell
        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {
                // If current element doesn't match its top-left neighbor, it's not a Toeplitz matrix
                if(mat[i][j] != mat[i - 1][j - 1])
                    return false;
            }
        }
        
        // All diagonal elements matched successfully
        return true;
    }
};

/*
*
* Dry Run
*
* Input:
* mat = [[6, 7, 8],
* [4, 6, 7],
* [1, 4, 6]]
* n = 3, m = 3
*
* Iteration starts at i = 1:
* j = 1: mat[1][1] (6) == mat[0][0] (6) -> True, continue
* j = 2: mat[1][2] (7) == mat[0][1] (7) -> True, continue
* * Iteration moves to i = 2:
* j = 1: mat[2][1] (4) == mat[1][0] (4) -> True, continue
* j = 2: mat[2][2] (6) == mat[1][1] (6) -> True, continue
*
* Both loops end without returning false.
* Return true.
* * Output: true
*
*/
```

---

## 🧠 Key Insights

- **Avoid Redundant Work:** Instead of trying to extract full diagonals and checking their bounds, shifting our perspective to compare adjacent elements relative to the diagonal path (`mat[i][j]` vs `mat[i-1][j-1]`) drastically simplifies the code logic.
- **In-place Verification:** We don't need any auxiliary space or extra arrays to keep track of diagonal elements, achieving an $O(1)$ space complexity.

---

## 🔍 Further Exploration

- [Matrix Diagonal Sum](https://leetcode.com/problems/matrix-diagonal-sum/)
- [Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/)
- [Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

---

## 🔗 References

- **Original GeeksforGeeks Problem:** [Toeplitz Matrix](https://www.geeksforgeeks.org/problems/toeplitz-matrix/1)

---

## 👨‍💻 Author

<a href="https://github.com/imnilesh18">
  <img src="https://img.shields.io/badge/GitHub-imnilesh18-181717?style=for-the-badge&logo=github&logoColor=white" alt="imnilesh18 GitHub" />
</a>

---

## 🏷️ Tags

`#Matrix` `#DataStructures` `#Array` `#GeeksForGeeks` `#Algorithms`