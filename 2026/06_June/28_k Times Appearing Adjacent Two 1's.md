# 🔢 k Times Appearing Adjacent Two 1's

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 60.55%](https://img.shields.io/badge/Accuracy-60.55%25-green?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two integers `n` and `k`, count the number of binary strings of length `n` where adjacent `1`s appear exactly `k` times.

Since the answer can be huge, return it modulo $10^9+7$.

---

## 💡 Examples

**Example 1:**
```text
Input: n = 3, k = 2
Output: 1
Explanation: Possible string is "111" where 2 adjacent 1s appear.
```

**Example 2:**
```text
Input: n = 5, k = 2
Output: 6
Explanation: Possible strings are "00111", "10111", "01110", "11100", "11101" and "11011".
```

<details>
<summary>📖 Example Breakdown (n = 5, k = 2)</summary>

Let's look at the valid binary strings of length 5 containing exactly 2 adjacent `1`s:
*   `00111` -> `11` appears twice (indexes 2-3 and 3-4)
*   `10111` -> `11` appears twice (indexes 2-3 and 3-4)
*   `01110` -> `11` appears twice (indexes 1-2 and 2-3)
*   `11100` -> `11` appears twice (indexes 0-1 and 1-2)
*   `11101` -> `11` appears twice (indexes 0-1 and 1-2)
*   `11011` -> `11` appears twice (indexes 0-1 and 3-4)

Total valid strings = **6**.
</details>

---

## ⚙️ Constraints

*   $1 \le n, k \le 10^3$

**Expected Complexities:**
*   **Time Complexity:** $O(n^2)$
*   **Auxiliary Space:** $O(n \times k)$

---

## 🧠 Solution Approach

Here is the choice-based Dynamic Programming approach mimicking the process of building the binary string bit by bit, tracking the total length, the number of adjacent `1`s formed, and the last bit placed.

```cpp
// Intuition: We can build the binary string bit by bit. At each step, we have the choice to append a '0' or a '1'. If we append a '1' and the previous bit was also '1', we increase our count of adjacent 1s. This optimal substructure and overlapping subproblems make it a perfect fit for 3D Dynamic Programming.
// Approach:
// 1. Initialize a 3D DP array dp[i][j][last_bit] to store the number of valid strings of length 'i', with 'j' adjacent 1s, ending in 'last_bit' (0 or 1).
// 2. Set the base cases for length 1: dp[1][0][0] = 1 (string "0") and dp[1][0][1] = 1 (string "1").
// 3. Iterate through lengths 'i' from 2 to n, and adjacent counts 'j' from 0 to k.
// 4. If we place a '0', the adjacent 1s count doesn't change: dp[i][j][0] = dp[i-1][j][0] + dp[i-1][j][1].
// 5. If we place a '1', it depends on the previous bit. If previous was '0', count doesn't change. If previous was '1', we formed a new pair, so count increases.
// 6. Return the sum of strings of length n with exactly k adjacent 1s, ending in either 0 or 1, modulo 10^9+7.
// Time Complexity: O(n * k), as we compute states for n lengths and k adjacent 1 counts, doing O(1) operations per state.
// Space Complexity: O(n * k), for storing the 3D DP table.

class Solution {
  public:
    int countStrings(int n, int k) {
        long long MOD = 1e9 + 7;
        
        // dp[length][adjacent_ones][last_bit]
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(k + 1, vector<long long>(2, 0)));
        
        // Base cases for strings of length 1
        dp[1][0][0] = 1; // String "0"
        dp[1][0][1] = 1; // String "1"
        
        // Fill the DP table
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                // Choice 1: Place a '0' at the current position
                // Appending '0' never creates adjacent '1's
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
                
                // Choice 2: Place a '1' at the current position
                // Subcase 2.1: Previous bit was '0', no new adjacent pair formed
                dp[i][j][1] = dp[i - 1][j][0];
                
                // Subcase 2.2: Previous bit was '1', new adjacent pair formed
                if (j > 0) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][1]) % MOD;
                }
            }
        }
        
        // Sum the answers for length n, exactly k pairs, ending in either 0 or 1
        return (dp[n][k][0] + dp[n][k][1]) % MOD;
    }
};

/*
*
* Dry Run
*
* Input: n = 3, k = 2
* MOD = 1000000007
*
* Initialization:
* dp[1][0][0] = 1 (String: "0")
* dp[1][0][1] = 1 (String: "1")
*
* Loop i = 2:
* j = 0:
*   dp[2][0][0] = dp[1][0][0] + dp[1][0][1] = 1 + 1 = 2 (Strings: "00", "10")
*   dp[2][0][1] = dp[1][0][0] = 1 (String: "01")
* j = 1:
*   dp[2][1][0] = dp[1][1][0] + dp[1][1][1] = 0 + 0 = 0
*   dp[2][1][1] = dp[1][1][0] + dp[1][0][1] = 0 + 1 = 1 (String: "11")
* j = 2:
*   dp[2][2][0] = 0
*   dp[2][2][1] = 0
*
* Loop i = 3:
* j = 0:
*   dp[3][0][0] = dp[2][0][0] + dp[2][0][1] = 2 + 1 = 3 (Strings: "000", "100", "010")
*   dp[3][0][1] = dp[2][0][0] = 2 (Strings: "001", "101")
* j = 1:
*   dp[3][1][0] = dp[2][1][0] + dp[2][1][1] = 0 + 1 = 1 (String: "110")
*   dp[3][1][1] = dp[2][1][0] + dp[2][0][1] = 0 + 1 = 1 (String: "011")
* j = 2:
*   dp[3][2][0] = dp[2][2][0] + dp[2][2][1] = 0 + 0 = 0
*   dp[3][2][1] = dp[2][2][0] + dp[2][1][1] = 0 + 1 = 1 (String: "111")
*
* Result:
* dp[3][2][0] + dp[3][2][1] = 0 + 1 = 1
* Output: 1
*/
```

---

## 🔑 Key Insights

* **Optimal Substructure:** A valid string of length `n` can be constructed seamlessly by examining valid strings of length `n-1` and making valid bit placements based solely on the last character.
* **State Space:** By keeping the state simple `(Current Length, Adjacent 1s Count, Last Bit Used)`, we map out all possibilities without generating permutations, turning an exponential string generation problem into a $O(n \times k)$ mathematical traversal.
* **Modulo Arithmetic:** Since combinations quickly scale out of standard 32-bit integer limits, maintaining modulo addition continuously prevents overflow and ensures calculation stability.

---

## 🚀 Further Exploration

*   [GeeksforGeeks - Count number of binary strings without consecutive 1’s](https://www.geeksforgeeks.org/count-number-binary-strings-without-consecutive-1s/)
*   [GeeksforGeeks - Longest Increasing Subsequence](https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/)

---

## 🔗 References

*   **Original Problem:** [k Times Appearing Adjacent Two 1's on GeeksforGeeks](https://www.geeksforgeeks.org/problems/count-binary-strings1944/1)

---

## 👤 Author

*   **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Dynamic Programming` • `Algorithms` • `Strings` • `GeeksforGeeks` • `C++`