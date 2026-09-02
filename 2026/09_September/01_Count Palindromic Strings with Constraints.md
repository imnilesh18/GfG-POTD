# 🧮 Count Palindromic Strings with Constraints

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-51.99%25-green?style=for-the-badge" alt="Accuracy 51.99%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given two integers `n` and `k`, consider an alphabet consisting of the first `k` lowercase English letters. Find the number of palindromic strings whose length is less than or equal to `n`, such that:
1. Every character in the string belongs to the given alphabet.
2. No character appears more than twice in the string.

*Note: Since the answer can be very large, return it modulo `10^9+7`.*

---

## 💡 Examples

### Example 1
```text
Input: n = 3, k = 2
Output: 6
Explanation: The possible strings are: "a", "b", "aa", "bb", "aba", "bab".
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Let's look at all valid palindromes of length ≤ 3 using letters `{'a', 'b'}`:
*   **Length 1:** "a", "b" (2 strings)
*   **Length 2:** "aa", "bb" (2 strings)
*   **Length 3:** "aba", "bab" (2 strings) -> Note that "aaa" is invalid because 'a' appears 3 times.

**Total:** 2 + 2 + 2 = 6 palindromes.
</details>

### Example 2
```text
Input: n = 4, k = 3
Output: 18
Explanation: The possible strings are:
"a", "b", "c", "aa", "bb", "cc", "aba", "aca", "bab", "bcb", "cac", "cbc", "abba", "acca", "baab", "bccb", "caac", "cbbc".
```

---

## ⚠️ Constraints

```text
• 1 ≤ k ≤ 26
• 1 ≤ n ≤ 52
• n ≤ 2 * k
```

---

## 🚀 Solution Approach

### Combinatorial DP (Optimized)

```cpp
// Intuition: Since characters can appear at most twice, a valid palindrome must be formed by selecting distinct characters for its first half. The middle character (for odd lengths) must also be distinct from the mirrored characters. This reduces the problem to counting permutations of `k` items.
// Approach: 
// 1. Precompute a Permutation (nPr) table using DP where nPr[i][j] = nPr[i-1][j] + j * nPr[i-1][j-1].
// 2. Iterate half-lengths `i` from 1 to `n/2`. Each half-length `i` contributes to both an even palindrome of length 2i and an odd palindrome of length 2i-1. Thus, we add nPr[k][i] to our result and multiply the sum by 2.
// 3. If `n` is odd, we also add the permutations for the exact odd length `n` which requires `n/2 + 1` characters.
// 4. Apply modulo 10^9+7 at each addition/multiplication.
// Time Complexity: O(k^2) to build a DP table of size (k+1) x (k+1) to compute all required permutations.
// Space Complexity: O(k^2) to store the 2D array for permutations.
class Solution {
  public:
    int palindromicStrings(int n, int k) {
         int MOD = 1e9 + 7;

         long long nPr[k + 1][k + 1];

         // Initialize the permutation table with zeros
         memset(nPr, 0, sizeof(nPr));

         // Build the nPr table dynamically
         for (int i = 0; i <= k; i++) {
             for (int j = 0; j <= i; j++) {
                 // Base case: 0 items chosen from i items is exactly 1 way
                 if (j == 0)
                     nPr[i][j] = 1;

                 // Calculate using previously stored values: exclude or include in j positions
                 else
                     nPr[i][j] = (nPr[i - 1][j] % MOD + (j * nPr[i - 1][j - 1]) % MOD) % MOD;
             }
         }

         long long res = 0;

         // Add ways for both odd (2i-1) and even (2i) length palindromes
         for (int i = 1; i <= n / 2; i++)
             res = (res + nPr[k][i]) % MOD;

         // Multiply by 2 since each half-length 'i' provides 1 odd and 1 even configuration
         res = (res * 2) % MOD;

         // Add the extra odd length permutations when the maximum length 'n' is odd
         if (n & 1)
             res = (res + nPr[k][n / 2 + 1]) % MOD;

         return (int)res;
     }
};

/*
Dry Run
Input: n = 3, k = 2
MOD = 1000000007

Table nPr initialization (size 3x3):
i=0: nPr[0][0]=1
i=1: nPr[1][0]=1, nPr[1][1]=1
i=2: nPr[2][0]=1, nPr[2][1]=2, nPr[2][2]=2

Loop for i=1 to n/2 (3/2 = 1):
i=1: res = (0 + nPr[2][1]) = (0 + 2) = 2

res = (res * 2) % MOD
res = (2 * 2) % 1000000007 = 4

Check if n is odd:
3 is odd (3 & 1 is true).
res = res + nPr[k][n / 2 + 1]
res = 4 + nPr[2][1 + 1]
res = 4 + nPr[2][2]
res = 4 + 2 = 6

Output: 6
*/
```

---

## 🧠 Key Insights

* **Constraint Mapping:** The condition "no character appears more than twice" essentially forces every character in the first half of the palindrome to be completely unique. If any character duplicated in the first half, it would mirror to the second half and appear 4 times.
* **Permutation Parity:** A half-length of $i$ unique characters gives you enough building blocks to create exactly one palindrome of length $2i$ (even) and one palindrome of length $2i - 1$ (odd). This beautiful symmetry allows us to calculate `nPr[k][i]` once, sum it up, and simply multiply by 2 for the paired lengths.
* **Math Optimization:** Pre-computing the permutation matrix $^nP_r$ in an $O(k^2)$ tabular manner avoids expensive factorial and modular inverse operations, keeping everything lightning fast given the tiny $k \le 26$ constraint.

---

## 🔍 Further Exploration

* Explore similar problems dealing with combinatorial strings and constraints.
* Practice optimizing combinatorial logic using modular inverses for larger constraints (e.g., $k \ge 10^5$).
* Related concepts: **Pascal's Triangle**, **Stars and Bars**, **Modular Arithmetic**.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Count Palindromic Strings with Constraints](https://www.geeksforgeeks.org/problems/number-of-palindromic-strings2706/1)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Strings` `Dynamic Programming` `Mathematics` `Combinatorial` `GeeksforGeeks`