# 🟧 Sequences where Adjacent Divide

<div align="center">
  <img src="https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksForGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-69.24%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two positive integers `n` and `m`. Find the number of arrays of size `n` that can be formed such that:
1. Each element is in the range `[1, m]`.
2. All adjacent elements are such that one of them divides the another (i.e., element $A_i$ divides $A_{i+1}$ or $A_{i+1}$ divides $A_i$).

---

## 💡 Examples

```text
Input: n = 3, m = 3
Output: 17
Explanation: The possible arrays are [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 1], [1, 2, 2], [1, 3, 1], [1, 3, 3], [2, 1, 1], [2, 1, 2], [2, 1, 3], [2, 2, 1], [2, 2, 2], [3, 1, 1], [3, 1, 2], [3, 1, 3], [3, 3, 1] and [3, 3, 3].
```

```text
Input: n = 1, m = 10 
Output: 10
Explanation: The possible arrays are [1], [2], [3], [4], [5], [6], [7], [8], [9] and [10].
```

<details>
  <summary>📖 <b>Example Breakdown</b></summary>
  
  **Let's analyze `n = 2, m = 3`:**
  - We need to form arrays of size 2, picking numbers from `{1, 2, 3}`.
  - The valid pairs where one divides the other are: `(1,1), (1,2), (1,3), (2,1), (2,2), (3,1), (3,3)`.
  - Notice that in each pair, the divisibility rule holds true. 
  - There are exactly **7** valid arrays.
</details>

---

## 🚨 Constraints

> - `1 ≤ n ≤ 11`
> - `1 ≤ m ≤ 11`

---

## 🚀 Solution Approaches

### Dynamic Programming Approach

**Intuition:** 
We can build the arrays element by element. To figure out how many valid arrays of length `i` can end with a specific number `j`, we only need to look at the valid arrays of length `i-1` and check which ending numbers `k` can successfully transition to `j`. The transition is only valid if `j % k == 0` or `k % j == 0`.

```cpp
// Intuition: We can build the sequences incrementally. The number of valid sequences of length i ending in j depends entirely on the number of valid sequences of length i-1 ending in k, where j and k divide each other.
// Approach:
// 1. Create a 2D DP table `dp[i][j]` representing the number of valid sequences of length `i` ending with the number `j`.
// 2. Initialize the base case: for length 1, there is exactly 1 valid sequence for each number from 1 to m.
// 3. Iterate through lengths from 2 to n. For each length `i` and each ending number `j`, check all possible previous numbers `k` (from 1 to m).
// 4. If `k` divides `j` or `j` divides `k`, add `dp[i-1][k]` to `dp[i][j]`.
// 5. Finally, sum up all values in `dp[n][j]` for all `1 <= j <= m` to get the total count.
// Time Complexity: O(n * m^2) - Three nested loops (length `n`, current element `m`, previous element `m`). Given the small constraints (m <= 11), this is highly efficient.
// Space Complexity: O(n * m) - We use a 2D vector of size (n+1) x (m+1) to store the DP states.

class Solution {
  public:
    int count(int n, int m) {
        // dp[i][j] stores the number of valid arrays of size i ending with element j
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        // Base case: arrays of size 1 ending with j have exactly 1 valid combination
        for (int j = 1; j <= m; j++) {
            dp[1][j] = 1;
        }
        
        // Build the DP table for lengths 2 to n
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Check all possible preceding elements k
                for (int k = 1; k <= m; k++) {
                    // Check the divisibility condition for adjacent elements
                    if (j % k == 0 || k % j == 0) {
                        dp[i][j] += dp[i - 1][k];
                    }
                }
            }
        }
        
        // Sum up all valid arrays of size n
        int total_sequences = 0;
        for (int j = 1; j <= m; j++) {
            total_sequences += dp[n][j];
        }
        
        return total_sequences;
    }
};

/*
*
* Dry Run
* Input: n = 2, m = 3
*
* Initialization (i = 1):
* dp[1][1] = 1, dp[1][2] = 1, dp[1][3] = 1
* 
* Iteration 1 (i = 2):
* For j = 1:
*   k = 1: 1%1==0 (Yes) -> dp[2][1] += dp[1][1] (1)
*   k = 2: 2%1==0 (Yes) -> dp[2][1] += dp[1][2] (1)
*   k = 3: 3%1==0 (Yes) -> dp[2][1] += dp[1][3] (1)
*   dp[2][1] = 3
* 
* For j = 2:
*   k = 1: 2%1==0 (Yes) -> dp[2][2] += dp[1][1] (1)
*   k = 2: 2%2==0 (Yes) -> dp[2][2] += dp[1][2] (1)
*   k = 3: Neither divides -> skip
*   dp[2][2] = 2
* 
* For j = 3:
*   k = 1: 3%1==0 (Yes) -> dp[2][3] += dp[1][1] (1)
*   k = 2: Neither divides -> skip
*   k = 3: 3%3==0 (Yes) -> dp[2][3] += dp[1][3] (1)
*   dp[2][3] = 2
* 
* Total Sum: dp[2][1] + dp[2][2] + dp[2][3] = 3 + 2 + 2 = 7
* Output: 7
*
*/
```

---

## 🧠 Key Insights

- The problem forces us to track paths based purely on the state of the *last element added*. This makes it a textbook Dynamic Programming problem.
- Instead of checking all $M^N$ permutations (which would TLE on larger constraints), we group them into states `dp[length][last_element]`.
- The transition purely checks divisibility between $j$ and $k$, eliminating invalid adjacent pairs early in the sequence building process.

---

## 🔍 Further Exploration

- **Optimization:** For larger values of `M`, looping through all `k` from $1$ to `M` becomes $O(M^2)$. You can optimize the inner loop to $O(M \log M)$ by precomputing the multiples and factors of every number up to `M`, and then iterating only over valid transitions.
- **Related Patterns:** This logic maps heavily to path-counting on Directed Acyclic Graphs (DAGs) and state-machine dynamic programming scenarios.

---

## 📚 References

- [GeeksforGeeks Problem: Sequences where Adjacent Divide](https://www.geeksforgeeks.org/problems/count-in-array2138/1)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming`, `math`, `memoization`, `array`, `geeksforgeeks`