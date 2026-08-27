# 🟥 Largest Rectangle with Column Swaps

![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy: 60.08%](https://img.shields.io/badge/Accuracy-60.08%25-brightgreen?style=for-the-badge)
![Points: 8](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> ⚠️ **Educational Use Only**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a binary matrix `mat[][]` of size `n × m` containing only `0`s and `1`s, any pair of columns may be swapped any number of times. Return the **maximum area** of a rectangle consisting entirely of `1`s that can be formed after performing the column swaps.

---

## 💡 Examples

### Example 1
```text
Input: mat[][] = [[0, 1, 0, 1, 0], [0, 1, 0, 1, 1], [1, 1, 0, 1, 0]]
Output: 6
Explanation: After swapping the 2nd and 3rd columns, the largest rectangle of 1s has an area of 6.
```

### Example 2
```text
Input: mat[][] = [[0, 1, 1, 0, 0], [1, 1, 1, 0, 1], [1, 1, 1, 0, 1], [1, 1, 1, 1, 1]]
Output: 12
Explanation: After swapping the 4th and 5th columns, the largest rectangle of 1s has an area of 12.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

1. **Calculate Consecutive Heights:**
   Treat each row as the base of a histogram. We count consecutive `1`s ending at each cell.
   - Row 0: `[0, 1, 0, 1, 0]`
   - Row 1: `[0, 2, 0, 2, 1]`
   - Row 2: `[1, 3, 0, 3, 0]`

2. **Sort Heights Descending (Simulating Swaps):**
   For each row, sort the heights in descending order to group the tallest columns together.
   - Row 0 Sorted: `[1, 1, 0, 0, 0]` -> Max Area = `1*2 = 2`
   - Row 1 Sorted: `[2, 2, 1, 0, 0]` -> Max Area = `2*2 = 4`
   - Row 2 Sorted: `[3, 3, 1, 0, 0]` -> Max Area = `3*2 = 6`

3. **Final Result:** The maximum area across all evaluated rows is **6**.
</details>

---

## ⚠️ Constraints

* $1 \le n, m \le 10^3$
* $0 \le mat[i][j] \le 1$
* $mat.rows = n$
* $mat.cols = m$

---

## 💻 Solution Approach

Below is the optimized solution using dynamic programming (histogram technique) combined with counting sort for sorting row heights.

```cpp
// Intuition: To find the largest rectangle, we can treat each row as the base of a histogram. Since we can swap columns, we just need to know the heights of consecutive 1s in each column up to the current row, sort these heights in descending order, and calculate the maximum possible area.
// Approach:
// 1. Create a `height` matrix to store the count of consecutive 1s ending at each cell.
// 2. Iterate through the original matrix to populate the `height` matrix column by column.
// 3. For each row, count the frequencies of each height (using counting sort for efficiency).
// 4. Rearrange the heights in the current row in descending order.
// 5. For each rearranged height, calculate the area as `height * (current_index + 1)` and update the maximum area found so far.
// Time Complexity: O(n * (n + m)) - We process the grid to find heights in O(n*m). For each of the n rows, counting sort takes O(n+m) and calculating area takes O(m).
// Space Complexity: O(n * m) - Auxiliary space required for the 2D `height` matrix and O(n) for the `count` array.

class Solution {
  public:
    int maxArea(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> height(n, vector<int>(m, 0));

        // height[i][j] stores consecutive 1s ending at row i in column j.
        for (int j = 0; j < m; j++) {
            height[0][j] = mat[0][j];

            for (int i = 1; i < n; i++) {
                // Increment height only if current cell is 1
                if (mat[i][j] == 1) {
                    height[i][j] = height[i - 1][j] + 1;
                }
            }
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            vector<int> count(n + 1, 0);

            // Count frequency of each height.
            for (int j = 0; j < m; j++) {
                count[height[i][j]]++;
            }

            int col = 0;

            // Rearrange heights in decreasing order using counting sort.
            for (int h = n; h >= 0; h--) {
                while (count[h] > 0) {
                    height[i][col] = h;
                    col++;
                    count[h]--;
                }
            }

            // Calculate maximum area for this row.
            for (int j = 0; j < m; j++) {
                // Area is height * width (number of columns >= this height)
                ans = max(ans, height[i][j] * (j + 1));
            }
        }

        return ans;
    }
};

/*
 *
 * Dry Run
 * Input: mat = [[0, 1, 0], [1, 1, 1]]
 * n = 2, m = 3
 * 
 * Step 1: Height Matrix Generation
 * Row 0: height = [0, 1, 0]
 * Row 1: mat[1] is [1, 1, 1], adding to Row 0 -> height = [1, 2, 1]
 * 
 * Step 2: Processing Row 0
 * Heights: [0, 1, 0]
 * Sorted desc: [1, 0, 0]
 * Areas: 1*1=1, 0*2=0, 0*3=0 -> max for row = 1
 * 
 * Step 3: Processing Row 1
 * Heights: [1, 2, 1]
 * Sorted desc: [2, 1, 1]
 * Areas: 2*1=2, 1*2=2, 1*3=3 -> max for row = 3
 * 
 * Final ans: 3
 *
 */
```

---

## 🧠 Key Insights

* **Histogram Equivalence:** The problem can be reduced to the classic "Largest Rectangle in Histogram" problem. The ability to swap columns simply means we can sort the histogram bars at each step.
* **Counting Sort Optimization:** Since the maximum possible height is `n` (the number of rows), we can avoid the $O(M \log M)$ standard sort overhead by using Counting Sort, reducing the per-row sorting step to $O(N + M)$.
* **Prefix Sum Logic:** The `height` array dynamically builds up consecutive `1`s vertically, acting as a vertical prefix sum that resets upon hitting a `0`.

---

## 🔗 Further Exploration
* **Max Rectangle in Binary Matrix** (without column swaps)
* **Largest Rectangle in Histogram**
* **Maximal Square**

---

## 📚 References
* **GeeksforGeeks Problem:** [Largest Rectangle with Column Swaps](https://www.geeksforgeeks.org/problems/find-the-largest-rectangle-of-1s-with-swapping-of-columns-allowed0243/1)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`Arrays` `Matrix` `Dynamic Programming` `Sorting` `GeeksforGeeks`