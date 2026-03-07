# 🎲 Dice throw

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-36.52%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:** > This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given `n` dice, each with `m` faces (numbered from `1` to `m`), find the total number of ways to get a exact sum `x`. The sum `x` is the summation of the values on the top face of each die when all `n` dice are thrown.

---

## 💡 Examples

### Example 1
```text
Input: m = 6, n = 3, x = 12
Output: 25
Explanation: There are 25 total ways to get the Sum 12 using 3 dices with faces from 1 to 6.
```

### Example 2
```text
Input: m = 2, n = 3, x = 6
Output: 1
Explanation: There is only 1 way to get the Sum 6 using 3 dices with faces from 1 to 2. All the dices will have to land on 2. (i.e., 2 + 2 + 2 = 6).
```

<details>
<summary>📖 <b>Example Breakdown (m=6, n=2, x=7)</b></summary>

Imagine rolling two standard Ludo dice (`m = 6`). You want a sum of `7`.
- Roll 1st Die: If it lands on `1`, the 2nd die must land on `6` (1 + 6 = 7). ✅
- Roll 1st Die: If it lands on `2`, the 2nd die must land on `5` (2 + 5 = 7). ✅
- Roll 1st Die: If it lands on `3`, the 2nd die must land on `4` (3 + 4 = 7). ✅
- Roll 1st Die: If it lands on `4`, the 2nd die must land on `3` (4 + 3 = 7). ✅
- Roll 1st Die: If it lands on `5`, the 2nd die must land on `2` (5 + 2 = 7). ✅
- Roll 1st Die: If it lands on `6`, the 2nd die must land on `1` (6 + 1 = 7). ✅

Total valid combinations = 6. 
This is the core intuition! We simulate these rolls recursively.
</details>

---

## ⚠️ Constraints

- `1 <= m, n, x <= 50`

---

## 🚀 Solution Approaches

### Top-Down Dynamic Programming (Memoization)

**Intuition:** Think of this like throwing standard dice. For the first throw, you have `m` different choices. Once you pick a value, you are left with `n - 1` dice and a reduced target sum `x - faceValue`. Since multiple combinations can lead to the exact same remaining dice and remaining sum (overlapping subproblems), recursively exploring all paths leads to Time Limit Exceeded (TLE). We can solve this efficiently by storing our calculated states using a 2D memoization array `dp[n][x]`.

```cpp
// Intuition: We need to find all valid combinations of 'n' dice rolls that sum to 'x'. This forms a recursive tree of choices (1 to m). Because many branches share the same remaining dice 'n' and remaining target 'x', we use Dynamic Programming (Memoization) to cache and reuse these subproblem results.
// Approach: Build a recursive function `solve(m, n, x)`. Try every face value from 1 to m. For each choice, subtract the face value from 'x' and decrement 'n'. Use base cases: if target < 0 return 0, if n==0 and target==0 return 1. Cache the sum of valid paths in `dp[n][x]`.
// Time Complexity: O(m * n * x) - We calculate the answer for 'n * x' unique states. Calculating each state takes an O(m) loop.
// Space Complexity: O(n * x) - We use a 2D DP array of size 51x51 to store results, plus the O(n) recursive stack depth.

class Solution {
public:

    int dp[51][51]; // Memoization table to store results of subproblems

    // Recursive function to calculate the number of ways to get sum 'x' with 'n' dice and 'm' faces
    int solve(int m, int n, int x) {
        if (x < 0) {
            return 0; // If the remaining sum is negative, no valid combination
        }

        if (dp[n][x] != -1) {
            return dp[n][x]; // Return previously computed result
        }

        if (n == 0 && x == 0) {
            return 1; // Base case: exact match of dice used and sum required
        }

        if (n == 0) {
            return 0; // No dice left but sum not reached
        }

        int result = 0;
        for (int faceVal = 1; faceVal <= m; faceVal++) {
            // Try all face values from 1 to m and recurse
            result += solve(m, n - 1, x - faceVal);
        }

        return dp[n][x] = result; // Store result in dp table
    }
    
    int noOfWays(int m, int n, int x) {
        memset(dp, -1, sizeof(dp)); // Initialize dp table with -1
        return solve(m, n, x);      // Start the recursive computation
    }
};

/*
 *
 * Dry Run
 * Input: m = 6, n = 2, x = 7
 * Goal: Find the number of ways to get sum 7 using 2 dice, each with 6 faces.
 *
 * solve(6, 2, 7)
 * → First dice: Try face values from 1 to 6
 * → face = 1 → solve(6, 1, 6)
 * → face = 2 → solve(6, 1, 5)
 * → face = 3 → solve(6, 1, 4)
 * → face = 4 → solve(6, 1, 3)
 * → face = 5 → solve(6, 1, 2)
 * → face = 6 → solve(6, 1, 1)
 *
 * Now solve(6, 1, k) means we have 1 die left to get sum k.
 * For each solve(6, 1, k):
 * → Try face = k → solve(6, 0, 0) → base case → returns 1
 * → Other faces will give x < 0 or x > 6 → invalid
 *
 * So valid combinations:
 * 1st die: 1, 2, 3, 4, 5, 6
 * 2nd die must be: 6, 5, 4, 3, 2, 1 respectively
 * Total valid pairs:
 * (1,6), (2,5), (3,4), (4,3), (5,2), (6,1) → 6 ways
 *
 * Return value = 6
 */
```

---

## 🧠 Key Insights

- **Combinatorics vs DP:** While this can be viewed mathematically using combinations, Dynamic Programming provides a straightforward implementation avoiding complex combinatorial arithmetic.
- **State Definition:** The state is completely defined by two variables: the number of dice left to roll (`n`) and the remaining target sum (`x`). 
- **Pruning Invalid Paths:** The check `if (x < 0)` is a crucial optimization. It immediately kills recursive branches that exceed the target sum without needing further exploration.

---

## 🔍 Further Exploration

If you enjoyed this problem, you might also want to practice:
- **Coin Change II** (Finding combinations for a sum with infinite supplies)
- **Subset Sum Problem**
- **Partition Equal Subset Sum**

---

## 🔗 References

- **GeeksforGeeks Problem:** [Dice throw](https://www.geeksforgeeks.org/problems/dice-throw5349/1)

---

## 🧑‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

<div align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
  <img src="https://img.shields.io/badge/Dynamic_Programming-8A2BE2?style=for-the-badge&logo=codeforces&logoColor=white" alt="Dynamic Programming" />
  <img src="https://img.shields.io/badge/Algorithms-FF4B4B?style=for-the-badge" alt="Algorithms" />
</div>