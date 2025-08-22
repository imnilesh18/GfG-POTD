# Median in a row-wise sorted Matrix

<div align="center">

![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-55.05%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1).

## </div>

## 📝 Problem Statement

Given a row-wise sorted matrix `mat[][]` of size `n*m`, where the number of rows `n` and columns `m` is always **odd**. Return the **median** of the matrix.

### Constraints

- `1 ≤ n, m ≤ 400`
- `1 ≤ mat[i][j] ≤ 2000`

---

## 🧪 Examples

### Example 1:

```

Input:
mat[][] = [[1, 3, 5],
[2, 6, 9],
[3, 6, 9]]
Output: 5
Explanation: Sorting the matrix elements gives us [1, 2, 3, 3, 5, 6, 6, 9, 9]. Hence, 5 is the median.

```

<details>
<summary>📖 Example Breakdown</summary>

1.  **Total Elements**: The matrix is 3x3, so there are `3 * 3 = 9` elements.
2.  **Median Position**: The median is the middle element in a sorted list. For `N` elements, the median is at index `(N-1)/2`. Here, `(9-1)/2 = 4`. So we need the 5th element (0-indexed) of the sorted version of the matrix.
3.  **Sorted Array**: If we flatten and sort the matrix, we get: `[1, 2, 3, 3, 5, 6, 6, 9, 9]`.
4.  **Find Median**: The element at index 4 is `5`.
5.  **Our Goal**: The challenge is to find this median `without` actually creating the sorted array, as that would be inefficient (O(n*m log(n*m)) time and O(n*m) space). The optimal solution uses binary search on the *range of values\* in the matrix.

</details>

### Example 2:

```

Input:
mat[][] = [[2, 4, 9],
[3, 6, 7],
[4, 7, 10]]
Output: 6
Explanation: Sorting matrix elements gives us [2, 3, 4, 4, 6, 7, 7, 9, 10]. Hence, 6 is the median.

```

### Example 3:

```

Input:
mat = [[3], [4], [8]]
Output: 4
Explanation: Sorting matrix elements gives us [3, 4, 8]. Hence, 4 is the median.

```

---

## 💡 Solution Approaches

The problem can be solved efficiently by performing a binary search on the range of possible median values. The key insight is that for any number `mid`, we can efficiently count how many elements in the matrix are less than or equal to `mid`.

### Optimized Approach (Binary Search)

The range of possible values for the median is between the minimum and maximum elements in the matrix. We can find this range by iterating through the first and last elements of each row.

We then binary search on this range (`low` to `high`). For each `mid` value, we count how many elements in the matrix are less than or equal to `mid`. Since each row is sorted, this count can be found in `O(log m)` time per row using `upper_bound`.

- If the count is less than the desired median position (`(n*m + 1) / 2`), it means the median must be larger, so we update `low = mid + 1`.
- If the count is greater than or equal to the desired position, `mid` could be our median (or the median could be smaller), so we update `high = mid`.

The loop continues until `low` and `high` converge, giving us the median value.

### C++ Solution

```cpp
// Intuition: The median of the matrix must lie within the range of the minimum and maximum values present in the matrix. We can binary search on this potential range of answers. For any given number 'mid', we can efficiently count how many elements in the matrix are less than or equal to it. This count helps us narrow down the search space.
// Approach:
// 1. Determine the search range. The minimum possible median is the smallest element in the matrix (found in the first column), and the maximum is the largest (found in the last column).
// 2. Calculate the desired position of the median, which is (n*m + 1) / 2.
// 3. Apply binary search on the range [minVal, maxVal].
// 4. For each 'mid' value in the binary search, count the number of elements in the matrix that are less than or equal to 'mid'. This can be done efficiently for each row using 'upper_bound' since rows are sorted.
// 5. If this count ('place') is less than the desired median position, it means our assumed median 'mid' is too small. We need to search in the higher range, so we set low = mid + 1.
// 6. If the count is greater than or equal to the desired position, 'mid' is a potential median, or the actual median is even smaller. We narrow the search to the lower range by setting high = mid.
// 7. The loop terminates when low equals high, and this value is the median.
// Time Complexity: O(n * log(m) * log(maxVal - minVal)). The binary search on the answer range takes log(maxVal - minVal) iterations. Inside each iteration, we iterate through 'n' rows, and for each row, we perform an upper_bound operation which takes O(log m) time.
// Space Complexity: O(1), as we are not using any extra space that depends on the input size.

class Solution {
  public:
    int median(vector<vector<int>> &mat) {
        int n = mat.size();
        int m = mat[0].size();

        int minVal = INT_MAX, maxVal = INT_MIN;

        // Find the minimum and maximum elements to define the search range.
        // The minimum is among the first elements of rows, max is among the last.
        for (int i = 0; i < n; i++) {
            if (mat[i][0] < minVal)
                minVal = mat[i][0];
            if (mat[i][m - 1] > maxVal)
                maxVal = mat[i][m - 1];
        }

        // The desired rank of the median element
        int desired = (n * m + 1) / 2;
        int lo = minVal, hi = maxVal;

        // Binary search on the range of possible values
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int place = 0;

            // Count elements smaller than or equal to mid in the entire matrix
            for (int i = 0; i < n; ++i) {
                // upper_bound finds the first element greater than mid.
                // The distance from the beginning gives the count of elements <= mid.
                place += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }

            // Adjust the search range based on the count
            if (place < desired) {
                // If count is less than desired, median must be in the right half
                lo = mid + 1;
            } else {
                // If count is sufficient, mid could be the median or it's in the left half
                hi = mid;
            }
        }
        return lo; // lo and hi converge to the median
    }
};

/*
*
* Dry Run
*
* Input: mat[][] = [[1, 3, 5], [2, 6, 9], [3, 6, 9]]
* n = 3, m = 3
* minVal = 1, maxVal = 9
* desired = (3 * 3 + 1) / 2 = 5
*
* Iteration 1:
* lo = 1, hi = 9
* mid = 1 + (9 - 1) / 2 = 5
* place = 0
* Row 1 ([1, 3, 5]): upper_bound for 5 is at index 3. Count = 3.
* Row 2 ([2, 6, 9]): upper_bound for 5 is at index 1. Count = 1.
* Row 3 ([3, 6, 9]): upper_bound for 5 is at index 1. Count = 1.
* total place = 3 + 1 + 1 = 5
* Since place (5) is not less than desired (5), we set hi = mid = 5.
*
* Iteration 2:
* lo = 1, hi = 5
* mid = 1 + (5 - 1) / 2 = 3
* place = 0
* Row 1 ([1, 3, 5]): upper_bound for 3 is at index 2. Count = 2.
* Row 2 ([2, 6, 9]): upper_bound for 3 is at index 1. Count = 1.
* Row 3 ([3, 6, 9]): upper_bound for 3 is at index 1. Count = 1.
* total place = 2 + 1 + 1 = 4
* Since place (4) is less than desired (5), we set lo = mid + 1 = 4.
*
* Iteration 3:
* lo = 4, hi = 5
* mid = 4 + (5 - 4) / 2 = 4
* place = 0
* Row 1 ([1, 3, 5]): upper_bound for 4 is at index 2. Count = 2.
* Row 2 ([2, 6, 9]): upper_bound for 4 is at index 1. Count = 1.
* Row 3 ([3, 6, 9]): upper_bound for 4 is at index 1. Count = 1.
* total place = 2 + 1 + 1 = 4
* Since place (4) is less than desired (5), we set lo = mid + 1 = 5.
*
* Iteration 4:
* lo = 5, hi = 5
* The loop condition (lo < hi) is false.
*
* Return lo, which is 5.
*
*/
```

### Java Solution

```java
// Intuition: The core idea is to leverage the sorted nature of rows to efficiently find the median without flattening the matrix. By recognizing that the median must fall within the matrix's min/max value range, we can apply binary search on this range of values. For any potential median `mid`, we can quickly determine its rank (how many elements are smaller or equal to it) and adjust our search space accordingly.
// Approach:
// 1. Find the overall minimum and maximum values in the matrix to establish the search space for the binary search. The minimum will be the smallest of the first elements of each row, and the maximum will be the largest of the last elements.
// 2. Calculate the required rank of the median element, which is `(n*m + 1) / 2`.
// 3. Perform a binary search on the value range `[min, max]`.
// 4. For each `mid` value, count how many elements in the entire matrix are less than or equal to `mid`.
// 5. This count is found by summing up the counts from each row. For each row, a helper binary search function (`upperBound`) finds the count of elements `<= mid` in O(log m) time.
// 6. If the total count (`place`) is less than the desired rank, it implies the true median is larger than `mid`, so we search in the right half by setting `min = mid + 1`.
// 7. Otherwise, `mid` could be the median, or a smaller value could be. So we shrink the search space to the left half by setting `max = mid`.
// 8. The loop terminates when `min` and `max` converge to a single value, which is the median.
// Time Complexity: O(n * log(m) * log(maxVal - minVal)). The main binary search runs in log(range) time. For each step, it iterates through 'n' rows, and the upperBound function for each row takes O(log m) time.
// Space Complexity: O(1), as no auxiliary data structures are used that scale with the input size.

class Solution {
    // Helper function to find the count of elements <= num in a sorted row
    static int upperBound(int[] row, int num) {
        int low = 0, high = row.length;
        // Standard binary search to find the insertion point for 'num'
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (row[mid] <= num) {
                low = mid + 1; // Move right if current element is <= num
            } else {
                high = mid; // Move left if current element is > num
            }
        }
        return low; // 'low' is the count of elements <= num
    }

    static int median(int mat[][]) {
        int n = mat.length;
        int m = mat[0].length;

        // Initializing the minimum and maximum values for the binary search range
        int min = Integer.MAX_VALUE,
            max = Integer.MIN_VALUE;

        // Iterate through each row to find the overall min and max values
        for (int i = 0; i < n; i++) {
            // Update min with the first element of the row if it's smaller
            if (mat[i][0] < min)
                min = mat[i][0];

            // Update max with the last element of the row if it's larger
            if (mat[i][m - 1] > max)
                max = mat[i][m - 1];
        }

        // Calculate the desired position of the median element
        int desired = (n * m + 1) / 2;

        // Binary search for the median value within the [min, max] range
        while (min < max) {
            // Calculate the middle value of the current range
            int mid = min + (max - min) / 2;

            // Count the number of elements less than or equal to mid
            int place = 0;
            for (int i = 0; i < n; i++) {
                place += upperBound(mat[i], mid);
            }

            // Update the search range based on the count of elements
            if (place < desired) {
                // If count is too small, the median must be larger than mid
                min = mid + 1;
            } else {
                // If count is sufficient, mid is a potential median, search for smaller values
                max = mid;
            }
        }

        // 'min' will converge to the median value
        return min;
    }
}
/*
*
* Dry Run
*
* Input: mat[][] = [[1, 3, 5], [2, 6, 9], [3, 6, 9]]
* n = 3, m = 3
* min = 1, max = 9
* desired = (3 * 3 + 1) / 2 = 5
*
* Iteration 1:
* min = 1, max = 9
* mid = 1 + (9 - 1) / 2 = 5
* place = 0
* Row 1 ([1, 3, 5]): upperBound for 5 is 3.
* Row 2 ([2, 6, 9]): upperBound for 5 is 1.
* Row 3 ([3, 6, 9]): upperBound for 5 is 1.
* total place = 3 + 1 + 1 = 5
* Since place (5) is not < desired (5), set max = mid = 5.
*
* Iteration 2:
* min = 1, max = 5
* mid = 1 + (5 - 1) / 2 = 3
* place = 0
* Row 1 ([1, 3, 5]): upperBound for 3 is 2.
* Row 2 ([2, 6, 9]): upperBound for 3 is 1.
* Row 3 ([3, 6, 9]): upperBound for 3 is 1.
* total place = 2 + 1 + 1 = 4
* Since place (4) < desired (5), set min = mid + 1 = 4.
*
* Iteration 3:
* min = 4, max = 5
* mid = 4 + (5 - 4) / 2 = 4
* place = 0
* Row 1 ([1, 3, 5]): upperBound for 4 is 2.
* Row 2 ([2, 6, 9]): upperBound for 4 is 1.
* Row 3 ([3, 6, 9]): upperBound for 4 is 1.
* total place = 2 + 1 + 1 = 4
* Since place (4) < desired (5), set min = mid + 1 = 5.
*
* Iteration 4:
* min = 5, max = 5
* The loop condition (min < max) is false.
*
* Return min, which is 5.
*
*/
```

---

## 🔑 Key Insights

- **Binary Search on Answer**: The core idea is to not search for the _position_ of the median, but to binary search for the _value_ of the median itself.
- **Monotonicity**: The key property that allows binary search is monotonicity. For a number `x`, let `count(x)` be the number of elements in the matrix less than or equal to `x`. If we increase `x`, `count(x)` will either stay the same or increase. This monotonic behavior is what allows us to effectively shrink our search space.
- **Efficient Counting**: Because each row is sorted, we can find the count of elements less than or equal to `mid` in a single row in `O(log m)` time instead of `O(m)`. This is the critical optimization that makes the overall solution efficient.

---

## 🚀 Further Exploration

- [Kth element in Matrix](https://www.geeksforgeeks.org/problems/kth-element-in-matrix/1)
- [Search in a row-column sorted Matrix](https://www.geeksforgeeks.org/problems/search-in-a-matrix-1587115621/1)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks | Median in a row-wise sorted Matrix](https://www.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Reminder on Educational Use:** The solutions and explanations in this repository are for educational purposes. They are meant to help in understanding problem-solving techniques and should be used as a reference, not for direct submission to online judges.
