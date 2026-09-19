# 🔀 Min Cost To Make Two Strings Identical

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/minimum-cost-to-make-two-strings-identical1107/1)
![Difficulty Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy 52.29%](https://img.shields.io/badge/Accuracy-52.29%25-green?style=for-the-badge)
![Points 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

<br>

⚠️ **Educational Use Only:**
<br>
This repository and its content are intended solely for educational purposes.
<br>
Solutions are provided for learning, practice, and reference only.
<br>
Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given two strings `s1` and `s2`, and two integers `costS1` and `costS2`, where `costS1` is the cost of deleting one character from `s1` and `costS2` is the cost of deleting one character from `s2`, find the minimum cost required to make the two strings identical[cite: 1].

You can delete any number of characters from either string, but the order of the remaining characters must be preserved[cite: 1].

---

## 💡 Examples

### Example 1
```text
Input: s1 = "abcd", s2 = "acdb", costS1 = 10, costS2 = 20
Output: 30
Explanation: Delete 'b' from both strings to obtain "acd". The total cost is 10 + 20 = 30.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>

1. **Initial Strings:** `s1` = "abcd", `s2` = "acdb".
2. **Goal:** Find the Longest Common Subsequence (LCS) to retain the maximum identical characters.
3. **LCS Found:** "acd" (length 3).
4. **Deletions Required:** 
   * From `s1`: Delete "b" (1 character). Cost = 1 × 10 = 10.
   * From `s2`: Delete "b" (1 character). Cost = 1 × 20 = 20.
5. **Total Cost:** 10 + 20 = 30.
</details>

### Example 2
```text
Input: s1 = "ef", s2 = "gh", costS1 = 10, costS2 = 20
Output: 60
Explanation: The two strings have no common characters, so delete all characters from both strings. The total cost is (2 × 10) + (2 × 20) = 60.
```

---

## ⚠️ Constraints

```text
1 ≤ s1.size(), s2.size() ≤ 1000
1 ≤ costS1, costS2 ≤ 10^5
```
*(Source: GeeksforGeeks[cite: 1])*

---

## 💻 Solution Approaches

### Optimized Dynamic Programming (Space-Optimized LCS)

**Intuition:** The problem can be reduced to finding the Longest Common Subsequence (LCS). Characters that are part of the LCS are kept, and all other characters must be deleted[cite: 1]. To minimize the deletion cost, we simply maximize the LCS and multiply the remaining lengths by their respective deletion costs.

```cpp
// Intuition: The optimal way to make strings identical via deletions is to reduce both strings to their Longest Common Subsequence (LCS). Characters outside the LCS are deleted.
// Approach: 
// 1. Calculate the length of the LCS of s1 and s2 using Dynamic Programming.
// 2. To optimize memory, swap strings if needed so s2 is always the shorter string.
// 3. Use two 1D arrays (`prev` and `curr`) instead of a full 2D DP table.
// 4. Calculate total cost: costS1 * (s1.length - LCS) + costS2 * (s2.length - LCS).
// Time Complexity: O(N * M) where N and M are the lengths of the given strings. We iterate through a nested loop over both strings.
// Space Complexity: O(min(N, M)) because we only store two rows of the DP table, dimensioned to the size of the shorter string.

class Solution {
  public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        // Ensure the shorter string determines the DP array size to minimize space.
        if (s1.length() < s2.length())
        {
            swap(s1, s2);
            swap(costS1, costS2);
        }

        int n = s1.length(), m = s2.length();
        // Allocate space for just two rows based on the shorter string's length
        vector<int> prev(m + 1), curr(m + 1);

        // Standard LCS DP logic building row by row
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // If characters match, add 1 to the diagonal result
                if (s1[i - 1] == s2[j - 1])
                    curr[j] = prev[j - 1] + 1;
                // If mismatch, take the maximum from top or left cells
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }

            // Reuse the current row as the previous row for the next iteration.
            swap(prev, curr);
        }

        // The length of the LCS is found at the end of the last computed row
        int lcsLength = prev[m];

        // Multiply remaining (non-LCS) characters by their respective deletion costs
        return (n - lcsLength) * costS1 + (m - lcsLength) * costS2;
    }
};

/*
*
* Dry Run
* Input: s1 = "abcd", s2 = "acdb", costS1 = 10, costS2 = 20
* Setup: lengths are equal (n=4, m=4). Arrays prev and curr allocated with size 5.
* i=1 ('a'): matches s2[1] ('a'). curr[1] = 1. Max propagates. curr becomes [0, 1, 1, 1, 1]. prev = curr.
* i=2 ('b'): matches s2[4] ('b'). curr[4] = 2. curr becomes [0, 1, 1, 1, 2]. prev = curr.
* i=3 ('c'): matches s2[2] ('c'). curr[2] = 2. curr becomes [0, 1, 2, 2, 2]. prev = curr.
* i=4 ('d'): matches s2[3] ('d'). curr[3] = 3. curr becomes [0, 1, 2, 3, 3]. prev = curr.
* Result: lcsLength = prev[4] = 3.
* Cost Calculation: (4 - 3) * 10 + (4 - 3) * 20 = 1 * 10 + 1 * 20 = 30.
* Output: 30
*
*/
```

---

## 🔍 Key Insights

* **Reduction to LCS:** The core realization is that the sequence of characters remaining after all optimal deletions *must* be a common subsequence. To strictly minimize deletions, we need the *longest* common subsequence[cite: 1].
* **Space Optimization Magic:** A standard 2D DP matrix for LCS takes $O(N \times M)$ space. However, calculating the `curr` row only ever requires data from the `curr` row and the `prev` row. By using two 1D arrays and guaranteeing the inner loop scales with the shorter string, memory usage drops dramatically to $O(\min(N, M))$[cite: 1].

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also like to explore:
* **Longest Common Subsequence (LCS)** - The foundational DP concept behind this problem.
* **Edit Distance** - A similar problem allowing replacements and insertions in addition to deletions.
* **Minimum Number of Deletions to Make a String Palindrome** - Another variation of the LCS algorithm.

---

## 📚 References

* Original Problem Statement: [GeeksforGeeks - Min Cost To Make Two Strings Identical](https://www.geeksforgeeks.org/problems/minimum-cost-to-make-two-strings-identical1107/1)[cite: 1]

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic_Programming-purple?style=for-the-badge) ![Strings](https://img.shields.io/badge/Strings-orange?style=for-the-badge) ![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)