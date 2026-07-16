# 🔢 Numbers with Given Digit Sum

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/count-of-n-digit-numbers-whose-sum-of-digits-equals-to-given-sum0733/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-26.33%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two integers `n` and `sum`, determine the number of `n`-digit positive integers whose digits add up to `sum`. 

An `n`-digit number **cannot have leading zeros**; that is, the first digit must be strictly between 1 and 9. 

If there exists no `n`-digit number with a sum of digits equal to the given `sum`, return `-1`.

---

## 💡 Examples

```text
Input: n = 2, sum = 2
Output: 2
Explanation: The valid 2-digit numbers whose digits sum to 2 are 11 and 20.

```

```text
Input: n = 1, sum = 10
Output: -1
Explanation: A single-digit number can only have a digit sum between 0 and 9.

```

```text
Input: n = 2, sum = 10
Output: 9
Explanation: The 2-digit numbers whose digits add up to 10 are: 19, 28, 37, 46, 55, 64, 73, 82, 91.

```

1. We need a 2-digit number (let's say `_ _`).
2. The first digit cannot be `0`. So it can only be `1` to `9`.
3. If the first digit is `1`, the remaining sum is `2 - 1 = 1`. The second digit must be `1`. (Number: **11**)
4. If the first digit is `2`, the remaining sum is `2 - 2 = 0`. The second digit must be `0`. (Number: **20**)
5. Any first digit `> 2` will exceed the target sum of 2.
6. Total valid numbers = 2.

---

## ⚙️ Constraints

* `1 ≤ n ≤ 9`
* `1 ≤ sum ≤ 81`

---

## 💻 Solution Approach

### 1. Dynamic Programming (Memoization)

```cpp
// Intuition: Building the number digit by digit reveals overlapping subproblems. A recursive DP approach can efficiently count valid paths by tracking remaining digits and the remaining sum needed.
// Approach: 
// 1. Process the first digit uniquely using a loop from 1 to 9 to prevent leading zeros.
// 2. For the remaining (n-1) digits, define a recursive function `solve` that tries all digits from 0 to 9.
// 3. Base cases: If no digits are left, return 1 if the remaining sum is exactly 0, else 0. If the sum becomes negative, return 0.
// 4. Memoize the overlapping states in a 2D `dp` table where `dp[n][sum]` stores the count of valid combinations.
// 5. If the final accumulated result is 0, return -1 as specified by the problem.
// Time Complexity: O(n * Sum) - We compute each state of our (n * Sum) DP matrix exactly once. Iterating through 10 digits per state is an O(1) constant factor.
// Space Complexity: O(n * Sum) - The 2D DP array requires O(10 * 82) space, and the recursion stack reaches a maximum depth of O(n).

class Solution {
private:
    long long dp[10][82]; // DP table to memoize states (max n = 9, max sum = 81)
    
    long long solve(int n, int sum) {
        // Base case: No digits left to place
        if (n == 0) {
            return sum == 0 ? 1 : 0; // Valid path if sum exactly reaches 0
        }
        
        // If sum becomes negative, it's impossible to reach the target
        if (sum < 0) return 0;
        
        // Return precalculated result if it already exists
        if (dp[n][sum] != -1) return dp[n][sum];
        
        long long ans = 0;
        
        // Try placing all possible digits from 0 to 9
        for (int i = 0; i <= 9; i++) {
            ans += solve(n - 1, sum - i);
        }
        
        // Memoize and return the answer
        return dp[n][sum] = ans;
    }
    
public:
    long long countWays(int n, int sum) {
        // Initialize DP table with -1
        memset(dp, -1, sizeof(dp));
        long long ans = 0;
        
        // First digit must be strictly between 1 and 9 (no leading zeros)
        for (int i = 1; i <= 9; i++) {
            if (sum - i >= 0) {
                ans += solve(n - 1, sum - i);
            }
        }
        
        // Return -1 if no valid numbers found, otherwise return the answer
        return ans == 0 ? -1 : ans;
    }
};

/*
*
* Dry Run
* Input: n = 2, sum = 2
* * Initialization: dp[][] = -1, ans = 0
* * Outer loop (first digit from 1 to 9):
* i = 1:
* sum - i = 2 - 1 = 1 (>= 0), calls solve(1, 1)
* solve(1, 1):
* Tries j from 0 to 9:
* j = 0 -> solve(0, 1) -> returns 0
* j = 1 -> solve(0, 0) -> returns 1
* j > 1 -> sum becomes < 0 -> returns 0
* Memoizes dp[1][1] = 1, returns 1
* ans = 0 + 1 = 1
* * i = 2:
* sum - i = 2 - 2 = 0 (>= 0), calls solve(1, 0)
* solve(1, 0):
* Tries j from 0 to 9:
* j = 0 -> solve(0, 0) -> returns 1
* j > 0 -> sum becomes < 0 -> returns 0
* Memoizes dp[1][0] = 1, returns 1
* ans = 1 + 1 = 2
* * i > 2:
* sum - i < 0, loop skips
* * Final ans = 2 (Representing numbers 11 and 20)
* Output: 2
*
*/

```

---

## 🧠 Key Insights

* **Leading Zeros Handled Naturally:** Treating the very first digit specially (looping `1` to `9` instead of `0` to `9`) elegantly bypasses all edge cases regarding leading zeros without needing complex conditions inside the DP.
* **State Reduction:** Since the maximum `n` is `9` and the maximum `sum` is `81` (`9 * 9`), the search space is incredibly tiny (`10 * 82` matrix). The DP approach efficiently overlaps matching subproblems preventing standard exponential Time Limit Exceeded (TLE) errors.

---

## 🔍 Further Exploration

* **Related Problem:** [Count all possible paths from top left to bottom right](https://www.geeksforgeeks.org/problems/count-all-possible-paths-from-top-left-to-bottom-right3011/1)
* **Concept Focus:** Variations of this problem often involve finding the lexicographically smallest or largest number matching the same conditions.

---

## 🔗 References

* **Original Problem:** [Numbers with Given Digit Sum (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/count-of-n-digit-numbers-whose-sum-of-digits-equals-to-given-sum0733/1)
* **Topic Reference:** [Digit DP Concepts](https://www.geeksforgeeks.org/digit-dp-introduction/)

---

## ✍️ Author

**Nilesh** [](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Dynamic Programming` `Algorithms` `Mathematical` `Digit DP` `Memoization` `GeeksForGeeks` `C++`