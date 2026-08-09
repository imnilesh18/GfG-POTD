# 🔀 Largest Zigzag Sequence

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/largest-zigzag-sequence5416/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-50.0%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a square matrix `mat[][]` of size $n \times n$. A zigzag sequence starts from the top row and ends at the bottom row. Two consecutive elements of the sequence **cannot belong to the same column**.

Return the maximum sum of such a zigzag sequence.

---

## 💡 Examples

### Example 1

```text
Input: mat[][] = [[3, 1, 2], [4, 8, 5], [6, 9, 7]]
Output: 18
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

One optimal zigzag sequence is: **3 -> 8 -> 7**.
* From Row 0: Select **3** (Column 0)
* From Row 1: Select **8** (Column 1) - Valid, as Column 1 != Column 0
* From Row 2: Select **7** (Column 2) - Valid, as Column 2 != Column 1

**Sum = 3 + 8 + 7 = 18.**
</details>

### Example 2

```text
Input: mat[][] = [[1, 2, 4], [3, 9, 6], [11, 3, 15]]
Output: 28
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

One optimal zigzag sequence is: **4 -> 9 -> 15**.
* From Row 0: Select **4** (Column 2)
* From Row 1: Select **9** (Column 1)
* From Row 2: Select **15** (Column 2)

**Sum = 4 + 9 + 15 = 28.**
</details>

---

## 🚧 Constraints

> - $1 \le n \le 100$
> - $1 \le mat[i][j] \le 1000$

---

## 🛠️ Solution Approach

### Space-Optimized Dynamic Programming

**Intuition:** 
To maximize the sum up to any cell in a row, we must add the matrix value of the current cell to the maximum sum obtained in the previous row, strictly avoiding the same column. 
A naive approach would check all columns of the previous row for each cell, resulting in an $O(n^3)$ time complexity. However, we can optimize this to $O(n^2)$ by simply keeping track of the **largest** and **second largest** values (and the column index of the largest value) in the previous row. 

If the current cell's column matches the largest value's column, we use the second largest value. Otherwise, we use the largest value. This guarantees valid zigzag steps while maximizing the sum. We can also optimize space by keeping track of only the previous row rather than an entire 2D DP array.

```cpp
// Intuition: To find the max zigzag path efficiently, track the top two maximum sums from the previous row. This avoids re-scanning the previous row for every element, reducing time complexity from O(n^3) to O(n^2).
// Approach:
// 1. Initialize a 1D array to store the maximum sequence sums up to the previous row.
// 2. Iterate through each row from the second row down to the last.
// 3. For the previous row, compute the maximum value (max1) and second maximum value (max2), tracking the column index of max1.
// 4. For each cell in the current row, if its column matches max1's column, add max2 to it. Otherwise, add max1.
// 5. Overwrite the previous row with the current row's results.
// 6. Return the maximum value found in the final processed row.
// Time Complexity: O(n^2) since we iterate through the matrix cells and do O(1) work per cell after a single O(n) sweep to find max1/max2 per row.
// Space Complexity: O(n) as we only use two 1D arrays of size n to store the current and previous DP states.

class Solution {
  public:
    int zigzagSequence(vector<vector<int>>& mat) {
        int n = mat.size();
        
        // Base case: If matrix has only 1 element, return it directly
        if (n == 1) return mat[0][0];

        // dp array storing the maximum sums ending at the previous row
        vector<int> prevRow = mat[0];
        vector<int> currRow(n, 0);

        // Iterate through each subsequent row
        for (int i = 1; i < n; ++i) {
            int max1 = -1, max1_idx = -1;
            int max2 = -1;

            // Find the highest and second highest values in prevRow
            for (int j = 0; j < n; ++j) {
                if (prevRow[j] > max1) {
                    max2 = max1;
                    max1 = prevRow[j];
                    max1_idx = j;
                } else if (prevRow[j] > max2) {
                    max2 = prevRow[j];
                }
            }

            // Compute maximum sequence sum for the current row
            for (int j = 0; j < n; ++j) {
                // If columns match, use the second max to maintain the zigzag rule
                if (j != max1_idx) {
                    currRow[j] = mat[i][j] + max1;
                } else {
                    currRow[j] = mat[i][j] + max2;
                }
            }
            // Move current row data to prevRow for the next loop
            prevRow = currRow;
        }

        // The answer is the maximum sum found in the final row
        int ans = 0;
        for (int j = 0; j < n; ++j) {
            ans = max(ans, prevRow[j]);
        }
        
        return ans;
    }
};

/*
 * Dry Run
 * 
 * Input: mat = [[3, 1, 2], 
 *               [4, 8, 5], 
 *               [6, 9, 7]]
 * 
 * Initialization:
 * prevRow = [3, 1, 2]
 * 
 * --- Iteration 1 (Row 1): [4, 8, 5] ---
 * prevRow values: [3, 1, 2]
 * max1 = 3 (at index 0), max2 = 2
 * j=0: col 0 == max1_idx(0), so use max2 -> currRow[0] = 4 + 2 = 6
 * j=1: col 1 != max1_idx(0), so use max1 -> currRow[1] = 8 + 3 = 11
 * j=2: col 2 != max1_idx(0), so use max1 -> currRow[2] = 5 + 3 = 8
 * Update prevRow = [6, 11, 8]
 * 
 * --- Iteration 2 (Row 2): [6, 9, 7] ---
 * prevRow values: [6, 11, 8]
 * max1 = 11 (at index 1), max2 = 8
 * j=0: col 0 != max1_idx(1), so use max1 -> currRow[0] = 6 + 11 = 17
 * j=1: col 1 == max1_idx(1), so use max2 -> currRow[1] = 9 + 8 = 17
 * j=2: col 2 != max1_idx(1), so use max1 -> currRow[2] = 7 + 11 = 18
 * Update prevRow = [17, 17, 18]
 * 
 * Final ans calculation:
 * max of [17, 17, 18] is 18.
 * Output: 18
 */
```

---

## 🔍 Key Insights

* **Precomputation Trick:** By determining the largest and second-largest elements of the previous state sequence just once per row, we drastically bring down the DP transition time from $O(n)$ to $O(1)$.
* **State Compression:** Since the current row's DP states rely strictly on the states of the immediate previous row, a full $N \times N$ matrix is unnecessary. Modifying it to use two 1D arrays brings auxiliary space down to $O(N)$.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Largest Zigzag Sequence](https://www.geeksforgeeks.org/problems/largest-zigzag-sequence5416/1)
* **Topic:** Dynamic Programming, Matrix

---

## ✍️ Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/-Dynamic_Programming-05122A?style=flat&logo=appveyor)
![Matrix](https://img.shields.io/badge/-Matrix-05122A?style=flat&logo=appveyor)
![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks-298D46?style=flat&logo=geeksforgeeks&logoColor=white)
