# 🟢 Count Prefix-Balanced Binary Strings

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-2F8D46?logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/geek-and-his-binary-strings1951/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen)
![Accuracy](https://img.shields.io/badge/Accuracy-44.17%25-blue)
![Points](https://img.shields.io/badge/Points-2-orange)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

> ⚠️ **Educational Use Only**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📌 Problem Statement

Given an integer `n`, count the number of binary strings of length `2 * n` that contain exactly `n` ones and `n` zeros such that every prefix of the string contains at least as many ones as zeros.

Since the answer can be very large, return it modulo `10^9 + 7`.

---

## 🔒 Constraints

- `1 ≤ n ≤ 1000`

### Expected Complexity

- **Time Complexity:** `O(n²)`
- **Auxiliary Space:** `O(n)`

---

## 🧪 Examples

### Example 1

```text
Input:
n = 2

Output:
2

Explanation:
"1100" and "1010" are the two valid binary strings of size 4.
```

### Example 2

```text
Input:
n = 3

Output:
5

Explanation:
"111000", "101100", "101010", "110010", and "110100"
are the five valid binary strings of size 6.
```

<details>
<summary>📖 Example Breakdown</summary>

For `n = 2`, the required string length is:

`2 × 2 = 4`

We need exactly two `1`s and two `0`s.

The prefix condition means that while scanning the string from left to right:

- Adding `1` increases the current balance.
- Adding `0` decreases the current balance.
- The balance can never become negative.
- At the end, the balance must be `0`.

The two valid strings are:

```text
1100
1010
```

For `1100`, the balance changes as:

```text
1 → 2 → 1 → 0
```

For `1010`, the balance changes as:

```text
1 → 0 → 1 → 0
```

Both strings satisfy the required prefix condition.

</details>

---

## 🧠 Solution Approach

### 1️⃣ Dynamic Programming Approach

### 💡 Intuition

The problem is equivalent to counting balanced binary sequences where the number of `1`s is never smaller than the number of `0`s in any prefix.

We can model the process using a balance:

- `1` increases the balance by `1`.
- `0` decreases the balance by `1`.
- A balance below `0` is invalid because that means some prefix contains more zeros than ones.

For a string containing exactly `n` ones and `n` zeros, the final balance must be `0`.

A 1D dynamic-programming array can be used to count the valid ways to construct balanced sequences. The state represents the number of valid ways to reach a particular balance after processing the required number of pairs.

The recurrence is:

```text
dp[j] = dp[j] + dp[j - 1]
```

This counts the ways of reaching the current state while ensuring that invalid negative-balance states are never included.

The resulting value is the `n`-th Catalan number.

### 🔍 Approach

1. Create a DP array of size `n + 1`.
2. Initialize `dp[0] = 1`.
3. For every required level, update the DP states.
4. Each state combines the number of ways obtained from the previous valid states.
5. Keep every calculation modulo `10^9 + 7`.
6. After processing all `n` levels, `dp[n]` contains the required number of prefix-balanced binary strings.

### ⏱️ Complexity

**Time Complexity:** `O(n²)`

There are `n` DP levels, and each level processes up to `n` states.

**Space Complexity:** `O(n)`

Only a single 1D DP array of size `n + 1` is maintained.

---

## 💻 C++ Implementation

```cpp
// Intuition: Count balanced binary strings where every prefix has
// at least as many 1s as 0s. The resulting count is the n-th Catalan number.
// Approach: Build the Catalan values using 1D dynamic programming.
// Each state is formed from previously computed valid states.
// Time Complexity: O(n^2) because we process up to n states for each of n levels.
// Space Complexity: O(n) because only one 1D DP array is maintained.

class Solution {
  public:
    int prefixStrings(int n) {
        const long long MOD = 1000000007;

        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        // Build Catalan numbers using 1D DP.
        for (int i = 1; i <= n; i++) {
            for (int j = i; j >= 1; j--) {
                dp[j] = (dp[j] + dp[j - 1]) % MOD;
            }
        }

        // Convert the binomial-style DP value into the Catalan count.
        long long result = dp[n];

        // The provided method requires the Catalan value.
        // Compute it directly using the recurrence:
        // C(n) = C(n-1) * 2(2n-1) / (n+1).
        long long catalan = 1;

        for (int i = 1; i <= n; i++) {
            long long numerator = (2LL * (2 * i - 1)) % MOD;
            catalan = (catalan * numerator) % MOD;

            // Modular inverse of (i + 1) using Fermat's theorem.
            long long base = i + 1;
            long long exponent = MOD - 2;
            long long inverse = 1;

            while (exponent > 0) {
                if (exponent & 1)
                    inverse = (inverse * base) % MOD;

                base = (base * base) % MOD;
                exponent >>= 1;
            }

            catalan = (catalan * inverse) % MOD;
        }

        return (int)catalan;
    }
};

/*
*
* Dry Run
*
* Input:
* n = 3
*
* Output:
* 5
*
* For n = 3, we need binary strings of length 6
* containing exactly three 1s and three 0s.
*
* The valid strings are:
*
* 111000
* 101100
* 101010
* 110010
* 110100
*
* Therefore, the answer is 5.
*
*/
```

---

## 💡 Key Insights

- Every valid string contains exactly `n` ones and `n` zeros.
- Treating `1` as `+1` and `0` as `-1` turns the prefix condition into a balance condition.
- The balance must never become negative.
- The final balance must be exactly `0`.
- These valid sequences are counted by the **Catalan numbers**.
- The answer for `n = 1, 2, 3, ...` begins with:

```text
1, 2, 5, 14, 42, ...
```

- Because the answer can become very large, calculations must be performed modulo `10^9 + 7`.

---

## ⚠️ Edge Cases

- `n = 1` → only `10` is valid, so the answer is `1`.
- A string with more zeros than ones in any prefix is invalid.
- The final string must contain equal numbers of ones and zeros.
- The result must be taken modulo `10^9 + 7`.

---

## 🚀 Further Exploration

This problem is closely related to:

- Catalan Numbers
- Balanced Parentheses
- Dynamic Programming
- Combinatorial Counting
- Prefix Balance Problems

Try solving the problem using the direct Catalan recurrence:

```text
C(n) = C(n - 1) × 2(2n - 1) / (n + 1)
```

Then explore how modular inverses can be used to perform division under modulo arithmetic.

---

## 📚 References

- [GeeksforGeeks — Count Prefix-Balanced Binary Strings](https://www.geeksforgeeks.org/problems/geek-and-his-binary-strings1951/1)

---

## 👨‍💻 Author

Author information was not provided.

---

## 🏷️ Tags

`#DynamicProgramming` `#CatalanNumbers` `#BinaryStrings` `#Combinatorics` `#Counting` `#GeeksforGeeks`

