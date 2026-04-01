# 🟧 Consecutive 1's Not Allowed

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-27.46%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a positive integer `n`, count all possible **distinct binary strings** of length `n` such that there are **no consecutive 1’s**.

---

## 💡 Examples

```text
Input: n = 3
Output: 5
Explanation: 5 strings are ("000", "001", "010", "100", "101").
```

```text
Input: n = 2
Output: 3
Explanation: 3 strings are ("00", "01", "10").
```

```text
Input: n = 1
Output: 2
Explanation: 2 strings are ("0", "1").
```

<details>
<summary>📖 <b>Example Breakdown (n = 3)</b></summary>

Let's generate all possible binary strings of length 3:
- "000" (Valid - no consecutive 1s)
- "001" (Valid)
- "010" (Valid)
- "011" (Invalid - contains "11")
- "100" (Valid)
- "101" (Valid)
- "110" (Invalid - contains "11")
- "111" (Invalid - contains "11")

Total valid distinct strings = **5**.
</details>

---

## ⚙️ Constraints

```text
1 ≤ n ≤ 44
```

---

## 💻 Solution Approaches

### Optimized Approach: Top-Down Dynamic Programming (Memoization)

This problem essentially models a constraint-based combination search. Instead of physically generating and validating every string, we can count valid configurations. If we append a `0` to our sequence, we can append either a `0` or `1` next. If we append a `1`, the very next character **must** be `0`. This overlapping subproblem structure is perfect for Dynamic Programming.

```cpp
// Intuition: The problem asks for binary strings of length `n` without consecutive 1s. If we place a '1', the next digit must be '0'. This behavior creates overlapping subproblems directly related to the Fibonacci sequence, where valid combinations for length 'n' depend on 'n-1' and 'n-2'.
// Approach: We use a top-down Recursive DP (Memoization) approach. We start generating from index 0. At any index `i`, we have two choices: place a '1' (forcing us to skip the next index, effectively jumping to `i+2`) or place a '0' (moving to `i+1`). We store the counts of valid configurations in a `memo` array to avoid re-evaluating the same states.
// Time Complexity: O(n) - Since we cache our results, each state from 0 to n is calculated exactly once.
// Space Complexity: O(n) - For the recursion call stack depth and the memoization array of size n.

class Solution {
  public:
    
    int countRecur(int i, int n, vector<int> &memo) {
        
        // Base case: if we reach or cross the length boundary, a valid string is formed
        if (i >= n) return 1;
        
        // If value is already memoized, return the precomputed result
        if (memo[i] != -1) return memo[i];
        
        // If we take 1 at ith index, 
        // we cannot have 1 at the adjacent index, so we jump to (i+2)
        int take = countRecur(i+2, n, memo);
        
        // If we skip 1 (i.e., place 0), we can safely consider
        // placing 1 at the immediate next index (i+1)
        int noTake = countRecur(i+1, n, memo);
        
        // Cache the sum of valid combinations and return
        return memo[i] = take + noTake;
    }
    
    int countStrings(int n) {
        
        // Initialize memoization array with -1 representing uncalculated states
        vector<int> memo(n, -1);
        
        // Start recursive tree evaluation from index 0
        return countRecur(0, n, memo);
    }
};

/*
*
* Dry Run
*
* Input: n = 3
* memo = [-1, -1, -1]
*
* Call countRecur(0, 3):
* Choice 1 (Take 1): call countRecur(2, 3)
* Choice 1 (Take 1): call countRecur(4, 3) -> hits base case, returns 1
* Choice 2 (No Take 1): call countRecur(3, 3) -> hits base case, returns 1
* memo[2] = 1 + 1 = 2
* (Returns 2)
*
* Choice 2 (No Take 1): call countRecur(1, 3)
* Choice 1 (Take 1): call countRecur(3, 3) -> hits base case, returns 1
* Choice 2 (No Take 1): call countRecur(2, 3) -> returns memo[2] = 2
* memo[1] = 1 + 2 = 3
* (Returns 3)
*
* memo[0] = take(2) + noTake(3) = 5
* * Output: 5
*
*/
```

---

## 🧠 Key Insights

- **Mathematical Relation:** The solution strictly maps to the Fibonacci sequence. The number of valid strings of length `N` without consecutive 1s is equal to the `(N+2)th` Fibonacci number.
- **State Jumping Strategy:** Advancing by `i+2` automatically handles the constraint of avoiding consecutive 1s, saving us from passing and checking a "previous character" boolean flag in our recursive state!

---

## 🔍 Further Exploration

If you enjoyed this problem, you might want to try these related challenges:
- *Count all possible paths in a matrix*
- *Fibonacci Sequence optimizations (Matrix Exponentiation)*
- *Generate All Valid Parentheses*

---

## 🔗 References

- **GeeksforGeeks Problem:** [Consecutive 1's Not Allowed](https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1)

---

## 👨‍💻 Author

**Nilesh** [![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=flat-square&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Dynamic Programming` `Data Structures` `Algorithms` `Flipkart` `Morgan Stanley` `Microsoft` `Snapdeal`