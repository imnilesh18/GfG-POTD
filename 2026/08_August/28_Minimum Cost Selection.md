# 🥦 Minimum Cost Selection (Buying Vegetables)

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/buying-vegetables0016/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-44.66%25-green?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)]()

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

## 📝 Problem Statement

Given an `n × 3` matrix `mat[][]`, where each row represents the costs of three available choices at a shop. Your task is to select exactly one choice from each row such that the same choice is **not selected** in two adjacent rows. 

Return the minimum total cost required to make these selections.

### 🚧 Constraints

> - `1 <= n <= 10^5`
> - `mat[0].size() == 3`
> - `1 <= mat[i][j] <= 100`
> - `mat.rows == n`

---

## 💡 Examples

**Example 1:**
```text
Input: mat[][] = [[1, 50, 50], [50, 50, 50], [1, 50, 50]]
Output: 52
Explanation: One optimal selection is:
Row 1: Choice 1 (Cost = 1)
Row 2: Choice 2 (Cost = 50)
Row 3: Choice 1 (Cost = 1)
Total cost = 1 + 50 + 1 = 52.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>

1. **Row 0:** We can pick costs `1`, `50`, or `50`. Current running minimums: `[1, 50, 50]`.
2. **Row 1:** 
   - If we pick index 0 (cost 50), we must add the min from previous indices 1 or 2 (`min(50, 50) = 50`). Total = 100.
   - If we pick index 1 (cost 50), we must add the min from previous indices 0 or 2 (`min(1, 50) = 1`). Total = 51.
   - If we pick index 2 (cost 50), we must add the min from previous indices 0 or 1 (`min(1, 50) = 1`). Total = 51.
   - Running minimums updated to: `[100, 51, 51]`.
3. **Row 2:**
   - Pick index 0 (cost 1): add `min(51, 51) = 51`. Total = 52.
   - Pick index 1 (cost 50): add `min(100, 51) = 51`. Total = 101.
   - Pick index 2 (cost 50): add `min(100, 51) = 51`. Total = 101.
   - Running minimums updated to: `[52, 101, 101]`.
4. **Final Answer:** The minimum of the final row's totals is `52`.
</details>

**Example 2:**
```text
Input: mat[][] = [[1, 4, 1], [3, 2, 2], [3, 2, 3]]
Output: 5
Explanation: One optimal selection is:
Row 1: Choice 1 (Cost = 1)
Row 2: Choice 2 (Cost = 2)
Row 3: Choice 3 (Cost = 2)
Total cost = 1 + 2 + 2 = 5.
```

---

## 🛠️ Solution Approach

### Space-Optimized Dynamic Programming

```cpp
// Intuition: We must choose exactly one item per row without picking the same column in adjacent rows. The optimal cost for any choice in the current row only depends on the minimum valid costs computed in the immediately preceding row.
// Approach: 
// 1. Initialize three variables (prev0, prev1, prev2) to store the exact costs of the three choices from the first row.
// 2. Iterate through the remaining rows. For each of the three choices in the current row, calculate its total cost by adding its current matrix value to the minimum of the *other two* choices from the previous row.
// 3. Update the prev variables with the newly calculated current variables.
// 4. Return the minimum among the three final values.
// Time Complexity: O(n) - We iterate through the n rows of the matrix exactly once, performing constant O(1) operations per row.
// Space Complexity: O(1) - We only allocate a few integer variables (prev and curr states) rather than an entire DP table of size n x 3.

class Solution {
  public:
    int minCost(vector<vector<int>> &mat) {
        int n = mat.size();

        // Minimum cost when the first row selects each of the three choices
        int prev0 = mat[0][0];
        int prev1 = mat[0][1];
        int prev2 = mat[0][2];

        // Process remaining rows
        for (int i = 1; i < n; i++) {
            // Current row selects choice 0, add min of previous choices 1 and 2
            int curr0 = mat[i][0] + min(prev1, prev2);

            // Current row selects choice 1, add min of previous choices 0 and 2
            int curr1 = mat[i][1] + min(prev0, prev2);

            // Current row selects choice 2, add min of previous choices 0 and 1
            int curr2 = mat[i][2] + min(prev0, prev1);

            // Move current row values to previous row for the next iteration
            prev0 = curr0;
            prev1 = curr1;
            prev2 = curr2;
        }

        // The last row can end with any choice, return the absolute minimum
        return min(prev0, min(prev1, prev2));
    }
};

/*
Dry Run:
Input: mat = [[1, 50, 50], [50, 50, 50], [1, 50, 50]]

Initialization (Row 0):
prev0 = 1
prev1 = 50
prev2 = 50

Iteration 1 (Row 1):
curr0 = 50 + min(50, 50) = 100
curr1 = 50 + min(1, 50) = 51
curr2 = 50 + min(1, 50) = 51
prev0 = 100, prev1 = 51, prev2 = 51

Iteration 2 (Row 2):
curr0 = 1 + min(51, 51) = 52
curr1 = 50 + min(100, 51) = 101
curr2 = 50 + min(100, 51) = 101
prev0 = 52, prev1 = 101, prev2 = 101

Result:
min(52, min(101, 101)) = 52
*/
```

---

## 🔑 Key Insights

* **Optimal Substructure:** The problem strictly adheres to DP principles. To find the optimal cost at row `i`, you only need the optimal costs of row `i-1`. 
* **Space Optimization:** Because we only ever look exactly one row backward, a full `n x 3` DP table is unnecessary. We reduce space complexity to `O(1)` by keeping track of just 3 variables representing the prior row's states.

---

## 🔍 Further Exploration

* **Paint House Problem:** This is structurally identical to the classic "Paint House" DP problem (often found on LeetCode/GFG).
* **House Robber:** Another DP problem emphasizing picking adjacent versus non-adjacent elements.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Buying Vegetables / Minimum Cost Selection](https://www.geeksforgeeks.org/problems/buying-vegetables0016/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`Dynamic Programming` `Matrix` `Space Optimization` `GeeksforGeeks`