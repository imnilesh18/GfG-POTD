# ⌨️ Special Keyboard

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/special-keyboard3018/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" /></a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-28.66%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
    <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" /></a>
</div>

<br>

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a special keyboard that contains only four keys:
- **Key 1**: Prints a single character **'A'** on the screen.
- **Key 2** (Ctrl + A): Selects all the characters currently present on the screen.
- **Key 3** (Ctrl + C): Copies the selected characters to a buffer.
- **Key 4** (Ctrl + V): Pastes the content of the buffer onto the screen, appending it to the existing text.

Initially, the screen is empty and the buffer is also empty. Determine the maximum number of **'A'** characters that can be displayed on the screen after performing exactly `n` key presses.

---

## 💡 Examples

**Example 1:**
```text
Input: n = 3
Output: 3
Explanation: With only 3 key presses, the best option is to press Key 1 each time. So, the screen shows "AAA" and the total number of A’s is 3.
```

**Example 2:**
```text
Input: n = 7
Output: 9
Explanation: An optimal sequence is: press Key 1 three times to get "AAA", then use Key 2 (select all) and Key 3 (copy), followed by Key 4 twice (paste). This results in "AAAAAAAAA", so the total number of A’s is 9.
```

<details>
<summary>📖 <b>Example Breakdown (n = 7)</b></summary>

1. **Press 1 (Key 1):** Screen: `A`, Buffer: `empty`
2. **Press 2 (Key 1):** Screen: `AA`, Buffer: `empty`
3. **Press 3 (Key 1):** Screen: `AAA`, Buffer: `empty`
4. **Press 4 (Key 2 - Ctrl+A):** Screen: `[AAA]`, Buffer: `empty`
5. **Press 5 (Key 3 - Ctrl+C):** Screen: `AAA`, Buffer: `AAA`
6. **Press 6 (Key 4 - Ctrl+V):** Screen: `AAAAAA`, Buffer: `AAA`
7. **Press 7 (Key 4 - Ctrl+V):** Screen: `AAAAAAAAA`, Buffer: `AAA`

Total `A`s on the screen = 9.

</details>

---

## ⚠️ Constraints

- `1 ≤ n ≤ 70`

---

## 🚀 Solution Approaches

### 1️⃣ Dynamic Programming (Top-Down with Memoization)

**Intuition:** For small values of `n` (up to 6), the maximum number of 'A's is simply the number of keystrokes `n` because we don't have enough keys to make copying beneficial. For larger `n`, we generate a base sequence of 'A's, then use `Ctrl-A`, `Ctrl-C`, and multiple `Ctrl-V`s to effectively multiply the text. Recursion helps us explore all possible points to start copying, and memoization guarantees we avoid recalculating the same subproblems.

```cpp
// Intuition: For small n (up to 6), the maximum 'A's equals the number of keystrokes. For larger n, we can generate a base sequence of 'A's, then use Ctrl-A, Ctrl-C, and multiple Ctrl-Vs to multiply them. Recursion helps explore all possible points to start copying, and memoization prevents recalculating the same subproblems.
// Approach: We use a helper recursive function. If remaining keystrokes are <= 6, we return n. Otherwise, we iterate a breakpoint 'j' from 1 to n-3. The 'j' represents keystrokes used to build the initial sequence. The remaining keystrokes are used for Select All (1), Copy (1), and Paste (n - j - 2). This multiplies our sequence by (n - j - 1). We store the max outcome for each 'n' in a dp array.
// Time Complexity: O(n^2) because there are n possible states and each state runs a loop of size up to n to find the optimal breakpoint.
// Space Complexity: O(n) to maintain the memoization array and the recursive call stack overhead.

class Solution {
  public:
    int solve(int n, vector<int>& dp) {
        // base case for 6 or fewer keystrokes
        if (n <= 6) {
            return n;
        }
        
        // return precomputed value if it exists
        if (dp[n] != -1) {
            return dp[n];
        }
        
        int maxAs = 0;
        
        // try all valid breakpoints for copying
        for (int j = 1; j <= n - 3; j++) {
            // multiply sequence built in j steps by remaining paste operations
            // (n - j) remaining keystrokes: 2 used for Ctrl-A, Ctrl-C. Remaining (n - j - 2) for Ctrl-V.
            // Original text (1x) + pasted text (n - j - 2) times = text * (n - j - 1).
            int currentAs = solve(j, dp) * (n - j - 1);
            maxAs = max(maxAs, currentAs);
        }
        
        // memoize and return the optimal result
        return dp[n] = maxAs;
    }

    int optimalKeys(int n) {
        // enhanced code here: initializing dp state array with -1
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};

/*
*
* Dry Run
*
* Input n is 7
* Initialize dp array of size 8 filled with -1
* Call solve with n equals 7
* * n is greater than 6 so we proceed to the loop
* Iterate j from 1 to 4 to find the best copy-paste breakpoint
* * j is 1
* solve for 1 returns 1
* multiplier is 7 minus 1 minus 1 equals 5
* currentAs is 1 times 5 equals 5
* maxAs updates to 5
* * j is 2
* solve for 2 returns 2
* multiplier is 7 minus 2 minus 1 equals 4
* currentAs is 2 times 4 equals 8
* maxAs updates to 8
* * j is 3
* solve for 3 returns 3
* multiplier is 7 minus 3 minus 1 equals 3
* currentAs is 3 times 3 equals 9
* maxAs updates to 9
* * j is 4
* solve for 4 returns 4
* multiplier is 7 minus 4 minus 1 equals 2
* currentAs is 4 times 2 equals 8
* maxAs remains 9
* * Loop finishes
* Store 9 at dp index 7
* Return 9
*
*/
```

---

## 🔍 Key Insights

- **Mathematical multiplier:** The sequence behaves strictly mathematically. If you spend `j` keystrokes to get `X` amount of 'A's, spending the remaining `(n - j)` keystrokes optimally means pressing `Ctrl-A` and `Ctrl-C` (which takes 2 keystrokes), leaving `(n - j - 2)` keystrokes to press `Ctrl-V`. Adding the original text with `(n - j - 2)` copies yields `(n - j - 1)` times the original length.
- **Why bound check at 6?** For `n ≤ 6`, the length sequence is exactly `n`. Multipliers only start overtaking linear typing at `n = 7`.

---

## 🔭 Further Exploration

- **Similar Problems:**
  - **4 Keys Keyboard** (LeetCode 651 - Premium)
  - Longest Common Subsequence
- **Advanced Concept:** Can we optimize the lookup loop to run in strictly **O(N)** time instead of **O(N²)** using an optimized DP array technique? Try converting this memoized version to pure bottom-up tabulation.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Special Keyboard](https://www.geeksforgeeks.org/problems/special-keyboard3018/1)
- **Concepts Used:** Dynamic Programming, Optimization over states, Recursion.

---

## 👤 Author

**Nilesh**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming` `recursion` `algorithms` `geeksforgeeks` `c++` `arrays`