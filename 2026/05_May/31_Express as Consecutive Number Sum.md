# 🟩 Express as Consecutive Number Sum

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/consecutive-numbers-for-sum3132/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks"></a>
    <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty">
    <img src="https://img.shields.io/badge/Accuracy-43.44%25-blue?style=for-the-badge" alt="Accuracy">
    <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License">
</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a number `n`, find whether `n` can be expressed as the sum of two or more consecutive positive numbers.

---

## 💡 Examples

```text
Input: n = 10
Output: true
Explanation: 10 can be expressed as 1 + 2 + 3 + 4.
```

```text
Input: n = 8
Output: false
Explanation: 8 can't be expressed as the sum of two or more consecutive numbers.
```

```text
Input: n = 24
Output: true
Explanation: 24 can be expressed as 7 + 8 + 9.
```

<details>
<summary><b>📖 Example Breakdown (n = 10)</b></summary>

Let's test if `10` can be formed by consecutive numbers.
- Consecutive sequence starting at `1`: `1 + 2 + 3 + 4 = 10`. 
- Since we found a valid sequence, the answer is `true`.
- Conversely, for `8`, no consecutive positive integers will sum up to `8` (e.g., `1+2+3=6`, `2+3+4=9`, `3+4=7`, `4+5=9`). Hence, the answer is `false`.

</details>

---

## 🔒 Constraints

> - `1 ≤ n ≤ 10^9`

---

## 🛠️ Solution Approaches

### Mathematical Approach: Power of 2 Property
The core mathematical property governing this problem is that **a number can be written as the sum of consecutive positive numbers if and only if it is NOT a power of 2.** **Why a Power of 2 cannot be expressed?**
Every sum of `k` consecutive integers must have at least one odd factor greater than 1. 
The sum of `k` consecutive numbers is given by: 
`k(2a + k - 1) / 2 = n`
This simplifies to:
`k(2a + k - 1) = 2n`
If `k` is even, then `(k-1)` is odd. Adding `2a` (which is even) to an odd number results in an odd number. Thus, one of these factors must be odd and the other must be even. Since powers of 2 have only `2` as their prime factor, they contain no odd factors greater than 1. Therefore, they can never be expressed as the sum of consecutive positive integers.

**Why all other numbers can be expressed?**
Every odd number `n` can be written as `(2m + 1)`, which trivially splits into `m + (m+1)`—the sum of two consecutive numbers. Similarly, numbers with odd factors can be mapped back to arithmetic progressions.

### 💻 C++ Code

```cpp
// Intuition: A number can be expressed as the sum of consecutive positive numbers if and only if it is not a power of 2.
// Approach: We can determine if a number is a power of 2 using bit manipulation. The expression `(n & (n - 1)) == 0` evaluates to true for powers of 2. If it is a power of 2, we return false; otherwise, we return true. We also handle the base case `n = 1` separately.
// Time Complexity: O(1), as bitwise operations execute in constant time.
// Space Complexity: O(1), since we only use a few variables and no auxiliary space.

class Solution {
  public:
    bool isSumOfConsecutive(int n) {
        
        // 1 cannot be represented as a sum of two or more numbers
        if (n == 1) {
            return false;
        }
    
        // Check if n is a power of 2 using bitwise AND
        if ((n & (n - 1)) == 0) {
            return false;
        }
    
        // If it's not a power of 2, it can be represented
        return true;
    }
};

/*
*
* Dry Run
* Input: n = 10
* * n = 10. Check if n == 1 (False).
* Check if n is a power of 2: (10 & 9)
* 10 in binary: 1010
* 9 in binary: 1001
* 1010 & 1001 = 1000 (8 in decimal)
* Since (10 & 9) != 0, 10 is not a power of 2.
* The function returns true.
* Output: true
*
*/
```

---

## 🧠 Key Insights
- **Bit Manipulation Magic:** The trick `(n & (n - 1)) == 0` is an elegant, widely-used method to check if a number is a power of `2` in `O(1)` time.
- **Number Theory Application:** Understanding the prime factorization of a number (specifically the presence of odd factors) converts an `O(N)` simulation problem into a simple `O(1)` math problem.

---

## 🔗 Further Exploration
If you enjoyed this problem, you might also like:
- [Power of 2](https://www.geeksforgeeks.org/problems/power-of-2-1587115620/1)
- [Consecutive Numbers Sum (LeetCode 829)](https://leetcode.com/problems/consecutive-numbers-sum/)
- [Check whether K-th bit is set or not](https://www.geeksforgeeks.org/problems/check-whether-k-th-bit-is-set-or-not-1587115620/1)

---

## 📚 References
- **Original Problem:** [GeeksforGeeks - Express as Consecutive Number Sum](https://www.geeksforgeeks.org/problems/consecutive-numbers-for-sum3132/1)
- **Concept Reference:** [Bitwise Hacks for Competitive Programming](https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/)

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
![Mathematical](https://img.shields.io/badge/Mathematical-blue?style=flat-square) ![Algorithms](https://img.shields.io/badge/Algorithms-orange?style=flat-square) ![Bit Manipulation](https://img.shields.io/badge/Bit_Manipulation-purple?style=flat-square) ![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=flat-square)