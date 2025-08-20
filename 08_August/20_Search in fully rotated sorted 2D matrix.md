# MATRIX - Search in fully rotated sorted 2D matrix

> ⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/search-in-fully-rotated-sorted-2d-matrix/1).

<div align="center">
    <img src="https://github.com/imnilesh18/gfg-potd/assets/73957723/6f7d0220-4171-4176-857c-87d21c17223b" alt="GeeksforGeeks Problem of the Day" width="800"/>
</div>

<p align="center">
    <a href="https://www.geeksforgeeks.org/problems/search-in-fully-rotated-sorted-2d-matrix/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG Problem">
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
    <img src="https://img.shields.io/badge/Accuracy-56.77%25-brightgreen?style=for-the-badge" alt="Accuracy: 56.77%">
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
    <img src="https://img.shields.io/badge/License-MIT-purple?style=for-the-badge" alt="License: MIT">
</p>

---

## 📝 Problem Statement

You are given a 2D matrix `mat[][]` of size `n x m` that was initially filled in the following manner:

- Each row is sorted in increasing order from left to right.
- The first element of every row is greater than the last element of the previous row.

This implies that if the matrix is flattened row-wise, it forms a strictly sorted 1D array.
Later, this sorted 1D array was rotated at some unknown pivot. The rotated array was then written back into the matrix row-wise to form the current matrix.

Given such a matrix `mat[][]` and an integer `x`, determine whether `x` exists in the matrix.

---

## Examples

### Example 1:

**Input:**

```
x = 3
mat[][] = [[7, 8, 9, 10],
           [11, 12, 13, 1],
           [2, 3, 4, 5]]
```

**Output:**

```
true
```

**Explanation:**
3 is located at the 3rd row and 2nd column.

<details>
<summary>📖 Example Breakdown</summary>
<div>
The matrix, when flattened, would be `[7, 8, 9, 10, 11, 12, 13, 1, 2, 3, 4, 5]`. This is a rotated version of `[1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13]`. We need to find `x = 3` in this structure. By applying a modified binary search, we can efficiently locate the target.
</div>
</details>

---

### Example 2:

**Input:**

```
x = 10
mat[][] = [[6, 7, 8],
           [9, 1, 2],
           [3, 4, 5]]
```

**Output:**

```
false
```

**Explanation:**
The value 10 does not exist in the matrix.

---

## ⛓️ Constraints

- `1 ≤ n × m ≤ 10^5`
- `1 ≤ mat[i][j], x ≤ 10^6`

---

## 💡 Solution Approaches

### Optimized Approach (Binary Search)

The core idea is to treat the 2D matrix as a 1D array and apply a binary search algorithm tailored for rotated sorted arrays.

- **Intuition**: Since the flattened matrix is a rotated sorted array, we can use binary search. The main challenge is to determine which half of the search space is sorted and whether the target lies within that sorted portion.
- **Approach**: We use two pointers, `low` and `high`, to represent the start and end indices of the flattened array (`0` to `n*m - 1`). In each step, we calculate the `mid` index and its corresponding 2D coordinates. We compare `mat[mid/m][mid%m]` with the target `x`. Then, we check if the left half (`low` to `mid`) is sorted. If it is, we see if `x` lies in this range. If so, we search in the left half; otherwise, we search in the right half. If the left half is not sorted, the right half must be. We then perform a similar check for the right half. This process narrows down the search space until the element is found or the search space is exhausted.

---

### C++ Solution

```cpp
// Intuition: The problem can be modeled as searching for an element in a rotated sorted array, but in a 2D matrix. By treating the matrix as a flattened 1D array, we can apply a modified binary search to find the target element efficiently. The key is to correctly identify the sorted half of the array at each step to narrow down the search space.
// Approach:
// 1. Initialize `low` to 0 and `high` to (n * m) - 1, representing the flattened 1D array indices.
// 2. Perform a binary search while `low <= high`.
// 3. Calculate `mid` index and convert it to 2D matrix coordinates: `row = mid / m`, `col = mid % m`.
// 4. If `mat[row][col]` equals the target `x`, return true.
// 5. Check if the left part of the array (from `low` to `mid`) is sorted. This is true if `mat[low/m][low%m] <= mat[mid/m][mid%m]`.
//    a. If sorted, check if `x` lies within the range of this sorted part.
//    b. If `x` is in range, search the left half by setting `high = mid - 1`.
//    c. Otherwise, search the right half by setting `low = mid + 1`.
// 6. If the left part is not sorted, the right part (from `mid` to `high`) must be sorted.
//    a. Check if `x` lies within the range of this sorted right part.
//    b. If `x` is in range, search the right half by setting `low = mid + 1`.
//    c. Otherwise, search the left half by setting `high = mid - 1`.
// 7. If the loop finishes without finding `x`, return false.
// Time Complexity: O(log(n*m)), as we perform a binary search on the entire matrix treated as a 1D array of size n*m.
// Space Complexity: O(1), as we only use a few variables to keep track of indices, requiring no extra space proportional to the input size.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        int n = mat.size();    // Number of rows
        int m = mat[0].size(); // Number of columns
        int low = 0, high = n * m - 1; // Flattened array indices

        while (low <= high) {
            int mid = low + (high - low) / 2; // Calculate mid index
            int row = mid / m; // Convert mid to 2D row index
            int col = mid % m; // Convert mid to 2D col index

            // Check if the middle element is the target
            if (mat[row][col] == x) {
                return true;
            }

            // Check if the left half is sorted
            if (mat[low / m][low % m] <= mat[row][col]) {
                // Check if target is in the sorted left half
                if (x >= mat[low / m][low % m] && x < mat[row][col]) {
                    high = mid - 1; // Search left
                } else {
                    low = mid + 1; // Search right
                }
            } else { // The right half must be sorted
                // Check if target is in the sorted right half
                if (x > mat[row][col] && x <= mat[high / m][high % m]) {
                    low = mid + 1; // Search right
                } else {
                    high = mid - 1; // Search left
                }
            }
        }
        return false; // Target not found
    }
};

/*
*
* Dry Run
*
* mat = [[7, 8, 9, 10], [11, 12, 13, 1], [2, 3, 4, 5]], x = 3
* n = 3, m = 4
*
* Initial: low = 0, high = 11
*
* Iteration 1:
* mid = 5 -> (1, 1), mat[1][1] = 12
* mat[0][0] (7) <= mat[1][1] (12) -> left half is sorted.
* Is 3 between 7 and 12? No.
* low = mid + 1 = 6
*
* Iteration 2:
* low = 6, high = 11
* mid = 8 -> (2, 0), mat[2][0] = 2
* mat[1][2] (13) > mat[2][0] (2) -> left half is not sorted.
* Right half [2, 3, 4, 5] is sorted.
* Is 3 between 2 and 5? Yes.
* low = mid + 1 = 9
*
* Iteration 3:
* low = 9, high = 11
* mid = 10 -> (2, 2), mat[2][2] = 4
* mat[2][1] (3) <= mat[2][2] (4) -> left half is sorted.
* Is 3 between 3 and 4? Yes.
* high = mid - 1 = 9
*
* Iteration 4:
* low = 9, high = 9
* mid = 9 -> (2, 1), mat[2][1] = 3
* mat[2][1] == x -> found!
* return true
*
*/
```

---

### Java Solution

```java
// Intuition: The problem can be modeled as searching for an element in a rotated sorted array, but in a 2D matrix. By treating the matrix as a flattened 1D array, we can apply a modified binary search to find the target element efficiently. The key is to correctly identify the sorted half of the array at each step to narrow down the search space.
// Approach:
// 1. Initialize `low` to 0 and `high` to (n * m) - 1, representing the flattened 1D array indices.
// 2. Perform a binary search while `low <= high`.
// 3. Calculate `mid` index and convert it to 2D matrix coordinates: `row = mid / m`, `col = mid % m`.
// 4. If `mat[row][col]` equals the target `x`, return true.
// 5. Check if the left part of the array (from `low` to `mid`) is sorted. This is true if `mat[low/m][low%m] <= mat[mid/m][mid%m]`.
//    a. If sorted, check if `x` lies within the range of this sorted part.
//    b. If `x` is in range, search the left half by setting `high = mid - 1`.
//    c. Otherwise, search the right half by setting `low = mid + 1`.
// 6. If the left part is not sorted, the right part (from `mid` to `high`) must be sorted.
//    a. Check if `x` lies within the range of this sorted right part.
//    b. If `x` is in range, search the right half by setting `low = mid + 1`.
//    c. Otherwise, search the left half by setting `high = mid - 1`.
// 7. If the loop finishes without finding `x`, return false.
// Time Complexity: O(log(n*m)), as we perform a binary search on the entire matrix treated as a 1D array of size n*m.
// Space Complexity: O(1), as we only use a few variables to keep track of indices, requiring no extra space proportional to the input size.

class Solution {
    public boolean searchMatrix(int[][] mat, int x) {
        int n = mat.length;    // Number of rows
        int m = mat[0].length; // Number of columns
        int low = 0, high = n * m - 1; // Flattened array indices

        while (low <= high) {
            int mid = low + (high - low) / 2; // Calculate mid index
            int row = mid / m; // Convert mid to 2D row index
            int col = mid % m; // Convert mid to 2D col index

            // Check if the middle element is the target
            if (mat[row][col] == x) {
                return true;
            }

            // Check if the left half is sorted
            if (mat[low / m][low % m] <= mat[row][col]) {
                // Check if target is in the sorted left half
                if (x >= mat[low / m][low % m] && x < mat[row][col]) {
                    high = mid - 1; // Search left
                } else {
                    low = mid + 1; // Search right
                }
            } else { // The right half must be sorted
                // Check if target is in the sorted right half
                if (x > mat[row][col] && x <= mat[high / m][high % m]) {
                    low = mid + 1; // Search right
                } else {
                    high = mid - 1; // Search left
                }
            }
        }
        return false; // Target not found
    }
}
/*
*
* Dry Run
*
* mat = [[7, 8, 9, 10], [11, 12, 13, 1], [2, 3, 4, 5]], x = 3
* n = 3, m = 4
*
* Initial: low = 0, high = 11
*
* Iteration 1:
* mid = 5 -> (1, 1), mat[1][1] = 12
* mat[0][0] (7) <= mat[1][1] (12) -> left half is sorted.
* Is 3 between 7 and 12? No.
* low = mid + 1 = 6
*
* Iteration 2:
* low = 6, high = 11
* mid = 8 -> (2, 0), mat[2][0] = 2
* mat[1][2] (13) > mat[2][0] (2) -> left half is not sorted.
* Right half [2, 3, 4, 5] is sorted.
* Is 3 between 2 and 5? Yes.
* low = mid + 1 = 9
*
* Iteration 3:
* low = 9, high = 11
* mid = 10 -> (2, 2), mat[2][2] = 4
* mat[2][1] (3) <= mat[2][2] (4) -> left half is sorted.
* Is 3 between 3 and 4? Yes.
* high = mid - 1 = 9
*
* Iteration 4:
* low = 9, high = 9
* mid = 9 -> (2, 1), mat[2][1] = 3
* mat[2][1] == x -> found!
* return true
*
*/
```

---

## 🔑 Key Insights

- **Virtual 1D Array**: The problem becomes much simpler by visualizing the 2D matrix as a single, flattened 1D array. The mapping from a 1D index `i` to 2D coordinates `(row, col)` is `row = i / m` and `col = i % m`, where `m` is the number of columns.
- **Rotated Sorted Array Logic**: The core of the solution is the standard algorithm for binary searching in a rotated sorted array. By checking `mat[low] <= mat[mid]`, we can quickly determine which half is sorted and then decide whether to search within that sorted portion or the other unsorted portion.

---

## 🚀 Further Exploration

- [Search a 2D Matrix](https://www.geeksforgeeks.org/search-in-a-row-wise-and-column-wise-sorted-matrix/) (Standard, not rotated)
- [Find minimum in rotated sorted array](https://www.geeksforgeeks.org/find-minimum-element-in-a-sorted-and-rotated-array/)
- [Search in Rotated Sorted Array II](https://www.geeksforgeeks.org/search-element-in-a-sorted-and-rotated-array-with-duplicates/) (with duplicates)

---

## 📚 References

- **Original Problem**: [GeeksforGeeks - Search in fully rotated sorted 2D matrix](https://www.geeksforgeeks.org/problems/search-in-fully-rotated-sorted-2d-matrix/1)
- **Binary Search on Rotated Array**: [GeeksforGeeks Article](https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p align="left">
  <a href="https://github.com/imnilesh18/gfg-potd/tree/main/tag/array">
    <img src="https://img.shields.io/badge/Array-2D-blue?style=for-the-badge" alt="Array">
  </a>
  <a href="https://github.com/imnilesh18/gfg-potd/tree/main/tag/binary-search">
    <img src="https://img.shields.io/badge/Binary Search-orange?style=for-the-badge" alt="Binary Search">
  </a>
  <a href="https://github.com/imnilesh18/gfg-potd/tree/main/tag/geeksforgeeks">
    <img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge" alt="GeeksforGeeks">
  </a>
</p>

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

<p align="center">
  <a href="https://github.com/imnilesh18/gfg-potd">
    <img src="https://img.shields.io/github/stars/imnilesh18/gfg-potd?style=social" alt="GitHub Stars">
  </a>
  <a href="https://github.com/imnilesh18/gfg-potd/fork">
    <img src="https://img.shields.io/github/forks/imnilesh18/gfg-potd?style=social" alt="GitHub Forks">
  </a>
</p>
