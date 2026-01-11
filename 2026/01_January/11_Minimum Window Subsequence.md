# 🟧 Minimum Window Subsequence

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-49.43%25-blue?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 🧐 Problem Statement

You are given two strings, `s1` and `s2`. Your task is to find the **smallest substring** in `s1` such that `s2` appears as a **subsequence** within that substring.

* The characters of `s2` must appear in the same sequence within the substring of `s1`.
* If there are multiple valid substrings of the same minimum length, return the one that appears **first** in `s1`.
* If no such substring exists, return an empty string.

**Note:** Both the strings contain only lowercase English letters.

### 📉 Constraints

* $1 \le s1.length \le 10^4$
* $1 \le s2.length \le 50$

---

## 📂 Examples

<div align="center">

| Example | Input | Output | Explanation |
| :---: | :--- | :--- | :--- |
| **1** | `s1 = "geeksforgeeks"` <br> `s2 = "eksrg"` | `"eksforg"` | "eksforg" satisfies conditions. `s2` is its subsequence and it is the smallest valid substring. |
| **2** | `s1 = "abcdebdde"` <br> `s2 = "bde"` | `"bcde"` | "bcde" and "bdde" are valid, but "bcde" occurs first. |
| **3** | `s1 = "ad"` <br> `s2 = "b"` | `""` | No substring exists. |

</div>

<details>
<summary><strong>📖 Example Breakdown (Example 1)</strong></summary>

* **s1**: `geeksforgeeks` (Indices 0-12)
* **s2**: `eksrg`
* We need `e` -> `k` -> `s` -> `r` -> `g`.
* Matching `g` at index 12 (last char):
    * Look backwards for `r`... found at 9.
    * Look backwards for `s`... found at 8.
    * Look backwards for `k`... found at 7.
    * Look backwards for `e`... found at 6.
* Start index: 6 (`e`), End index: 12 (`g`).
* Substring: `eksforg`. Length: 7.
* This is the minimal window.

</details>

---

## 💡 Solution Approach

### Dynamic Programming (Memoization)

The core challenge is finding the shortest window. A window is defined by a `start` and an `end` index. If we fix the `end` index (where the last character of `s2` matches `s1`), we want to find the **maximum possible `start` index** such that `s2` fits within `s1[start...end]`. Maximizing the start index minimizes the window length for a fixed end.

We iterate through `s1` to find potential `end` points. For each valid `end`, we use a recursive function (with memoization) to backtrack and find the best matching `start`.

#### Code Template

```cpp
// Intuition: To minimize the window length (end - start + 1), for every occurrence of the last character of s2 in s1 (fixed 'end'), we want to find the 'latest' possible starting position of s2's first character (maximized 'start').
// Approach: Iterate through s1. If s1[i] matches the last char of s2, treat 'i' as the window end. Use a recursive function 'solve' to find the max start index of s2[0...m-2] ending before 'i'. Memoize results to avoid re-computation.
// Time Complexity: O(N * M) where N is length of s1 and M is length of s2. Each state (i, j) is computed once.
// Space Complexity: O(N * M) for the memoization table + O(N) stack space for recursion.

class Solution {
    public:
    int memo[10001][51]; // Memoization table to store max start index

    // Recursive function to find the max start index of s2[0...j] in s1[0...i]
    int solve(int i, int j, string& s1, string& s2) {
        // Base case: If s1 is exhausted, match failed
        if (i < 0) return -1;
        
        // Base case: If strictly looking for the first char s2[0]
        if (j == 0) {
            // Check previous positions for s2[0]
            int prev = solve(i - 1, j, s1, s2);
            // If current char matches s2[0], it's a candidate for start index
            if (s1[i] == s2[0]) {
                return max(i, prev); // Prefer current i (max index) for shortest window
            }
            return prev;
        }

        // Return memoized result if already computed
        if (memo[i][j] != -2) return memo[i][j];

        // Option 1: Ignore s1[i] and look for s2[0...j] in s1[0...i-1]
        int res = solve(i - 1, j, s1, s2);

        // Option 2: If characters match, try to match s2[j] at s1[i]
        if (s1[i] == s2[j]) {
            // Find where the previous part of s2 (0...j-1) ended
            int prevMatch = solve(i - 1, j - 1, s1, s2);
            if (prevMatch != -1) {
                res = max(res, prevMatch); // Maximize start index
            }
        }

        return memo[i][j] = res;
    }

    string minWindow(string& s1, string& s2) {
        int n = s1.length();
        int m = s2.length();
        
        // Initialize memo table with -2 (since -1 is a valid return for "not found")
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                memo[i][j] = -2;
            }
        }

        string minStr = "";
        int minLen = 1e9; // Initialize with a large value

        // Iterate through s1 to find potential end points for s2
        for (int i = 0; i < n; i++) {
            // We only care if the current char completes s2 (matches last char)
            if (s1[i] == s2[m - 1]) {
                int start = -1;
                
                if (m == 1) {
                    start = i; // Special case for single char s2
                } else {
                    // Find the best start index for the prefix s2[0...m-2] ending before i
                    start = solve(i - 1, m - 2, s1, s2);
                }

                // If a valid start index was found
                if (start != -1) {
                    int currentLen = i - start + 1;
                    // Update result if we found a smaller window
                    if (currentLen < minLen) {
                        minLen = currentLen;
                        minStr = s1.substr(start, currentLen);
                    }
                }
            }
        }

        return minStr;
    }
};

/*
*
* Dry Run
* Input: s1 = "abcdebdde", s2 = "bde"
* n = 9, m = 3. Last char of s2 is 'e'.
*
* 1. Loop i from 0 to 8:
* - i=0 ('a') != 'e'
* - ...
* - i=4 ('e') == 'e' (Possible End)
* Call solve(3, 1, s1, s2) -> Find max start of "bd" in "abcd".
* solve returns 1 (index of 'b' at s1[1]).
* Window: s1[1...4] = "bcde". Length = 4. minLen = 4. minStr = "bcde".
*
* - i=5 ('b') != 'e'
* - ...
* - i=8 ('e') == 'e' (Possible End)
* Call solve(7, 1, s1, s2) -> Find max start of "bd" in "abcdebd".
* solve returns 5 (index of 'b' at s1[5]).
* Window: s1[5...8] = "bdde". Length = 4.
* currentLen (4) is NOT < minLen (4). Keep first occurrence.
*
* Final Output: "bcde"
*/

```

---

## 🗝️ Key Insights

1. **Fixing the End Point:** By iterating through `s1` and checking if `s1[i]` matches the *last* character of `s2`, we efficiently identify all potential window endings.
2. **Maximizing Start Index:** To minimize window length (), we need the `Start` index to be as large as possible. The `solve` function is designed specifically to find this "latest possible start".
3. **Memoization:** Since `solve(i, j)` might be called multiple times for the same indices (especially if characters repeat), caching the result in `memo` reduces complexity from exponential to polynomial.

---

## 🚀 Further Exploration

* **Follow-up:** What if `s1` is extremely large (stream of characters)?
* **Related Problems:**
* [Minimum Window Substring (LeetCode 76)](https://leetcode.com/problems/minimum-window-substring/) - Similar but order doesn't matter (bag of chars).
* [Longest Common Subsequence](https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/)



---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note:** This repository is for educational purposes only.
