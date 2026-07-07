<div align="center">
  
# 🟧 Largest Unblocked Submatrix

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/largest-unblocked-submatrix/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-52.99%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statements and test cases are based on the GeeksforGeeks platform.

</div>

---

## 📝 Problem Statement

You are given integers `n` and `m`, and an array `arr[][]` of size `k`, where `arr[i] = [r, c]` represents a blocked cell in an `n × m` grid. 

Each blocked cell blocks its **entire row and column**. Your task is to find the largest continuous unblocked area in the grid.

> **Note:** No two blocked cells are in the same row or the same column.

---

## 💡 Examples

### Example 1
```text
Input: n = 5, m = 5, k = 2, arr[][] = [[2, 1], [5, 3]]
Output: 4
```

<details>
<summary>📖 Example Breakdown</summary>

- Enemies block rows **2 and 5** and columns **1 and 3**. 
- Between rows 2 and 5, rows **3 and 4** remain unblocked, giving a maximum row segment of length `2`. 
- Between columns 3 and the right boundary, columns **4 and 5** remain unblocked, giving a maximum column segment of length `2`. 
- Hence, the largest continuous unblocked rectangle has an area of `2 × 2 = 4`.
</details>

### Example 2
```text
Input: n = 2, m = 2, k = 1, arr[][] = [[2, 2]]
Output: 1
Explanation: Since only the (1,1) cell is free from the enemy, the maximum unblocked area is 1.
```

---

## 🛑 Constraints

> - `1 ≤ n, m ≤ 10^4`
> - `0 ≤ k ≤ min(n, m)`
> - `1 ≤ r ≤ n`
> - `1 ≤ c ≤ m`

---

## 🧠 Solution Approach

### **Optimized Approach (Sorting Gaps)**

**Intuition:**
Since a blocked cell blocks its *entire* row and column, the row blockages and column blockages are completely independent of each other. The grid is essentially sliced into a series of unblocked horizontal and vertical strips. To maximize the unblocked area, we simply need to find the widest unblocked horizontal strip (maximum row gap) and multiply it by the widest unblocked vertical strip (maximum column gap).

**Approach:**
1. Extract all the blocked rows and blocked columns from the given array into two separate lists.
2. Sort both lists to simulate scanning the grid sequentially from top to bottom (and left to right).
3. Calculate the maximum gap between adjacent blocked rows. Don't forget to account for the grid boundaries: the gap from the top border (`1`) to the first blocked row, and from the last blocked row to the bottom border (`n`).
4. Repeat the exact same gap-finding process for the columns.
5. The maximum area is the product of the maximum row gap and the maximum column gap.

---

## 💻 Code Implementation

```cpp
// Intuition: The problem asks for the largest unblocked rectangle. Since a blocked cell blocks its entire row and column, the rows and columns are completely independent. Thus, the maximum unblocked area is just the product of the maximum contiguous unblocked row segment and the maximum contiguous unblocked column segment.
// Approach:
// 1. Separate the blocked row indices and column indices into two different arrays.
// 2. Sort both arrays to find the gaps between consecutive blocked lines.
// 3. Find the maximum gap between consecutive blocked rows. Also consider the gap from the start (1) to the first block, and the last block to the end (n).
// 4. Repeat the same gap-finding process for columns.
// 5. Multiply the maximum row gap and the maximum column gap to get the answer.
// Time Complexity: O(k log k), where k is the number of blocked cells. The dominant operation is sorting the row and column arrays.
// Space Complexity: O(k), because we store the row and column indices in separate vectors of size k.

class Solution {
  public:
    int largestArea(int n, int m, int k, vector<vector<int>> &arr) {
        // Edge case: if there are no blocked cells, the whole grid is unblocked
        if (k == 0) return n * m;

        // Arrays to store the blocked rows and columns independently
        vector<int> rows;
        vector<int> cols;

        for(int i = 0; i < k; i++) {
            rows.push_back(arr[i][0]);
            cols.push_back(arr[i][1]);
        }

        // Sort to process the blocked lines sequentially
        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());

        // Initialize max gaps by checking the start boundary to the first block
        // Grid is 1-indexed, so unblocked length before first block is rows[0] - 1
        int max_row = rows[0] - 1; 
        int max_col = cols[0] - 1; 

        // Find the maximum gap between consecutive blocked lines
        for(int i = 1; i < k; i++) {
            max_row = max(max_row, rows[i] - rows[i-1] - 1);
            max_col = max(max_col, cols[i] - cols[i-1] - 1);
        }

        // Finally, check the gap from the last block to the end boundary
        max_row = max(max_row, n - rows[k-1]);
        max_col = max(max_col, m - cols[k-1]);

        // The largest area is the product of the maximum row and column segments
        return max_row * max_col;
    }
};

/*
*
* Dry Run
* * Input: n = 2, m = 2, k = 1, arr = [[2, 2]]
* * 1. Initialize empty arrays: rows = [], cols = []
* 2. Loop through arr:
* - arr[0] = [2, 2] -> rows = [2], cols = [2]
* 3. Sort arrays: rows = [2], cols = [2]
* 4. Initial max gaps from start boundary:
* - max_row = rows[0] - 1 = 2 - 1 = 1
* - max_col = cols[0] - 1 = 2 - 1 = 1
* 5. Loop through gaps: (skips, since k = 1)
* 6. Check end boundaries:
* - max_row = max(1, n - rows[0]) = max(1, 2 - 2) = max(1, 0) = 1
* - max_col = max(1, m - cols[0]) = max(1, 2 - 2) = max(1, 0) = 1
* 7. Result = max_row * max_col = 1 * 1 = 1
* * Output: 1
*
*/
```

---

## 🔍 Key Insights
- **Independence:** The main takeaway is recognizing that the $X$ and $Y$ axes do not interfere with each other when calculating dimensions. Slicing rows doesn't change column widths, and slicing columns doesn't change row heights.
- **Edge Boundaries:** Often in gap-finding problems, the biggest mistakes occur by forgetting the edges (from the start boundary to the first element, and the last element to the end boundary).

---

## 🚀 Further Exploration
If you enjoyed this problem, you might also want to try:
- **Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts** (Similar concept on LeetCode)
- **Largest Rectangle in Histogram** (GFG/LeetCode)
- **Maximal Rectangle in a 2D Matrix** (GFG/LeetCode)

---

## 🔗 References
- **Original Problem:** [Largest Unblocked Submatrix on GeeksforGeeks](https://www.geeksforgeeks.org/problems/largest-unblocked-submatrix/1)

---

## 👨‍💻 Author
**GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`Greedy` `Sorting` `Algorithms` `Math` `GeeksforGeeks`
