# 🟧 Maximum sum Rectangle

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty: Hard">
  <img src="https://img.shields.io/badge/Accuracy-49.78%25-yellow?style=for-the-badge" alt="Accuracy: 49.78%">
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points: 8">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</div>

---

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximum-sum-rectangle2948/1).

---

## 📄 Problem Statement

Given a 2D matrix `mat[][]` with dimensions `n x m`, your task is to find the maximum possible sum of any submatrix (a rectangular block of cells) within the given matrix.

---

## 📖 Examples

### Example 1:

**Input:**

```
mat[][] = [[1, 2, -1, -4, -20],
           [-8, -3, 4, 2, 1],
           [3, 8, 10, 1, 3],
           [-4, -1, 1, 7, -6]]
```

**Output:**

```
29
```

**Explanation:**
The submatrix with the maximum sum is highlighted in green below, which sums to 29.

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/899247/Web/Other/blobid0_1751695089.jpg" alt="Maximum Sum Submatrix" width="400"/>
</div>

The submatrix is:

```
 -3   4   2
  8  10   1
 -1   1   7
```

The sum is `-3 + 4 + 2 + 8 + 10 + 1 + (-1) + 1 + 7 = 29`.

<details>
<summary><b>📖 Example Breakdown</b></summary>

1.  **Goal**: Find the rectangular submatrix with the largest possible sum.
2.  **Matrix**:
    ```
    [[ 1,  2, -1, -4, -20],
     [-8, -3,  4,  2,   1],
     [ 3,  8, 10,  1,   3],
     [-4, -1,  1,  7,  -6]]
    ```
3.  **Strategy**: The core idea is to fix the `left` and `right` columns of a potential submatrix and use Kadane's algorithm. The actual submatrix that gives the sum of 29 is found when we fix the `left` column at index 1 and the `right` column at index 3.
4.  Let's "compress" the columns from `left=1` to `right=3` into a temporary 1D array by summing the elements row by row.
    - `temp[0]` = `mat[0][1]` + `mat[0][2]` + `mat[0][3]` = `2 + (-1) + (-4)` = `-3`
    - `temp[1]` = `mat[1][1]` + `mat[1][2]` + `mat[1][3]` = `-3 + 4 + 2` = `3`
    - `temp[2]` = `mat[2][1]` + `mat[2][2]` + `mat[2][3]` = `8 + 10 + 1` = `19`
    - `temp[3]` = `mat[3][1]` + `mat[3][2]` + `mat[3][3]` = `-1 + 1 + 7` = `7`
5.  The temporary 1D array is `[-3, 3, 19, 7]`.
6.  Now, we apply **Kadane's Algorithm** on this 1D array to find the maximum sum subarray.
    - For `[-3, 3, 19, 7]`:
      - Start with `max_so_far = -3`, `current_max = -3`. `current_max` becomes `0`.
      - Next element is `3`. `current_max` becomes `3`. `max_so_far` is `3`.
      - Next is `19`. `current_max` becomes `3 + 19 = 22`. `max_so_far` is `22`.
      - Next is `7`. `current_max` becomes `22 + 7 = 29`. `max_so_far` is `29`.
7.  This sum of `29` is the maximum we find across all possible `(left, right)` column pairs. The subarray that produced this sum was `[3, 19, 7]`, which corresponds to the correct rows and columns in the original matrix.

</details>

### Example 2:

**Input:**

```
mat[][] = [[-1, -2],
           [-3, -4]]
```

**Output:**

```
-1
```

**Explanation:**
The largest sum is obtained by taking just the single element `-1`. All other submatrices result in a smaller (more negative) sum.

---

## ⛓️ Constraints

- `1 ≤ n, m ≤ 300`
- `-1000 ≤ mat[i][j] ≤ 1000`

---

## 💡 Solution Approaches

### Optimized Approach (Using Kadane's Algorithm)

The problem can be reduced from a 2D problem to a 1D problem. We can iterate through all possible pairs of left and right columns. For each pair, we create a temporary 1D array that holds the sum of elements for each row between these two columns. Then, we apply Kadane's algorithm on this 1D array to find the maximum sum subarray. This maximum sum corresponds to the maximum sum of a submatrix with the fixed left and right columns. We keep track of the overall maximum sum found across all column pairs.

#### C++ Solution

```cpp
// Intuition: The problem can be solved by iterating through all possible column combinations (left and right boundaries) and for each combination, reducing the 2D matrix to a 1D array. Kadane's algorithm can then find the maximum sum subarray in this 1D array, which corresponds to the maximum sum submatrix for the chosen column boundaries.
// Approach:
// 1. Initialize `maxSum` to a very small number.
// 2. Use two nested loops to fix the `left` and `right` boundaries of the submatrix.
// 3. For each `(left, right)` pair, create a temporary 1D array `temp` of size `rows`.
// 4. Populate `temp` where `temp[i]` is the sum of elements in `mat[i]` from column `left` to `right`.
// 5. Apply Kadane's algorithm on the `temp` array to find the maximum subarray sum for this `(left, right)` configuration.
// 6. Update the global `maxSum` with the result from Kadane's if it's greater.
// 7. After checking all `(left, right)` pairs, `maxSum` will hold the final answer.
// Time Complexity: O(cols * cols * rows), as we have two nested loops for columns and an inner loop for Kadane's algorithm which takes O(rows).
// Space Complexity: O(rows), for the temporary array `temp` used to store row sums.
class Solution {
  public:
    // Kadane's algorithm to find the maximum sum subarray in a 1D array
    int kadane(vector<int>& temp) {
      	int rows = temp.size();
        int currSum = 0;
        int maxSum = INT_MIN;

        for (int i = 0; i < rows; i++) {
            currSum += temp[i];

            // Update maxSum if the current sum is greater
            if (maxSum < currSum) {
                maxSum = currSum;
            }

            // If the current sum becomes negative, reset it to 0
            // A negative sum subarray will not contribute to a larger maximum
            if (currSum < 0) {
                currSum = 0;
            }
        }
        return maxSum;
    }

    // Function to find the maximum sum rectangle in a 2D matrix
    int maxRectSum(vector<vector<int>> &mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        int maxSum = INT_MIN;

        // Temporary array to store row-wise sums between left and right boundaries
        vector<int> temp(rows);

        // Fix the left boundary
        for (int left = 0; left < cols; left++) {

            // Reset the temporary array for each new left boundary
            fill(temp.begin(), temp.end(), 0);

            // Fix the right boundary
            for (int right = left; right < cols; right++) {

                // Calculate the sum of elements of each row for the current [left, right] columns
                for (int row = 0; row < rows; row++) {
                    temp[row] += mat[row][right];
                }

                // Apply Kadane's algorithm on the temporary array
                int sum = kadane(temp);

                // Update the overall maximum sum
                maxSum = max(maxSum, sum);
            }
        }
        return maxSum;
    }
};

/*
*
* Dry Run
*
* mat = [[1, 2], [-3, 4]]
*
* left = 0:
* right = 0:
* temp = [1, -3]
* kadane(temp) -> 1
* maxSum = 1
*
* right = 1:
* temp = [1+2, -3+4] = [3, 1]
* kadane(temp) -> 4
* maxSum = 4
*
* left = 1:
* right = 1:
* temp = [2, 4]
* kadane(temp) -> 6
* maxSum = 6
*
* Final Answer: 6
*
*/
```

#### Java Solution

```java
// Intuition: The problem can be solved by iterating through all possible column combinations (left and right boundaries) and for each combination, reducing the 2D matrix to a 1D array. Kadane's algorithm can then find the maximum sum subarray in this 1D array, which corresponds to the maximum sum submatrix for the chosen column boundaries.
// Approach:
// 1. Initialize `maxSum` to a very small number.
// 2. Use two nested loops to fix the `left` and `right` boundaries of the submatrix.
// 3. For each `(left, right)` pair, create a temporary 1D array `temp` of size `rows`.
// 4. Populate `temp` where `temp[i]` is the sum of elements in `mat[i]` from column `left` to `right`.
// 5. Apply Kadane's algorithm on the `temp` array to find the maximum subarray sum for this `(left, right)` configuration.
// 6. Update the global `maxSum` with the result from Kadane's if it's greater.
// 7. After checking all `(left, right)` pairs, `maxSum` will hold the final answer.
// Time Complexity: O(cols * cols * rows), as we have two nested loops for columns and an inner loop for Kadane's algorithm which takes O(rows).
// Space Complexity: O(rows), for the temporary array `temp` used to store row sums.
class Solution {
    // Kadane's algorithm to find the maximum sum subarray in a 1D array
    static int kadane(int[] temp) {
        int rows = temp.length;
        int currSum = 0;
        int maxSum = Integer.MIN_VALUE;

        for (int i = 0; i < rows; i++) {
            currSum += temp[i];

            // Update maxSum if the current sum is greater
            if (maxSum < currSum) {
                maxSum = currSum;
            }

            // If the current sum becomes negative, reset it to 0
            // A negative sum subarray will not contribute to a larger maximum
            if (currSum < 0) {
                currSum = 0;
            }
        }
        return maxSum;
    }

    // Function to find the maximum sum rectangle in a 2D matrix
    static int maxRectSum(int[][] mat) {
        int rows = mat.length;
        int cols = mat[0].length;
        int maxSum = Integer.MIN_VALUE;

        // Temporary array to store row-wise sums between left and right boundaries
        int[] temp = new int[rows];

        // Fix the left boundary
        for (int left = 0; left < cols; left++) {

            // Reset the temporary array for each new left boundary
            Arrays.fill(temp, 0);

            // Fix the right boundary
            for (int right = left; right < cols; right++) {

                // Calculate the sum of elements of each row for the current [left, right] columns
                for (int row = 0; row < rows; row++) {
                    temp[row] += mat[row][right];
                }

                // Apply Kadane's algorithm on the temporary array
                int sum = kadane(temp);

                // Update the overall maximum sum
                maxSum = Math.max(maxSum, sum);
            }
        }
        return maxSum;
    }
}

/*
*
* Dry Run
*
* mat = [[1, 2], [-3, 4]]
*
* left = 0:
* right = 0:
* temp = [1, -3]
* kadane(temp) -> 1
* maxSum = 1
*
* right = 1:
* temp = [1+2, -3+4] = [3, 1]
* kadane(temp) -> 4
* maxSum = 4
*
* left = 1:
* right = 1:
* temp = [2, 4]
* kadane(temp) -> 6
* maxSum = 6
*
* Final Answer: 6
*
*/
```

---

## 🔑 Key Insights

- **Dimensionality Reduction**: The core trick is to convert the 2D matrix problem into a series of 1D array problems.
- **Kadane's Algorithm**: This classic algorithm is perfect for finding the maximum sum subarray in a 1D array. By fixing the left and right column boundaries, we create a 1D array representing the sum of rows, allowing us to efficiently find the best top and bottom boundaries for that column selection using Kadane's.
- **Iterative Approach**: By systematically considering every possible pair of `left` and `right` columns, we ensure that every possible submatrix is evaluated, guaranteeing the discovery of the one with the maximum sum.

---

## 🚀 Further Exploration

- [Maximum Subarray Sum](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/) (The 1D version of this problem)
- [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) (Find the largest rectangle containing only 1s in a binary matrix)
- [Largest rectangular sub-matrix whose sum is 0](https://www.geeksforgeeks.org/problems/largest-rectangular-sub-matrix-whose-sum-is-0/1)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - Maximum sum Rectangle](https://www.geeksforgeeks.org/problems/maximum-sum-rectangle2948/1)
- **Kadane's Algorithm:** [GeeksforGeeks Article](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)

---

## ✍️ Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="center">
  <img src="https://img.shields.io/badge/dynamic programming-4285F4?style=for-the-badge" alt="Dynamic Programming">
  <img src="https://img.shields.io/badge/kadane's algorithm-DB4437?style=for-the-badge" alt="Kadane's Algorithm">
  <img src="https://img.shields.io/badge/matrix-0F9D58?style=for-the-badge" alt="Matrix">
  <img src="https://img.shields.io/badge/array-F4B400?style=for-the-badge" alt="Array">
  <img src="https://img.shields.io/badge/geeksforgeeks-298D46?style=for-the-badge" alt="GeeksforGeeks">
</div>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Note on Educational Use:** This content is for educational and learning purposes. It is not intended for submission to any coding platform for points or ratings, as this would violate their terms of service.
