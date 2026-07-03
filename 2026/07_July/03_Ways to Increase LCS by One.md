<div align="center">
    
# 🔠 Ways to Increase LCS by One

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-ways-to-increase-lcs-length-of-two-strings-by-one2236/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB84D?style=for-the-badge&logo=codeforces&logoColor=white)](#)
[![Accuracy: 52.12%](https://img.shields.io/badge/Accuracy-52.12%25-118DFF?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-00A98F?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given two strings `s1` and `s2` consisting of lowercase English letters of length `n1` and `n2` respectively, find the number of ways to insert **exactly one character** into string `s1` such that the length of the Longest Common Subsequence (LCS) of both strings increases by exactly 1.

---

## 💡 Examples

### Example 1
```text
Input: s1 = "abab", s2 = "abc"
Output: 3
Explanation: 
The LCS length of the given two strings is 2 (either "ab" or "ac"). 
There are 3 valid insertions in s1 which increase the LCS length to 3:
1. "abcab" -> insert 'c' at index 2 (LCS = 3)
2. "abacb" -> insert 'c' at index 3 (LCS = 3)
3. "ababc" -> insert 'c' at index 4 (LCS = 3)
```

### Example 2
```text
Input: s1 = "abcabc", s2 = "abcd"
Output: 4
Explanation: 
The LCS length of the given two strings is 3 ("abc"). 
There are 4 valid insertions in s1 which increase the LCS length to 4:
1. "abcdabc" -> insert 'd' at index 3 (LCS = 4)
2. "abcadcb" -> insert 'd' at index 4 (LCS = 4)
3. "abcabdc" -> insert 'd' at index 5 (LCS = 4)
4. "abcabcd" -> insert 'd' at index 6 (LCS = 4)
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<br>

Let's break down **Example 1**:
- Original strings: `s1 = "abab"`, `s2 = "abc"`
- Original LCS length = 2.
- We try inserting every character from `'a'` to `'z'` at every possible position from `0` to `4` in `s1`.
- When we insert `'c'` after the 2nd character (`"ab"`), the new string is `"abcab"`. The LCS with `"abc"` is now `"abc"` (Length = 3).
- When we insert `'c'` after the 3rd character (`"aba"`), the new string is `"abacb"`. The LCS is `"abc"` (Length = 3).
- When we insert `'c'` at the end (`"abab"`), the new string is `"ababc"`. The LCS is `"abc"` (Length = 3).
- For all other combinations of (index, character), the LCS either remains 2 or does not form a valid new subsequence matching the criteria. Thus, there are exactly 3 ways.

</details>

---

## ⚙️ Constraints

- `1 <= n1, n2 <= 100`
- Both strings consist of lowercase English letters only.

---

## 🛠️ Solution Approaches

### Optimized Prefix-Suffix DP Approach

The intuitive way to solve this is to realize that inserting a character into `s1` splits it into two parts: a prefix and a suffix. To determine the new LCS efficiently, we can precompute the LCS lengths for all prefixes and suffixes of `s1` against `s2`. 
By doing this, for any insertion of character `c` at position `i` matching with `s2[j]`, the new LCS is simply `(Prefix LCS up to i, j) + 1 + (Suffix LCS from i, j+1)`. We just need to check if this sum equals the original LCS length `L`.

```cpp
// Intuition: We need to find valid positions in s1 where inserting a character increases the LCS length. Precomputing prefix and suffix LCS lengths allows us to quickly evaluate the new LCS if we insert a specific character at a specific position without recalculating from scratch.
// Approach: 
// 1. Build a prefix LCS DP table `pref` where pref[i][j] is the LCS of s1[0..i-1] and s2[0..j-1].
// 2. Build a suffix LCS DP table `suff` where suff[i][j] is the LCS of s1[i..n-1] and s2[j..m-1].
// 3. The original LCS length is L = pref[n][m].
// 4. Iterate over every possible insertion index i in s1 (0 to n) and every possible character c ('a' to 'z').
// 5. Check if inserting c at i can form a new LCS of length L + 1 by matching c with some s2[j]. Condition: pref[i][j] + suff[i][j+1] == L.
// Time Complexity: O(n1 * n2) because we precompute two DP tables of size n1*n2, and then run a nested loop taking O(n1 * 26 * n2) steps which simplifies to O(n1 * n2).
// Space Complexity: O(n1 * n2) to store the prefix and suffix DP arrays.

class Solution {
public:
    int waysToIncreaseLCSBy1(string &s1, string &s2) {
        int n = s1.length();
        int m = s2.length();
        
        // DP tables for prefix and suffix LCS
        vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> suff(n + 1, vector<int>(m + 1, 0));
        
        // Build prefix LCS
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    pref[i][j] = 1 + pref[i - 1][j - 1]; // Match found
                } else {
                    pref[i][j] = max(pref[i - 1][j], pref[i][j - 1]); // No match
                }
            }
        }
        
        // Build suffix LCS
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (s1[i] == s2[j]) {
                    suff[i][j] = 1 + suff[i + 1][j + 1]; // Match found
                } else {
                    suff[i][j] = max(suff[i + 1][j], suff[i][j + 1]); // No match
                }
            }
        }
        
        int original_LCS = pref[n][m];
        int ways = 0;
        
        // Try inserting every character at every possible position
        for (int i = 0; i <= n; i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                bool can_increase = false;
                for (int j = 0; j < m; j++) {
                    // Check if inserted character matches s2[j] and forms L+1 LCS
                    if (s2[j] == c) {
                        if (pref[i][j] + suff[i][j + 1] == original_LCS) {
                            can_increase = true;
                            break;
                        }
                    }
                }
                if (can_increase) ways++;
            }
        }
        
        return ways;
    }
};

/*
*
* Dry Run
* s1 = "abab", s2 = "abc"
* n = 4, m = 3
* Prefix LCS (pref) built. pref[4][3] = 2. So, original_LCS = 2.
* Suffix LCS (suff) built.
* * Checking insertions (i from 0 to 4, c from 'a' to 'z'):
* For i = 2 (after "ab"), c = 'c':
* - Iterate j from 0 to 2. At j = 2, s2[2] == 'c'.
* - pref[2][2] (LCS of "ab" & "ab") = 2
* - suff[2][3] (LCS of "ab" & "") = 0
* - 2 + 0 == 2 (original_LCS). can_increase = true.
* - ways = 1
* For i = 3 (after "aba"), c = 'c':
* - At j = 2, s2[2] == 'c'.
* - pref[3][2] (LCS of "aba" & "ab") = 2
* - suff[3][3] (LCS of "b" & "") = 0
* - 2 + 0 == 2. can_increase = true.
* - ways = 2
* For i = 4 (after "abab"), c = 'c':
* - At j = 2, s2[2] == 'c'.
* - pref[4][2] (LCS of "abab" & "ab") = 2
* - suff[4][3] (LCS of "" & "") = 0
* - 2 + 0 == 2. can_increase = true.
* - ways = 3
* * Result ways = 3.
*
*/
```

---

## 🧠 Key Insights

- Standard Longest Common Subsequence requires $O(n^2)$ time. Trying to recalculate it for every single possible insertion point and every character would take $O(n^3 \times 26)$, which is too slow.
- The **Prefix-Suffix DP Trick** efficiently bypasses this constraint. By calculating `pref[i][j]` (LCS from the start) and `suff[i][j]` (LCS from the end), we can determine the exact length of the LCS in $O(1)$ time whenever we split the string at index `i`.
- The equation `pref[i][j] + suff[i][j + 1] == original_LCS` implies that if we wedge a matching character `c == s2[j]` perfectly between these prefixes and suffixes, it serves as the necessary bridge to push the total length to `original_LCS + 1`.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might want to look into:
1. **Longest Common Subsequence** - The base concept used here.
2. **Shortest Common Supersequence** - Expanding on LCS foundations.
3. **Edit Distance** - Finding the minimum operations to convert one string to another.

---

## 📑 References
- **Original Problem**: [GeeksforGeeks - Ways to Increase LCS by One](https://www.geeksforgeeks.org/problems/count-ways-to-increase-lcs-length-of-two-strings-by-one2236/1)

---

## 👤 Author
**Nilesh**
* [GitHub](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#Dynamic-Programming` `#LCS` `#Strings` `#GeeksforGeeks` `#Algorithms` 
