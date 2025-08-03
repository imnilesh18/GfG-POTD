# 💻 2D Difference Array

<div align="center">

⚠️ **Educational Use Only**:  
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/2-d-difference-array/1).

</div>

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-62.66%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge)

</div>

---

## 📝 Problem Statement

Given a 2D integer matrix `mat[][]` of size $n \times m$ and a list of $q$ operations `opr[][]`, each operation is represented as an array `[v, r1, c1, r2, c2]`:

- `v` is the value to be added
- `(r1, c1)` is the top-left cell of a submatrix
- `(r2, c2)` is the bottom-right cell of the submatrix (inclusive)

For each of the $q$ operations, add `v` to every element in the submatrix from `(r1, c1)` to `(r2, c2)`. Return the **final matrix** after applying all operations.

---

## 🧪 Examples

### Example 1

```
Input:
mat[][] = [[1, 2, 3],
           [1, 1, 0],
           [4, -2, 2]]
opr[][] = [[2, 0, 0, 1, 1],
           [-1, 1, 0, 2, 2]]

Output:
[[3, 4, 3],
 [2, 2, -1],
 [3, -3, 1]]
```

<div>
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/899248/Web/Other/blobid1_1753512754.jpg" alt="2D Difference Array Illustration" width="400px">
</div>

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

**Initial Matrix**:

```
[[1, 2, 3],
 [1, 1, 0],
 [4, -2, 2]]
```

**First Operation**: `[2, 0, 0, 1, 1]`  
Add `2` to submatrix from `(0,0)` to `(1,1)`.

Matrix becomes:

```
[[3, 4, 3],
 [3, 3, 0],
 [4, -2, 2]]
```

**Second Operation**: `[-1, 1, 0, 2, 2]`  
Add `-1` to submatrix from `(1,0)` to `(2,2)`.

Matrix becomes:

```
[[3, 4, 3],
 [2, 2, -1],
 [3, -3, 1]]
```

</details>

---

## ⛓️ Constraints

> `1 ≤ n×m, q ≤ 10^5`  
> `0 ≤ r1 ≤ r2 ≤ n - 1`  
> `0 ≤ c1 ≤ c2 ≤ m - 1`  
> `-10^4 ≤ mat[i][j], v ≤ 10^4`

---

## 💡 Solution Approach

When multiple rectangular updates are required on a 2D grid, the direct approach (iterating over every cell for every update) is too slow. The **2D Difference Array** technique allows each range update to be performed in constant time, and the final matrix to be constructed in $O(n \times m)$ using prefix sums.

**How It Works:**

- For each operation, update only the four corners of a helper `diff` matrix.
- After all operations, compute row-wise and then column-wise prefix sums on `diff`.
- Add the resulting `diff` to the original matrix to get the final answer.

---

## 🚀 C++ Solution

```cpp
// Intuition: Efficiently handle multiple range updates on a 2D grid by marking only the corners of the update area using a difference array, which can then be resolved with prefix sums.
// Approach:
// 1. Create a difference matrix 'diff' of the same size as 'mat' and initialize it to zero.
// 2. For each operation, update four corners in 'diff' to mark the update region.
//    - Add at (r1,c1), subtract at (r1,c2+1) and (r2+1,c1), add at (r2+1,c2+1) if within bounds.
// 3. Compute row-wise prefix sums, then column-wise prefix sums on 'diff' to propagate the updates to all covered cells.
// 4. Add the final 'diff' matrix to the original 'mat' to get the updated matrix.
// Time Complexity: O(q + n*m) - Each operation is O(1), prefix sums and application are O(n*m).
// Space Complexity: O(n*m) - Additional matrix used for the difference array.

class Solution {
  public:
    vector<vector<int>> applyDiff2D(vector<vector<int>>& mat, vector<vector<int>>& opr) {
        int n = mat.size();
        int m = mat[0].size();

        // Initialize difference matrix with zeros
        vector<vector<int>> diff(n, vector<int>(m, 0));

        // Apply each operation using 4-point updates
        for (auto& q : opr) {
            int v = q[0];
            int r1 = q[1], c1 = q[2], r2 = q[3], c2 = q[4];

            // Top-left corner: start of addition
            diff[r1][c1] += v;

            // Top-right corner: end of addition for row
            if (c2 + 1 < m) diff[r1][c2 + 1] -= v;

            // Bottom-left corner: end of addition for column
            if (r2 + 1 < n) diff[r2 + 1][c1] -= v;

            // Bottom-right: restore overlap
            if (r2 + 1 < n && c2 + 1 < m) diff[r2 + 1][c2 + 1] += v;
        }

        // Row-wise prefix sum to propagate row changes
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                diff[i][j] += diff[i][j - 1];
            }
        }

        // Column-wise prefix sum to propagate column changes
        for (int j = 0; j < m; j++) {
            for (int i = 1; i < n; i++) {
                diff[i][j] += diff[i - 1][j];
            }
        }

        // Add diff matrix to the original matrix for final result
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mat[i][j] += diff[i][j];
            }
        }

        return mat;
    }
};

/*
*
* Dry Run
*
* Input:
* mat = [[1, 2, 3],
*        [1, 1, 0],
*        [4, -2, 2]]
* opr = [[2, 0, 0, 1, 1],
*        [-1, 1, 0, 2, 2]]
*
* Initial diff = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
*
* After Op1 [2,0,0,1,1]:
* diff[0][0] += 2  => [[2, 0, 0], [0, 0, 0], [0, 0, 0]]
* diff[0][2] -= 2  => [[2, 0, -2], [0, 0, 0], [0, 0, 0]]
* diff[2][0] -= 2  => [[2, 0, -2], [0, 0, 0], [-2, 0, 0]]
* diff[2][2] += 2  => [[2, 0, -2], [0, 0, 0], [-2, 0, 2]]
*
* After Op2 [-1,1,0,2,2]:
* diff[1][0] -= 1  => [[2, 0, -2], [-1, 0, 0], [-2, 0, 2]]
* (others out of bounds)
*
* Row-wise prefix sum:
* [[2, 2, 0], [-1, -1, -1], [-2, -2, 0]]
*
* Column-wise prefix sum:
* [[2, 2, 0], [1, 1, -1], [-1, -1, -1]]
*
* Final add to mat:
* [[1+2, 2+2, 3+0], [1+1, 1+1, 0-1], [4-1, -2-1, 2-1]]
* [[3, 4, 3], [2, 2, -1], [3, -3, 1]]
*
*/
```

---

## 🚀 Java Solution

```java
// Intuition: Efficiently perform multiple submatrix updates by marking just the corners in a difference array, then resolve all updates at once using prefix sums.
// Approach:
// 1. Create a difference matrix 'diff' the same size as 'mat' initialized to zero.
// 2. For each operation, adjust four corners in 'diff' to mark the region to update.
//    - Add at (r1,c1), subtract at (r1,c2+1) and (r2+1,c1), add at (r2+1,c2+1) if within bounds.
// 3. Perform row-wise prefix sums and then column-wise prefix sums on 'diff' so every cell accumulates all relevant updates.
// 4. Add the resulting 'diff' values back to 'mat' to produce the final matrix.
// Time Complexity: O(q + n*m) - Each operation is O(1), prefix sums and result are O(n*m).
// Space Complexity: O(n*m) - Uses an auxiliary matrix for the difference array.

class Solution {
    public ArrayList<ArrayList<Integer>> applyDiff2D(int[][] mat, int[][] opr) {
        int n = mat.length, m = mat[0].length;
        int[][] diff = new int[n][m];

        // Apply each operation with 4-corner updates
        for (int[] q : opr) {
            int v = q[0], r1 = q[1], c1 = q[2], r2 = q[3], c2 = q[4];
            // Top-left: start of addition
            diff[r1][c1] += v;
            // Top-right: end of addition for row
            if (c2 + 1 < m) diff[r1][c2 + 1] -= v;
            // Bottom-left: end of addition for column
            if (r2 + 1 < n) diff[r2 + 1][c1] -= v;
            // Bottom-right: restore overlap
            if (r2 + 1 < n && c2 + 1 < m) diff[r2 + 1][c2 + 1] += v;
        }

        // Row-wise prefix sum
        for (int i = 0; i < n; i++)
            for (int j = 1; j < m; j++)
                diff[i][j] += diff[i][j - 1];

        // Column-wise prefix sum
        for (int j = 0; j < m; j++)
            for (int i = 1; i < n; i++)
                diff[i][j] += diff[i - 1][j];

        // Build result by adding diff to mat and converting to ArrayList
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            ArrayList<Integer> row = new ArrayList<>();
            for (int j = 0; j < m; j++) {
                mat[i][j] += diff[i][j];
                row.add(mat[i][j]);
            }
            result.add(row);
        }

        return result;
    }
}

/*
*
* Dry Run
*
* Input:
* mat = [[1, 2, 3],
*        [1, 1, 0],
*        [4, -2, 2]]
* opr = [[2, 0, 0, 1, 1],
*        [-1, 1, 0, 2, 2]]
*
* Initial diff = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
*
* After Op1 [2,0,0,1,1]:
* diff[0][0] += 2  => [[2, 0, 0], [0, 0, 0], [0, 0, 0]]
* diff[0][2] -= 2  => [[2, 0, -2], [0, 0, 0], [0, 0, 0]]
* diff[2][0] -= 2  => [[2, 0, -2], [0, 0, 0], [-2, 0, 0]]
* diff[2][2] += 2  => [[2, 0, -2], [0, 0, 0], [-2, 0, 2]]
*
* After Op2 [-1,1,0,2,2]:
* diff[1][0] -= 1  => [[2, 0, -2], [-1, 0, 0], [-2, 0, 2]]
* (others out of bounds)
*
* Row-wise prefix sum:
* [[2, 2, 0], [-1, -1, -1], [-2, -2, 0]]
*
* Column-wise prefix sum:
* [[2, 2, 0], [1, 1, -1], [-1, -1, -1]]
*
* Final add to mat:
* [[1+2, 2+2, 3+0], [1+1, 1+1, 0-1], [4-1, -2-1, 2-1]]
* [[3, 4, 3], [2, 2, -1], [3, -3, 1]]
*
*/
```

---

## 🎯 Key Insights

- **Only Four Updates Per Query:**  
  Instead of updating every cell in a rectangle, update just four corners in a helper array.
- **Prefix Sums:**  
  Row-wise and column-wise prefix sums propagate those updates to the entire submatrix.
- **Efficiency:**  
  Each operation is $O(1)$. Total time is $O(q + n \times m)$.

---

## 🔎 Further Applications

- Efficient grid simulations
- Image region adjustment
- Terrain/game map editing
- Spreadsheet batch operations

---

## 📚 References

- [GeeksforGeeks - 2D Difference Array (Original Problem)](https://www.geeksforgeeks.org/problems/2-d-difference-array/1)
- [Difference Array Techniques (Article)](https://www.geeksforgeeks.org/difference-array/)

---

## 🧑‍💻 Author

<div>
    <a href="https://github.com/imnilesh18">imnilesh18</a>
</div>

---

## 🏷️ Tags

![Matrix](https://img.shields.io/badge/Matrix-4a5568?style=for-the-badge)
![Array](https://img.shields.io/badge/Array-4a5568?style=for-the-badge)
![Prefix Sum](https://img.shields.io/badge/Prefix%20Sum-4a5568?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks)

---

## 📜 License

This project is licensed under the MIT License.

**A gentle reminder:** The solutions and explanations in this repository are for educational purposes. They are meant to help you understand the problem-solving process. Please try to solve the problems on your own before referring to the solutions.

Happy Coding! 🎉
