# 🔠 Count Matching Subsequences

<div align="center">
  
  [![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-matching-subsequences/1)
  [![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/)
  [![Accuracy](https://img.shields.io/badge/Accuracy-57.65%25-green?style=for-the-badge)](https://www.geeksforgeeks.org/)
  [![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/)
  [![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

<br>

> ⚠️ **Educational Use Only:**
> 
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem. 

---

## 📝 Problem Statement

Given two strings, `s1` and `s2`, count the number of subsequences of string `s1` equal to string `s2`.

Since the count can be very large, return the total count modulo **10^9 + 7**.

---

## 💡 Examples

**Example 1:**
```text
Input: s1 = "geeksforgeeks", s2 = "gks"
Output: 4
Explanation: We can pick characters from s1 as a subsequence from indices [0, 3, 4], [0, 3, 12], [0, 11, 12] and [8, 11, 12]. So total 4 subsequences of s1 that are equal to s2.
```

**Example 2:**
```text
Input: s1 = "problemoftheday", s2 = "geek"
Output: 0
Explanation: No subsequence of string s1 is equal to string s2.
```

<details>
<summary><b>📖 Example Breakdown (s1 = "geeksforgeeks", s2 = "gks")</b></summary>

1. We are looking for the sequence `g` -> `k` -> `s` in "geeksforgeeks".
2. We find the first `g` at index 0. Then `k` at index 3, and `s` at index 4 -> **Path 1** `[0, 3, 4]`
3. From the first `g` at index 0, we can also use `k` at index 3, and the *last* `s` at index 12 -> **Path 2** `[0, 3, 12]`
4. From the first `g` at index 0, we can also use the second `k` at index 11, and `s` at index 12 -> **Path 3** `[0, 11, 12]`
5. From the second `g` at index 8, we can use `k` at index 11, and `s` at index 12 -> **Path 4** `[8, 11, 12]`

Total ways = **4**.
</details>

---

## ⚠️ Constraints

> - `1 ≤ s1.size(), s2.size() ≤ 10^3`

---

## 🚀 Solution Approaches

### Optimized Dynamic Programming (2D Tabulation)
**Intuition**: The problem requires counting ways to form `s2` from `s1`. Since subsequences involve making choices (include or exclude a character) and we face overlapping subproblems (recomputing prefix matches), Dynamic Programming is the optimal approach.

```cpp
// Intuition: Since subsequences involve choice trees (include or exclude) with overlapping subproblems, DP is the best fit.
// Approach: Build a 2D DP table where dp[i][j] stores the number of ways s2[0..j-1] is a subsequence in s1[0..i-1]. If s1[i-1] == s2[j-1], add ways from both including and excluding the character. If not equal, we can only exclude.
// Time Complexity: O(n * m) where n and m are lengths of s1 and s2, as we traverse a 2D grid.
// Space Complexity: O(n * m) to store the DP table.

class Solution {
public:
    int countWays(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();
        int mod = 1e9 + 7;

        // dp[i][j] stores ways s2[0...j-1] matches subsequence in s1[0...i-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Base case: empty s2 can be formed in exactly 1 way
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 1;
        }

        // Fill DP table iteratively
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    // Match found: include or exclude s1's current character
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
                } else {
                    // No match: we must skip s1's current character
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // Result is ways to form full s2 from full s1
        return dp[n][m];
    }
};

/*
* Dry Run
* s1 = "ab", s2 = "a"
* n = 2, m = 1
* dp array initialized to 0, size 3x2
* Base case: dp[0][0]=1, dp[1][0]=1, dp[2][0]=1
* i = 1 ('a'), j = 1 ('a') -> match! dp[1][1] = dp[0][0] + dp[0][1] = 1 + 0 = 1
* i = 2 ('b'), j = 1 ('a') -> no match! dp[2][1] = dp[1][1] = 1
* Return dp[2][1] = 1
*/
```

---

## 🔑 Key Insights

- **Base Cases Matter:** An empty string `s2` can always be formed from any string `s1` in exactly 1 way (by deleting all characters of `s1`). This initializes the first column of the DP table to `1`.
- **String Matching Logic:** When `s1[i-1] == s2[j-1]`, you are not forced to match them. You can match them (`dp[i-1][j-1]`) AND you can choose to skip `s1[i-1]` entirely to find a different match earlier in the string (`dp[i-1][j]`).
- **Modulo Arithmetic:** The problem states the output can be large, so applying modulo `1e9+7` at every addition prevents integer overflow.

---

## 🔍 Further Exploration
Want to practice similar logic? Check out these related string and DP problems:
- [Distinct Subsequences (LeetCode 115)](https://leetcode.com/problems/distinct-subsequences/)
- [Longest Common Subsequence](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)
- [Edit Distance](https://www.geeksforgeeks.org/edit-distance-dp-5/)

---

## 🔗 References
- **Original Problem:** [GeeksforGeeks - Count Matching Subsequences](https://www.geeksforgeeks.org/problems/count-matching-subsequences/1)
- **Concepts:** Dynamic Programming on Strings, Sequence Counting

---

## 👨‍💻 Author
Built and maintained by **[imnilesh18](https://github.com/imnilesh18)**.  
Always open to connecting and collaborating on algorithmic problem solving!

---

## 🏷️ Tags
`Dynamic Programming` `Algorithms` `Strings` `Data Structures` `GeeksforGeeks` `C++`