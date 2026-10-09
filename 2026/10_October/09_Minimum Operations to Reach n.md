<div align="center">
  
# 🟩 Minimum Operations to Reach n

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-optimum-operation4504/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-60.02%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only**
<br>
This repository and its content are intended solely for educational purposes.
<br>
Solutions are provided for learning, practice, and reference only.
<br>
Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given a number `n`, your task is to find the minimum number of operations required to reach `n` starting from 0[cite: 2].

You have exactly two operations available:
1. **Double the number**[cite: 2]
2. **Add one to the number**[cite: 2]

---

## 💡 Examples

<details>
<summary><strong>📖 Example Breakdown 1</strong></summary>

```text
Input: n = 8
Output: 4
Explanation: 
0 + 1 = 1 --> 1 + 1 = 2 --> 2 * 2 = 4 --> 4 * 2 = 8.
Total operations = 4.
```
</details>

<details>
<summary><strong>📖 Example Breakdown 2</strong></summary>

```text
Input: n = 7
Output: 5
Explanation: 
0 + 1 = 1 --> 1 + 1 = 2 --> 1 + 2 = 3 --> 3 * 2 = 6 --> 6 + 1 = 7.
Total operations = 5.
```
</details>

---

## ⚠️ Constraints

> - `1 ≤ n ≤ 10^6`[cite: 2]
> - **Expected Time Complexity:** `O(log n)`[cite: 2]
> - **Expected Auxiliary Space:** `O(1)`[cite: 2]

---

## 🛠️ Solution Approaches

### 1️⃣ Approach 1: Top-Down Dynamic Programming (Memoization)

**Intuition:** 
We can explore both allowed operations to reach `n`. At any number `i`, we could have arrived from `i-1` (by adding 1) or from `i/2` if `i` is even (by doubling). By recursively taking the minimum of these valid paths and storing (memoizing) the results, we avoid recalculating overlapping subproblems.

```cpp
// Intuition: We explore both allowed operations to reach 'n'. We can arrive at 'i' from 'i-1' (by adding 1) or from 'i/2' if 'i' is even (by doubling). We memoize overlapping subproblems to prevent redundant calculations.
// Approach: 
// 1. Create a recursive function `solve(i)` that returns the minimum operations to reach `i`.
// 2. Base case: if `i == 0`, return 0.
// 3. If `memo[i]` is already computed, return it.
// 4. Calculate operations for the (i-1) path.
// 5. If `i` is even, calculate operations for the (i/2) path and take the minimum.
// 6. Store and return the result.
// Time Complexity: O(n) because each state from 0 to n is evaluated at most once.
// Space Complexity: O(n) for the memoization array and the recursion stack.
class Solution {
public:
    // Helper function for top-down recursion
    int solve(int i, vector<int>& memo) {
        // Base case: 0 operations needed to reach 0
        if (i == 0) return 0;
        
        // If we already calculated this state, return it
        if (memo[i] != -1) return memo[i];
        
        // Path 1: We arrived here by adding 1 to (i - 1)
        int ans = solve(i - 1, memo) + 1;
        
        // Path 2: If the number is even, we could have arrived by doubling (i / 2)
        if (i % 2 == 0) {
            ans = min(ans, solve(i / 2, memo) + 1);
        }
        
        // Store in memo and return
        return memo[i] = ans;
    }
    
    int minOperation(int n) {
        // Initialize memo array with -1 to indicate uncalculated states
        vector<int> memo(n + 1, -1);
        return solve(n, memo);
    }
};

/*
*
* Dry Run
* Input: n = 4
* solve(4) -> min(solve(3)+1, solve(2)+1)
*   solve(3) -> solve(2)+1
*     solve(2) -> min(solve(1)+1, solve(1)+1)
*       solve(1) -> solve(0)+1 = 1
*     solve(2) = min(1+1, 1+1) = 2
*   solve(3) = 2 + 1 = 3
* solve(4) -> min(3+1, 2+1) = 3
* Output: 3
*/
```

---

### 2️⃣ Approach 2: Bottom-Up Dynamic Programming (Tabulation)

**Intuition:** 
Instead of recursion, we can iteratively build the answer from `1` up to `n`. The minimum operations needed to reach any number `i` depends entirely on the precalculated results for `i-1` and, if `i` is even, `i/2`.

```cpp
// Intuition: We can build the answer from 1 up to 'n' iteratively. The minimum operations for 'i' depends entirely on 'i-1' and, if 'i' is even, 'i/2'.
// Approach:
// 1. Create a `dp` array of size `n + 1` initialized to 0.
// 2. Base case `dp[0] = 0` is already handled implicitly.
// 3. Iterate `i` from 1 to `n`.
// 4. For every `i`, default to `dp[i-1] + 1` (Path 1).
// 5. If `i` is even, update `dp[i]` to `min(dp[i], dp[i/2] + 1)` (Path 2).
// 6. Return `dp[n]`.
// Time Complexity: O(n) as we loop through 1 to n exactly once.
// Space Complexity: O(n) auxiliary space to store the DP array.
class Solution {
public:
    int minOperation(int n) {
        if (n == 0) return 0;
        
        // dp array replaces the memo array
        // dp[i] stores the minimum operations to reach i
        vector<int> dp(n + 1, 0);
        
        // Base case is inherently dp[0] = 0
        
        // Build the solution from 1 up to n
        for (int i = 1; i <= n; i++) {
            
            // Path 1: We arrived here by adding 1 to (i - 1)
            dp[i] = dp[i - 1] + 1;
            
            // Path 2: If the number is even, we could have arrived by doubling (i / 2)
            if (i % 2 == 0) {
                dp[i] = min(dp[i], dp[i / 2] + 1);
            }
        }
        
        return dp[n];
    }
};

/*
*
* Dry Run
* Input: n = 4
* dp = [0, 0, 0, 0, 0]
* i=1: dp[1] = dp[0]+1 = 1
* i=2: dp[2] = dp[1]+1 = 2, min(2, dp[1]+1) = 2
* i=3: dp[3] = dp[2]+1 = 3
* i=4: dp[4] = dp[3]+1 = 4, min(4, dp[2]+1) = 3
* Output: dp[4] = 3
*/
```

---

### 3️⃣ Approach 3: Greedy / Reverse Psychology (Optimal)

**Intuition:** 
Instead of trying to figure out when to add or multiply going forwards from `0` to `n`, we apply "reverse psychology" and go backwards from `n` to `0`. If `n` is even, dividing it by 2 is always optimal because it shrinks the number much faster than subtracting 1. If `n` is odd, we have no choice but to subtract 1. 

```cpp
// Intuition: Working backward from 'n' to 0 is always optimal. Halving an even number removes multiple "+1" operations at once.
// Approach:
// 1. Initialize an `operations` counter to 0.
// 2. Loop while `n > 0`.
// 3. If `n` is even, divide it by 2 (reversing the "double" operation).
// 4. If `n` is odd, subtract 1 (reversing the "add 1" operation).
// 5. Increment the `operations` counter for each step.
// 6. Return the total `operations`.
// Time Complexity: O(log n) because dividing by 2 halves the problem size at least every two steps.
// Space Complexity: O(1) because we only use a few integer variables.
class Solution {
public:
    int minOperation(int n) {
        int operations = 0;
        
        // Work backward from n to 0
        while (n > 0) {
            if (n % 2 == 0) {
                // Reverse psychology: if even, we must have doubled it
                n = n / 2;
            } else {
                // Reverse psychology: if odd, we must have added 1
                n = n - 1;
            }
            operations++;
        }
        
        return operations;
    }
};

/*
*
* Dry Run
* Input: n = 8
* operations = 0
* Step 1: n=8 is even -> n = 4, operations = 1
* Step 2: n=4 is even -> n = 2, operations = 2
* Step 3: n=2 is even -> n = 1, operations = 3
* Step 4: n=1 is odd  -> n = 0, operations = 4
* Loop ends. Output = 4.
*/
```

---

## 🧠 Key Insights
* **The DP Approaches** clearly establish the mathematical relationships between steps, serving as great foundational logic for this problem.
* **The Greedy Approach** takes advantage of the mathematical certainty that "doubling" scales exponentially. By working backward (from `n` to `0`), we bypass the `O(N)` space and time requirements, collapsing the complexity to a highly optimal `O(log N)` time and `O(1)` space[cite: 2].

---

## 🔍 Further Exploration
* **Broken Calculator (LeetCode)** - A very similar problem that reinforces the reverse psychology / greedy paradigm.
* **Min Cost Climbing Stairs** - Great for practicing bottom-up DP logic.

---

## 🔗 References
* **GeeksforGeeks Problem:** [Minimum Operations to Reach n](https://www.geeksforgeeks.org/problems/find-optimum-operation4504/1)[cite: 2]

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#DynamicProgramming` `#Greedy` `#Math` `#Optimization` `#GeeksforGeeks` `#C++`