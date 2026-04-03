# 🟩 Print Diagonally

<div align="center">
  
![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-66.11%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

<br>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an `n * n` square matrix `mat[][]`, return all the elements of its anti-diagonals from **top to bottom**.

---

## 💡 Examples

### Example 1

```text
Input: 
n = 2
mat[][] = [[1, 2],
           [3, 4]]
Output: 
[1, 2, 3, 4]
```

### Example 2

```text
Input: 
n = 3
mat[][] = [[1, 2, 3],
           [4, 5, 6],
           [7, 8, 9]]
Output: 
[1, 2, 4, 3, 5, 7, 6, 8, 9]
```

<details>
<summary>📖 Example Breakdown (n = 3)</summary>

For an `n = 3` matrix, the sum of row and column indices (`i + j`) ranges from `0` to `4` (since `2*n - 2 = 4`).

- **Sum 0:** Starts at `(0, 0)` ➔ **1**
- **Sum 1:** Starts at `(0, 1)` ➔ `(1, 0)` ➔ **2, 4**
- **Sum 2:** Starts at `(0, 2)` ➔ `(1, 1)` ➔ `(2, 0)` ➔ **3, 5, 7**
- **Sum 3:** Starts at `(1, 2)` ➔ `(2, 1)` ➔ **6, 8**
- **Sum 4:** Starts at `(2, 2)` ➔ **9**

**Result:** `[1, 2, 4, 3, 5, 7, 6, 8, 9]`
</details>

---

## ⚠️ Constraints

- `1 ≤ n ≤ 10^3`
- `0 ≤ mat[i][j] ≤ 10^6`

---

## 💻 Solution Approaches

### Optimized Approach (Mathematical Diagonal Traversal)

```cpp
// Intuition: Elements on the same anti-diagonal share a constant sum of their row and column indices (i + j). By iterating through all possible sum values from 0 to 2*n - 2, we can uniquely identify and extract each diagonal.
// Approach: Iterate 's' from 0 to 2*n - 2. For each 's', determine the starting row 'r' and column 'c'. If s < n, start at (0, s). If s >= n, start at (s - n + 1, n - 1). Traverse the diagonal by incrementing 'r' and decrementing 'c' until boundaries are hit.
// Time Complexity: O(N^2) where N is the size of the matrix, as we visit every element in the matrix exactly once.
// Space Complexity: O(1) auxiliary space, ignoring the space required for the output array.

class Solution {
  public:
    vector<int> diagView(vector<vector<int>> mat) {
        int n = mat.size();
        vector<int> ans;
        
        // Loop through all possible sum of indices (0 to 2n - 2)
        for (int s = 0; s < 2 * n - 1; s++) {
            
            // Calculate starting row and column for the current diagonal
            int r = (s < n) ? 0 : s - n + 1;
            int c = (s < n) ? s : n - 1;
            
            // Traverse downwards-left while within matrix boundaries
            while (r < n && c >= 0) {
                ans.push_back(mat[r][c]);
                r++; // Move down
                c--; // Move left
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
* Input: n = 2, mat = [[1, 2], [3, 4]]
* Matrix size n = 2, Max sum = 2*2 - 2 = 2
* s = 0: r = 0, c = 0 -> ans = [1]
* s = 1: r = 0, c = 1 -> ans = [1, 2], r=1, c=0 -> ans = [1, 2, 3]
* s = 2: r = 1, c = 1 -> ans = [1, 2, 3, 4]
* Output: [1, 2, 3, 4]
*
*/
```

---

## 🔑 Key Insights

- **Index Sum Property:** The fundamental trick is recognizing that for any anti-diagonal going from top-right to bottom-left, the sum of row and column coordinates `(i + j)` remains constant.
- **Boundary Handling:** Carefully calculating the starting point prevents index out-of-bounds errors. The shift in starting logic at `s == n` seamlessly transitions traversal from the top edge to the right edge.

---

## 🔍 Further Exploration

- **Print Matrix in Snake Pattern:** A variation where traversal alters direction periodically.
- **Spiral Traversal of a Matrix:** A classic matrix traversal problem that tests boundary manipulation.
- **Diagonal Traverse (LeetCode 498):** Similar problem but alternates the diagonal direction (up-right then down-left).

---

## 🔗 References

- **GeeksforGeeks Problem:** [Print Diagonally](https://practice.geeksforgeeks.org/problems/print-diagonally/1)
- **Company Tags:** Amazon

---

## 👨‍💻 Author

**Nilesh** [![GitHub](https://img.shields.io/badge/GitHub-Profile-181717?style=for-the-badge&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Arrays` `#Matrix` `#GeeksForGeeks` `#DataStructures` `#Amazon`