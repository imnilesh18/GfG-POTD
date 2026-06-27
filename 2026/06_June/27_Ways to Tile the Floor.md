# 🧩 Ways to Tile the Floor

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/count-the-number-of-ways-to-tile-the-floor-of-size-n-x-m-using-1-x-m-size-tiles0509/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-39.12%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a floor of dimensions `n × m` and an unlimited supply of tiles of size `1 × m`, find the total number of ways to completely tile the floor.

Each tile can be placed in one of the following ways:
*   **Horizontally**, covering `1` row and `m` columns.
*   **Vertically**, covering `m` rows and `1` column.

Count all possible ways to cover the entire floor such that there are no overlaps and no uncovered cells. Since the number of possible tilings can be very large, return the answer modulo `10^9 + 7`.

> **Note:** `n` and `m` are positive integers, and `m ≥ 2`.

---

## 💡 Examples

### Example 1
```text
Input: n = 4, m = 4
Output: 2
Explanation: There are exactly two valid ways to tile the floor (all horizontally or all vertically). 
```

### Example 2
```text
Input: n = 2, m = 3
Output: 1
Explanation: Placing a tile vertically would require a height of 3, which exceeds the floor's height of 2. The only way to cover the entire floor is by placing 2 horizontally, one in each row, resulting in exactly one valid tiling.
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>
<br>

**Walkthrough for `n = 4, m = 4`:**
1. We are given a `4 x 4` floor and `1 x 4` tiles.
2. If we try to place the first tile **vertically**, it takes up 4 rows and 1 column. To complete the grid, the remaining 3 columns must also be filled vertically. That is **1 way**.
3. If we try to place the first tile **horizontally**, it takes up 1 row and 4 columns. The remaining 3 rows must be filled with 3 horizontal tiles. That is **1 way**.
4. Total ways = `1 + 1 = 2`.
</details>

---

## ⚠️ Constraints

> * `1 ≤ n ≤ 10^5`
> * `2 ≤ m ≤ 10^5`

---

## 💻 Solution Approach

### 1. Dynamic Programming (Optimized)

```cpp
// Intuition: The problem requires finding all valid ways to tile an n x m floor with 1 x m tiles. We can either place a tile horizontally (consuming 1 row) or vertically (consuming m rows). This overlapping subproblem structure makes it a classic Dynamic Programming problem.
// Approach: We use a 1D DP array where dp[i] stores the number of ways to tile a floor of size i x m. If i < m, we can only place tiles horizontally (1 way). If i == m, we can place them all horizontally or all vertically (2 ways). For i > m, the total ways are the sum of placing a tile horizontally (dp[i-1]) and vertically (dp[i-m]). We compute this up to n and take modulo 10^9 + 7 to prevent overflow.
// Time Complexity: O(n) because we iterate from 1 to n exactly once to fill the DP array.
// Space Complexity: O(n) because we use a DP array of size n + 1 to store the number of ways for each height.

class Solution {
  public:
    int countWays(int n, int m) {
        // Modulo constant to avoid large number overflow
        int MOD = 1e9 + 7;
        
        // DP array to store the number of ways for each floor height
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            if (i < m) {
                dp[i] = 1; // Only horizontal placement is possible
            } else if (i == m) {
                dp[i] = 2; // Both all-horizontal and all-vertical are possible
            } else {
                dp[i] = (dp[i - 1] + dp[i - m]) % MOD; // Sum of both placement strategies
            }
        }
        
        return dp[n];
    }
};

/*
Dry Run

Input: n = 4, m = 4
MOD = 1000000007
Create dp array of size 5: [0, 0, 0, 0, 0]

i = 1: i < m is true, dp[1] = 1
i = 2: i < m is true, dp[2] = 1
i = 3: i < m is true, dp[3] = 1
i = 4: i == m is true, dp[4] = 2

Loop completes.
Return dp[4] which is 2.
Output: 2
*/
```

---

## 🧠 Key Insights

* **Pattern Recognition:** This problem is an extension of the classic Fibonacci sequence or the "Tiling a 2xN board" problem. By generalizing the tile size to `1 x M`, the recurrence relation shifts from `F(N) = F(N-1) + F(N-2)` to `F(N) = F(N-1) + F(N-M)`.
* **Modulo Arithmetic:** Because permutations grow exponentially, tracking `(a + b) % MOD` at every single step ensures values never exceed typical integer data bounds during intermediate operations.

---

## 🔍 Further Exploration

* **Similar Problems on GeeksforGeeks:**
  * Ways To Tile A Floor (1x2 tiles)
  * Count number of ways to cover a distance
  * Friends Pairing Problem

---

## 🔗 References

* **GeeksforGeeks Problem Link:** [Ways to Tile the Floor](https://www.geeksforgeeks.org/problems/count-the-number-of-ways-to-tile-the-floor-of-size-n-x-m-using-1-x-m-size-tiles0509/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

<div align="left">
  <img src="https://img.shields.io/badge/Algorithm-Dynamic_Programming-blue?style=flat-square" alt="Dynamic Programming" />
  <img src="https://img.shields.io/badge/Data_Structure-Array-orange?style=flat-square" alt="Array" />
  <img src="https://img.shields.io/badge/Platform-GeeksforGeeks-green?style=flat-square" alt="GeeksforGeeks" />
</div>