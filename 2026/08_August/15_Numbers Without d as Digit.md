# 🔢 Numbers Without d as Digit

<div align="center">
  
  ![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
  ![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
  ![Accuracy](https://img.shields.io/badge/Accuracy-40.35%25-green?style=for-the-badge)
  ![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
  ![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a number $n$, count the numbers from $1$ to $n$ that don’t contain digit $d$ in their decimal representation.

## ⚙️ Constraints

> - $0 \le n \le 10^9$
> - $0 \le d \le 9$
> - **Expected Time Complexity:** $\mathcal{O}(\log n)$
> - **Expected Auxiliary Space:** $\mathcal{O}(1)$

---

## 💡 Examples

**Example 1:**
```text
Input: n = 25, d = 3
Output: 22
Explanation: From 1 to 25, the numbers 3, 13, and 23 contain the digit 3, so the answer is 25 - 3 = 22.
```

**Example 2:**
```text
Input: n = 5, d = 3
Output: 4
Explanation: From 1 to 5, only 3 contains the digit 3, so the count of numbers without digit 3 is 4.
```

<details>
<summary>📖 <b>Example Breakdown (n = 25, d = 3)</b></summary>
<br>

1. We need to find all numbers between $1$ and $25$ that do not contain the digit `3`.
2. Total numbers initially considered: $25$.
3. The numbers in this range containing the digit `3` are: `3`, `13`, `23`.
4. The count of such numbers is $3$.
5. Subtracting these from the total gives us $25 - 3 = 22$.

</details>

---

## 🧠 Solution Approaches

### Digit Dynamic Programming (Optimized Approach)

**Intuition:** 
Instead of checking every number from $1$ to $n$ (which would take $\mathcal{O}(n)$ time and fail for $n=10^9$), we can build valid numbers digit-by-digit. By using Digit DP, we keep track of the number formed so far, ensuring it stays within the bounds of $n$ and never includes the restricted digit $d$. 

We maintain states based on two conditions:
1.  **Tight (`tight`)**: Are we bounded by the digits of $n$? (e.g., if $n=25$ and the first digit we placed is `2`, the second digit can only go up to `5`).
2.  **Started (`started`)**: Have we started forming a non-zero number? This is crucial for handling leading zeros, as leading zeros should not trigger the restriction if $d=0$.

```cpp
// Intuition: We can count the valid numbers by building them digit by digit using Dynamic Programming (Digit DP), skipping the forbidden digit 'd'.
// Approach: Convert 'n' to a string. Use a 2D DP array `dp[tight][started]` to track combinations from right to left. 'tight' indicates if we are bounded by n's prefix, and 'started' tracks if we've placed a non-zero digit (to handle leading zeros).
// Time Complexity: O(log n), where log n represents the number of digits in n. Processing each digit takes constant time.
// Space Complexity: O(1), since the DP table is of fixed size (2x2) regardless of n.
class Solution {
  public:
    int countWithout(int n, int d) {
         if (n <= 0)
             return 0;

         string s = to_string(n);
         int length = s.length();

         // dp[tight][started] = count of valid 
         // completions from the current position onward
         int dp[2][2];

         // base case: at the end, a number counts 
         // only if it actually started (non-empty)
         for (int tight = 0; tight < 2; tight++)
             for (int started = 0; started < 2; started++)
                 dp[tight][started] = started;

         // build the table backward from the last 
         // digit position to the first
         for (int pos = length - 1; pos >= 0; pos--) {
             int newDp[2][2] = {0}; // temporary DP state for current position

             for (int tight = 0; tight < 2; tight++) {
                 for (int started = 0; started < 2; started++) {
                     // determine max digit allowed based on tight constraint
                     int limit = tight ? (s[pos] - '0') : 9;
                     int total = 0;

                     // try every valid digit, skipping d once 
                     // the number has started
                     for (int digit = 0; digit <= limit; digit++) {
                         // check if placing this digit starts the number
                         int willStart = started || (digit != 0);

                         // skip the forbidden digit 'd'
                         if (willStart && digit == d)
                             continue;

                         // update tight constraint for the next position
                         int newTight = tight && (digit == limit);
                         total += dp[newTight][willStart]; // accumulate valid ways
                     }

                     newDp[tight][started] = total; // store results for current state
                 }
             }

             memcpy(dp, newDp, sizeof(dp)); // update main DP table for next iteration
         }

         return dp[1][0]; // result bounded by n and starting empty
     }
};

/*
* Dry Run
* Input: n = 5, d = 3
* String s = "5", length = 1
* Base Case: dp[tight][started] = started -> dp[0][0]=0, dp[0][1]=1, dp[1][0]=0, dp[1][1]=1
* Loop pos = 0 (Only one digit):
*   For tight=0, started=0: limit=9. digits=0,1,2,4,5,6,7,8,9 (9 valid). newDp[0][0] = 9
*   For tight=0, started=1: limit=9. digits=0,1,2,4,5,6,7,8,9 (9 valid). newDp[0][1] = 9
*   For tight=1, started=0: limit=5. valid digits=1,2,4,5 (0 skips as not started). newDp[1][0] = 4
*   For tight=1, started=1: limit=5. valid digits=0,1,2,4,5. newDp[1][1] = 5
* dp[] array updated with newDp.
* Result: dp[1][0] = 4
* Output: 4
*/
```

---

## 🔑 Key Insights

- **Digit DP Magic:** The core of the problem translates into effectively generating combinations. Instead of recursion with memoization, this solution uses an iterative DP approach built backwards from the least significant digit, optimizing recursive overhead.
- **Handling Zeroes:** The `started` state flag is an elegant way to differentiate between a structural leading zero (which shouldn't trigger the exclusion of $d$ if $d=0$) and a zero occurring within an actual number.
- **Space Efficiency:** Since calculating the DP states for position `i` only requires the results from position `i + 1`, we only need two $2 \times 2$ matrices, keeping auxiliary space at $\mathcal{O}(1)$.

---

## 🔎 Further Exploration

- **Related GFG Problem:** [Count Numbers with N Digits](#)
- **Concept:** Digit Dynamic Programming, Combinatorics.
- **Follow-up:** How would you modify the DP state if you had to omit *two* different digits instead of one?

---

## 🔗 References

- **Original GFG Problem:** [Numbers Without d as Digit](https://www.geeksforgeeks.org/problems/count-numbers2004/1)
- **Topics:** `Mathematical`

---

## 👤 Author

**Nilesh**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

`#dynamic-programming` `#digit-dp` `#mathematical` `#geeksforgeeks` `#c++`