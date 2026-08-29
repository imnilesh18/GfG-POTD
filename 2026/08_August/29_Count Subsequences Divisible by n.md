# 🧮 Count Subsequences Divisible by n

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-49.98%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a numeric string `s` containing only digits and an integer `n`, count the number of **non-empty subsequences** of `s` whose numeric value is divisible by `n`. 

Since the answer can be very large, return the answer modulo `10^9 + 7`.

---

## 💡 Examples

### Example 1:
```text
Input: s = "1234", n = 4
Output: 4
Explanation: The subsequences 4, 12, 24 and 124 are divisible by 4.
```

### Example 2:
```text
Input: s = "330", n = 6
Output: 4
Explanation: The subsequences 30, 30, 330 and 0 are divisible by 6.
```

<details>
<summary>📖 <b>Example Breakdown (s = "1234", n = 4)</b></summary>

Let's break down how the subsequences are formed and evaluated:
* The string has characters '1', '2', '3', '4'.
* Possible non-empty subsequences:
  * Length 1: 1, 2, 3, **4** 
  * Length 2: **12**, 13, 14, 23, **24**, 34
  * Length 3: 123, **124**, 134, 234
  * Length 4: 1234
* Among these, the values divisible by 4 are:
  1. `4` (4 % 4 == 0)
  2. `12` (12 % 4 == 0)
  3. `24` (24 % 4 == 0)
  4. `124` (124 % 4 == 0)
* Total count is exactly **4**.
</details>

---

## ⚠️ Constraints

> - `1 ≤ |s| * n ≤ 10^6`

---

## 🛠️ Solution Approach

### Dynamic Programming
The optimal way to solve this is by using Dynamic Programming. Instead of finding all actual subsequences (which takes $O(2^{|s|})$ time and is impossible for large strings), we can track the **count of remainders** modulo `n`. 

If we know how many subsequences leave a remainder `rem` so far, appending a new digit `d` to them shifts their remainder to `(rem * 10 + d) % n`.

#### Expected Complexities
* **Time Complexity:** $O(|s| \times n)$
* **Auxiliary Space:** $O(n)$

### 💻 Implementation (C++)

```cpp
// Intuition: Instead of generating all subsequences, we track the counts of subsequences based on their remainder modulo n. State dp[rem] represents the number of subsequences formed so far that leave a remainder 'rem'.
// Approach: 
// 1. Initialize a dp array of size n with 0s to store remainder frequencies.
// 2. Iterate through each character in the string and convert it to a digit.
// 3. Create a temporary array 'curr' copying current 'dp' to prevent using updated states within the same iteration.
// 4. Start a new subsequence containing only the current digit by incrementing curr[digit % n].
// 5. Append the current digit to all existing subsequences by calculating the new remainder: (rem * 10 + digit) % n.
// 6. Add the count of the old remainder dp[rem] to the new remainder's count in 'curr'.
// 7. Update 'dp' with 'curr' and continue. Finally, return dp[0].
// Time Complexity: O(|s| * n), where |s| is the string length. For each character, we iterate through n remainders.
// Space Complexity: O(n), since we use two arrays (dp and curr) of size n.

class Solution {
  public:
    int countSubsequences(string s, int n) {
        int MOD = 1e9 + 7;

        // dp[rem] stores the number of subsequences
        // having remainder rem modulo n.
        vector<int> dp(n, 0);

        // Process each digit of the string.
        for (char ch : s) {
            int digit = ch - '0';

            // Copy the previous DP state.
            vector<int> curr(dp);

            // Start a new subsequence with the current digit.
            curr[digit % n] = (curr[digit % n] + 1) % MOD;

            // Append the current digit to all existing subsequences.
            for (int rem = 0; rem < n; rem++) {
                int newRem = (rem * 10 + digit) % n;
                curr[newRem] = (curr[newRem] + dp[rem]) % MOD;
            }

            // Move to the next digit.
            dp = curr;
        }

        return dp[0];
    }
};

/*
* Dry Run
* 
* Input: s = "12", n = 4
* Initial: dp = [0, 0, 0, 0], MOD = 1e9+7
* 
* Iteration 1 (ch = '1'):
* digit = 1
* curr = dp = [0, 0, 0, 0]
* curr[1 % 4] += 1  => curr = [0, 1, 0, 0]
* rem loop: all dp[rem] are 0, so no additions.
* dp = curr = [0, 1, 0, 0]
* (Represents 1 subsequence leaving remainder 1: "1")
* 
* Iteration 2 (ch = '2'):
* digit = 2
* curr = dp = [0, 1, 0, 0]
* curr[2 % 4] += 1 => curr = [0, 1, 1, 0] 
* rem loop:
*   rem = 0: dp[0] = 0 (skip)
*   rem = 1: dp[1] = 1 -> newRem = (1 * 10 + 2) % 4 = 12 % 4 = 0
*            curr[0] += dp[1] => curr[0] = 0 + 1 = 1
*   rem = 2: dp[2] = 0 (skip)
*   rem = 3: dp[3] = 0 (skip)
* dp = curr = [1, 1, 1, 0]
* (Represents remainder 0: "12", remainder 1: "1", remainder 2: "2")
* 
* Return dp[0], which is 1 (the subsequence "12").
*/
```

---

## 🔍 Key Insights

* **Modulo Arithmetic Transition:** When appending a digit $d$ to an existing number $X$, the new number becomes $X \times 10 + d$. Thus, its remainder modulo $n$ seamlessly transitions to $(X\%n \times 10 + d) \% n$.
* **State Isolation:** We copy the DP array into `curr` at the start of each iteration. This prevents using a newly formed subsequence (from the current step) as a base to attach the same digit again in the same iteration.

---

## 🚀 Further Exploration
- **Related Problems:**
  - Check Divisibility by 8, 11, etc.
  - Number of subsets with sum divisible by `m`
- **Topics to Brush Up:**
  - 1D / 2D Dynamic Programming
  - Modular Arithmetic

---

## 🔗 References
* **GeeksforGeeks Problem:** [Count Subsequences Divisible by n](https://www.geeksforgeeks.org/problems/number-of-subsequences-in-a-string-divisible-by-n5947/1)
* **Topics:** `Dynamic Programming`, `Strings`, `Math`

---

## 👨‍💻 Author
**GitHub:** [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#DynamicProgramming` `#Strings` `#Math` `#ModuloArithmetic` `#GeeksForGeeks` `#CPP`