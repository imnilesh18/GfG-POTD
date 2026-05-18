# 🟢 Maximum Sum Problem

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-57.09%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximum-sum-problem2211/1).

---

## 📝 Problem Statement

Given a number `n`, find its **maximum sum value** with `3` recursive breaks described below.

1. Break the number into three parts: `n/2`, `n/3`, and `n/4` (consider only the integer part or floor value).
2. Each number obtained in this process can be divided further recursively.
3. At every step, we can take the **maximum** of the current value of `n` or the max value obtained with the recursive process.
4. It is possible that we don't divide the number at all and choose it as the final answer.

---

<div align="center">
  <img src="https://media.geeksforgeeks.org/wp-content/uploads/20260418103804283472/maxsum.webp" alt="Recursive Tree Diagram" />
</div>

---

## 💡 Examples

### Example 1
```text
Input: n = 12
Output: 13
Explanation: Break n = 12 into three parts [12/2, 12/3, 12/4] = [6, 4, 3].
Now current sum is = (6 + 4 + 3) = 13.
Further breaking 6, 4 and 3 into parts will produce sums less than or equal to 6, 4 and 3 respectively.
```

### Example 2
```text
Input: n = 24
Output: 27
Explanation: Break n = 24 into three parts [24/2, 24/3, 24/4] = [12, 8, 6].
Now current sum is = (12 + 8 + 6) = 26.
But recursively breaking 12 would produce value 13.
So our maximum sum is 13 + 8 + 6 = 27.
```

<details>
<summary><b>📖 Example Breakdown (n = 12)</b></summary>

- Break `12` -> `12/2 = 6`, `12/3 = 4`, `12/4 = 3`. Sum = `6 + 4 + 3 = 13`.
- Max(12, 13) -> `13`.
- If we try to break `6` -> `6/2 = 3`, `6/3 = 2`, `6/4 = 1`. Sum = `3 + 2 + 1 = 6`. Max(6, 6) -> `6`.
- Breaking parts further never exceeds their original value for numbers less than 12. Thus, the optimal answer is 13.

</details>

---

## 🚀 Constraints

> - `0 ≤ n ≤ 10^6`
> - **Expected Time Complexity:** O(N)
> - **Expected Auxiliary Space:** O(N)

---

## 🧠 Solution Approach

### Optimized Approach: Dynamic Programming (Memoization)

**Intuition:** 
The recursive tree branches out into overlapping subproblems (e.g., `solve(12)` calls `solve(6)`, `solve(4)`, `solve(3)`—and `solve(24)` also eventually calls `solve(6)`, etc.). To avoid recalculating the same values, we can store the computed results in an array (Dynamic Programming via Memoization). 

```cpp
// Intuition: We need to find the max sum by recursively breaking a number into n/2, n/3, and n/4. Since overlapping subproblems occur, we use DP Memoization to cache and reuse previously calculated results.
// Approach: Create a dp array of size n+1 initialized to -1. For any number, recursively compute the sum of its three parts. Store and return the maximum between the number itself and the sum of its parts.
// Time Complexity: O(N) where N is the given number. Each state from 0 to N is computed at most once.
// Space Complexity: O(N) for the recursion stack and the memoization dp array.

class Solution {
  public:
    int solve(int n, vector<int> &dp) {
        // Base Case: 0 and 1 cannot be broken down further to yield a larger sum
        if (n == 0 || n == 1)
            return n;
    
        // Already computed: Return cached result to avoid redundant work
        if (dp[n] != -1)
            return dp[n];
    
        // Recursive calculation: Break the number into three distinct parts
        int sum = solve(n / 2, dp) + solve(n / 3, dp) + solve(n / 4, dp);
    
        // Store and return maximum of not breaking vs breaking the number
        return dp[n] = max(n, sum);
    }
    
    int maxSum(int n) {
        // Initialize all values with -1 (means not computed yet)
        vector<int> dp(n + 1, -1);
    
        // Start recursive function
        return solve(n, dp);
    }
};

/*
*
* Dry Run
*
* Input: n = 12
* dp array of size 13 initialized to -1
*
* solve(12) calls:
*   solve(6) -> solve(3) + solve(2) + solve(1)
*     solve(3) -> solve(1) + solve(1) + solve(0) = 1 + 1 + 0 = 2. max(3, 2) -> 3
*     solve(2) -> solve(1) + solve(0) + solve(0) = 1 + 0 + 0 = 1. max(2, 1) -> 2
*   solve(6) sum = 3 + 2 + 1 = 6. max(6, 6) -> 6
*   solve(4) -> solve(2) + solve(1) + solve(1) = 2 + 1 + 1 = 4. max(4, 4) -> 4
*   solve(3) -> already computed (cached), returns 3
*
* solve(12) sum = solve(6) + solve(4) + solve(3) = 6 + 4 + 3 = 13.
* max(12, 13) -> 13
*
* Output: 13
*/
```

---

## 🔑 Key Insights
- **Overlapping Subproblems:** Recursive calls naturally revisit the same values. Caching answers reduces the time complexity from exponential to linear $O(N)$.
- **Base Elements:** For values `0` and `1`, breaking them down further yields `0`, meaning they are their own maximum sums.

---

## 🔗 References
- **Original Problem:** [Maximum Sum Problem (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/maximum-sum-problem2211/1)
- **Company Tags:** Morgan Stanley

---

## 👨‍💻 Author
**Created by:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`Dynamic Programming` `Algorithms` `Recursion` `Memoization` `GeeksforGeeks`