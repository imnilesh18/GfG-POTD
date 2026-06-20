<div align="center">
  
# 🔢 Last Digit of a^b

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-last-digit-of-ab-for-large-numbers1936/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-23.8%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

</div>

---

## 📜 Problem Statement

Given two integers `a` and `b` in the form of strings, your task is to return the last digit of **a<sup>b</sup>**.

---

## 💡 Examples

```text
Input: a = "3", b = "10"
Output: 9
Explanation: 3^10 = 59049. The last digit is 9.

```

```text
Input: a = "6", b = "2"
Output: 6
Explanation: 6^2 = 36. The last digit is 6.

```

**For Input: `a = "3"`, `b = "10"**`

1. The last digit of `a` is `3`.
2. We need to find the last digit of `3^10`.
3. The powers of 3 follow a cyclic pattern for their last digits: `[3, 9, 7, 1]`. The cycle length is 4.
4. Reduce the exponent `b` by modulo 4: `10 % 4 = 2`.
5. The reduced exponent is 2. The 2nd power of 3 is `3^2 = 9`.
6. The last digit is `9`.

---

## ⚠️ Constraints

> * **1 ≤ `a.size()`, `b.size()` ≤ 1000**
> * **`a` and `b` consist only of numeric digits ('0' - '9')**
> * **`a` and `b` do not contain any leading zeros, except when the number itself is "0"**
> 
> 

---

## 🛠️ Solution Approaches

### Optimized Approach: Cyclicity of Last Digit (Mod 10)

**Intuition:** The last digit of any number raised to a power follows a repeating sequence (maximum cycle length = 4). Instead of calculating impossibly large exponential values, we can simply shrink the exponent using modulo 4 and calculate the small power using just the last digit of the base string.

**Step-by-step Approach:**

1. Extract the last digit of the base string `a`.
2. Because the exponent `b` is extremely large (up to 1000 characters), compute `b % 4` character by character using string-based modulo arithmetic.
3. If `b % 4 == 0`, it means the power is a multiple of 4. We take the reduced exponent as `4` instead of `0` to get the correct mapping in the cycle.
4. Compute the power using the last digit of the base and the reduced exponent.
5. Return `result % 10`.

```cpp
// Intuition: The last digit of a number raised to a power follows a repeating cycle of length 4. We can reduce the large exponent by modulo 4 and calculate the power using the last digit of the base.
// Approach:
// 1. If the exponent string 'b' is "0", anything raised to 0 is 1.
// 2. Extract the last digit of the base string 'a'.
// 3. Compute the modulo of the large string 'b' by 4.
// 4. If the modulo is 0, we use 4 as the exponent (since cycle repeats every 4th power).
// 5. Calculate (last_digit_a ^ reduced_b) % 10.
// Time Complexity: O(len(b)), where len(b) is the length of string 'b', as we iterate through 'b' to find b % 4.
// Space Complexity: O(1), as we only use a few integer variables.

class Solution {
  public:
    int getLastDigit(string& a, string& b) {
        // Handle edge case where power is 0
        if (b.length() == 1 && b[0] == '0') {
            return 1;
        }

        // Handle edge case where base is 0
        if (a.length() == 1 && a[0] == '0') {
            return 0;
        }

        // Extract the last digit of the base
        int baseLastDigit = a.back() - '0';

        // Find the exponent modulo 4
        int exponentMod = 0;
        for (int i = 0; i < b.length(); i++) {
            exponentMod = (exponentMod * 10 + (b[i] - '0')) % 4;
        }

        // If the modulo is 0, the actual power in the cycle is 4
        if (exponentMod == 0) {
            exponentMod = 4;
        }

        // Calculate the result for the reduced power
        int result = pow(baseLastDigit, exponentMod);

        // Return the last digit of the result
        return result % 10;
    }
};

/*
Dry Run

Input: a = "3", b = "10"

1. Check edge cases: b is not "0", a is not "0".
2. Extract base last digit: a.back() is '3' -> baseLastDigit = 3.
3. Compute exponent modulo 4:
   - Initial exponentMod = 0
   - i = 0: b[0] = '1' -> exponentMod = (0 * 10 + 1) % 4 = 1
   - i = 1: b[1] = '0' -> exponentMod = (1 * 10 + 0) % 4 = 10 % 4 = 2
   - Loop ends. exponentMod = 2.
4. exponentMod is not 0.
5. Calculate result: pow(3, 2) = 9.
6. Return result % 10 -> 9 % 10 = 9.

Output: 9
*/

```

---

## 🧠 Key Insights

* **Why modulo 4 works?** Numbers ending in `1, 3, 7, 9` have a cycle length of 4. Numbers ending in `2, 4, 8` have cycle lengths that are factors of 4 (i.e., 2 or 4). Numbers ending in `0, 1, 5, 6` stay the same. Modulo 4 safely encompasses all possible cyclic rules.
* String modulo arithmetic enables processing numbers far beyond `long long` limits safely and efficiently in $O(N)$ time.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Last Digit of a^b](https://www.geeksforgeeks.org/problems/find-last-digit-of-ab-for-large-numbers1936/1)

---

## 👨‍💻 Author

Created with passion by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

`#Mathematics` `#Algorithms` `#NumberTheory` `#GeeksforGeeks` `#CPP`