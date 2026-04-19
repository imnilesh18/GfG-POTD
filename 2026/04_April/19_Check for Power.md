# ⚡ Check for Power

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/check-if-a-number-is-power-of-another-number5442/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Basic-5cb85c?style=for-the-badge" alt="Difficulty: Basic" />
    <img src="https://img.shields.io/badge/Accuracy-34.59%25-orange?style=for-the-badge" alt="Accuracy: 34.59%" />
    <img src="https://img.shields.io/badge/Points-1-blue?style=for-the-badge" alt="Points: 1" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two positive integers $x$ and $y$, determine if $y$ is a power of $x$. If $y$ is a power of $x$, return `true`. Otherwise, return `false`.

---

## 💡 Examples

```text
Input: x = 2, y = 8
Output: true 
Explanation: 2^3 is equal to 8.
```

```text
Input: x = 1, y = 8
Output: false
Explanation: Any power of 1 is not equal to 8.
```

```text
Input: x = 46, y = 205962976
Output: true
Explanation: 46^5 is equal to 205962976.
```

```text
Input: x = 50, y = 312500000
Output: true
Explanation: 50^5 is equal to 312500000.
```

<details>
<summary>📖 <b>Example Breakdown (x = 2, y = 8)</b></summary>

1. We are checking if $y$ is a power of $x$, which translates to the mathematical equation: $x^k = y$.
2. Substituting the values: $2^k = 8$.
3. We know that $2^3 = 8$, so $k = 3$.
4. Since $k$ is an exact integer, $8$ is indeed a valid power of $2$. Therefore, the output is `true`.
</details>

---

## ⚠️ Constraints

> - $1 \le x \le 10^3$
> - $1 \le y \le 10^9$

---

## 💻 Solution Approach

### Logarithmic Approach

```cpp
// Intuition: If y is a power of x (x^k = y), applying logarithm gives k = log(y) / log(x). If this resulting k is an exact integer, then y is a power of x.
// Approach: 
// 1. Handle edge cases where x is 1 (can only result in 1) or y is 1 (any number to power 0 is 1).
// 2. Use the change of base formula to compute the power `k` as log(y) / log(x).
// 3. Since floating-point math can cause slight precision errors (e.g., 3.0000000000000004), compare the result to its nearest integer (`round(res)`) using a tiny tolerance margin (`1e-10`).
// Time Complexity: O(1) - The log() function evaluates in constant time.
// Space Complexity: O(1) - We only use a few primitive variables.

class Solution {
  public:
    bool isPower(int x, int y) {
        // Edge case: 1^k = 1 only. If x is 1, y must also be 1.
        if (x == 1)
            return y == 1;
    
        // Edge case: x^0 = 1. Any positive integer to the power of 0 is 1.
        if (y == 1)
            return true;
    
        // Compute logarithm (change of base formula: log_x(y) = log_e(y) / log_e(x))
        double res = log(y) / log(x);
        
        // Compare with rounded value using a small tolerance to avoid floating point errors
        return fabs(res - round(res)) < 1e-10;
    }
};

/*
*
* Dry Run
*
* Input: x = 2, y = 8
* x == 1? False.
* y == 1? False.
* res = log(8) / log(2)
* res ≈ 2.07944154 / 0.69314718 ≈ 3.0
* round(res) = 3.0
* fabs(3.0 - 3.0) = 0.0
* 0.0 < 1e-10 is True.
* Output: true
*
*/
```

---

## 🧠 Key Insights
- **Floating Point Imprecision:** Standard `log()` functions return floating-point numbers. Simple equality checks (`res == (int)res`) often fail due to underlying representation errors (e.g., yielding `2.9999999999999996` instead of `3.0`). Using an epsilon/tolerance (`1e-10`) is a robust way to verify if a float is functionally an integer.
- **Logarithmic Change of Base:** The formula $\log_x(y) = \frac{\log(y)}{\log(x)}$ seamlessly translates the problem into an $O(1)$ calculation without needing iterative division or multiplication loops.

---

## 🔭 Further Exploration
- **Companies that asked this:** Zoho, SAP Labs.
- **Related Topics:** Mathematics, Number Theory, Logarithms.

---

## 🔗 References
- **GeeksforGeeks Problem:** [Check for Power](https://www.geeksforgeeks.org/problems/check-if-a-number-is-power-of-another-number5442/1)

---

## 🧑‍💻 Author
Developed and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags
`#Mathematical` `#Algorithms` `#GeeksForGeeks` `#Logarithms` `#C++`