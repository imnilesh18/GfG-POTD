# 🟢 Values with Equal Array Remainders

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/k-modulus-array-element0255/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy: 68.05%](https://img.shields.io/badge/Accuracy-68.05%25-blue?style=for-the-badge)](#)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](#)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]`, count the number of positive integers $k$ such that all elements of the array leave the same remainder when divided by $k$.

If there are **infinitely many** such values of $k$, return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [38, 6, 34]
Output: 3
Explanation: The values of k for which all elements leave the same remainder when divided by k are 1, 2, and 4.
- For k = 1, all elements leave remainder 0.
- For k = 2, all elements leave remainder 0.
- For k = 4, all elements leave remainder 2.
No other positive integer satisfies the condition. Hence, the answer is 3.
```

### Example 2
```text
Input: arr[] = [3, 2]
Output: 1
Explanation: The only positive integer for which both elements leave the same remainder is 1, since both numbers leave remainder 0 when divided by 1.
```

### Example 3
```text
Input: arr[] = [5, 5, 5]
Output: -1
Explanation: All elements in the array are equal. Therefore, for every positive integer k, all elements leave the same remainder when divided by k. Since there are infinitely many such values of k, the answer is -1.
```

<details>
<summary>📖 Example Breakdown (Walkthrough of Example 1)</summary>

<br>

**Input:** `arr[] = [38, 6, 34]`

1. **Difference Calculation Relative to `arr[0]` (38):**
   - $|arr[1] - arr[0]| = |6 - 38| = 32$
   - $|arr[2] - arr[0]| = |34 - 38| = 4$

2. **Compute Greatest Common Divisor (GCD):**
   - $g = \gcd(32, 4) = 4$

3. **Identify Positive Divisors of $g = 4$:**
   - Divisors are $1, 2, 4$.
   - Total count = $3$.

4. **Conclusion:**
   - Valid values of $k$ are $1, 2,$ and $4$. Final Output: `3`.

</details>

---

## ⚙️ Constraints

> - $1 \le \text{arr.size()}, \text{arr}[i] \le 10^5$

---

## 🚀 Solution Approach

### Mathematical Optimization (GCD & Divisors)

#### 💡 Intuition
For two numbers $a$ and $b$ to leave the same remainder modulo $k$, $a \equiv b \pmod k$, which mathematically implies that $k$ must divide the absolute difference $|a - b|$. Extending this rule across the entire array, $k$ must divide the difference between every element and a baseline element (e.g., `arr[0]`). Consequently, $k$ must be a factor of the Greatest Common Divisor (GCD) of all differences $|arr[i] - arr[0]|$. If all array elements are identical, the GCD is $0$, meaning every positive integer $k$ satisfies the condition, resulting in infinitely many solutions (`-1`).

#### 🛠️ C++ Code Implementation

```cpp
// Intuition: Two numbers leave the same remainder modulo k if and only if k divides their absolute difference. Therefore, k must divide the GCD of all differences |arr[i] - arr[0]|.
// Approach: Calculate the GCD 'g' of all absolute differences |arr[i] - arr[0]|. If g is 0, all elements are identical (infinitely many k), so return -1. Otherwise, count all positive divisors of 'g'.
// Time Complexity: O(n + sqrt(g)) where n is the array length and g is the GCD of absolute differences.
// Space Complexity: O(1) auxiliary space as only a few scalar variables are used.

class Solution {
  public:
    int sameMod(vector<int> &arr) {
        int n = arr.size();

        int g = 0;

        // Compute the GCD of all differences relative to arr[0].
        for (int i = 1; i < n; i++) {
            g = __gcd(g, abs(arr[i] - arr[0]));
        }

        // If all elements are equal, infinitely many values of k exist.
        if (g == 0) {
            return -1;
        }

        int cnt = 0;

        // Count all positive divisors of the GCD up to sqrt(g).
        for (int i = 1; i * i <= g; i++) {
            if (g % i == 0) {
                cnt++; // 'i' is a valid factor

                if (i != g / i) {
                    cnt++; // 'g / i' is the paired distinct factor
                }
            }
        }

        return cnt;
    }
};

/*
*
* Dry Run
* Input: arr = [38, 6, 34]
* 
* Step 1: Initialize g = 0, n = 3
* Step 2: Loop i = 1 to 2
*   - i = 1: abs(6 - 38) = 32 -> g = __gcd(0, 32) = 32
*   - i = 2: abs(34 - 38) = 4  -> g = __gcd(32, 4) = 4
* 
* Step 3: Check g == 0 -> false (g = 4)
* 
* Step 4: Count Divisors of g = 4 up to sqrt(4) = 2
*   - i = 1: 4 % 1 == 0 -> cnt = 1, paired divisor 4/1 = 4 (1 != 4) -> cnt = 2
*   - i = 2: 4 % 2 == 0 -> cnt = 3, paired divisor 4/2 = 2 (2 == 2) -> no extra increment
* 
* Step 5: Loop ends. Return cnt = 3
* Output: 3
*
*/
```

---

## 🔑 Key Insights

1. **Modular Congruence Principle:** 
   $a \equiv b \pmod k \iff k \mid (a - b)$. The problem reduces from calculating remainders for every $k$ to finding common divisors of array differences.
2. **GCD Reduction:** 
   Any number dividing a set of integers must also divide their Greatest Common Divisor ($g$). Hence, $k$ must be a factor of $g = \gcd(|arr[1]-arr[0]|, |arr[2]-arr[0]|, \dots)$.
3. **Infinite Solutions Edge Case:** 
   When all elements in the array are equal, $g = 0$. Since every positive integer $k \ge 1$ divides $0$, infinitely many $k$ exist, requiring a return value of `-1`.
4. **Optimized Factor Counting:** 
   Divisors come in complementary pairs $(i, g/i)$. Counting up to $\sqrt{g}$ runs in $O(\sqrt{g})$ time instead of naive $O(g)$.

---

## 🔗 Further Exploration

- **Follow-up Problem:** How would the solution change if $k$ must be strictly greater than $1$? *(Subtract $1$ from the total factor count when $g > 0$ to exclude $k = 1$.)*
- **Related GFG Problems:**
  - [GCD of Array](https://www.geeksforgeeks.org/problems/gcd-of-an-array4526/1)
  - [Common Factors of Two Numbers](https://www.geeksforgeeks.org/problems/common-factors-of-two-numbers/1)
  - [Equal Sum Differences](https://www.geeksforgeeks.org/problems/equal-sum0405/1)

---

## 📖 References

- **GeeksforGeeks Problem Page:** [Values with Equal Array Remainders](https://www.geeksforgeeks.org/problems/k-modulus-array-element0255/1)
- **C++ Documentation:** `std::__gcd` / `std::gcd` in `<numeric>` / `<algorithm>`

---

## 👤 Author

Developed with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`arrays` `mathematics` `number-theory` `gcd` `geeksforgeeks` `cpp`