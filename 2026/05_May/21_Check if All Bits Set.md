# 💯 Check if All Bits Set

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty](https://img.shields.io/badge/Difficulty-Basic-brightgreen) ![Accuracy](https://img.shields.io/badge/Accuracy-52.59%25-blue) ![Points](https://img.shields.io/badge/Points-1-blue) ![License](https://img.shields.io/badge/License-MIT-green)

<div align="center">
⚠️ <b>Educational Use Only</b><br/>
This repository and its content are intended solely for educational purposes.<br/>
Solutions are provided for learning, practice, and reference only.<br/>
Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given a number `n`, check whether every bit in the binary representation of the given number is set or not. Return `true` if yes, otherwise `false`.

---

## 💡 Examples

**Example 1:**
```text
Input: n = 7
Output: true
Explanation: Binary for 7 is 111. All the bits are set so the output is true.

```

**Example 2:**

```text
Input: n = 8
Output: false
Explanation: Binary for 8 is 1000. All the bits are not set so the output is false.

```

**Example 3:**

```text
Input: n = 0
Output: false
Explanation: All the bits are 0 so the output is false.

```

1. The integer `7` in binary representation is `111`.
2. Every position from the most significant bit to the least significant bit is a `1`.
3. Because there are no `0`s mixed in the active bit sequence, the condition holds `true`.

---

## ⚠️ Constraints

* **0 ≤ n ≤ 10^5**
* **Expected Time Complexity:** O(1)
* **Expected Auxiliary Space:** O(1)

---

## 💻 Solution Approach

**Summary:**
The most optimized way to check if all bits are set involves a simple mathematical property of binary numbers. If a number `n` has all its bits set to `1` (like `111` for 7), adding `1` to it flips all those `1`s to `0`s and carries over a `1` to the next power of 2 (resulting in `1000` for 8). By performing a bitwise `AND` operation between `n` and `n + 1`, we should get `0` if all bits were originally set.

```cpp
// Intuition: If all bits of a number n are set (e.g., 7 is 111 in binary), adding 1 to it makes it a power of 2 (8 is 1000). A bitwise AND of n and n+1 will yield 0.
// Approach: Check if n is 0 (base case, returns false). If not, evaluate (n & (n + 1)). If the result is 0, all bits were set.
// Time Complexity: O(1) as bitwise operations take constant time.
// Space Complexity: O(1) since no extra memory is utilized.
class Solution {
  public:
    bool isBitSet(int n) {
        // A number with 0 has no set bits, so return false
        if (n == 0) {
            return false;
        }
        
        // If all bits are 1, adding 1 makes it a power of 2.
        // n & (n + 1) will be 0 if all original bits were 1.
        return (n & (n + 1)) == 0;
    }
};

/*
*
* Dry Run
*
* Input: n = 7 (Binary: 111)
* n == 0 is false.
* n + 1 = 8 (Binary: 1000)
* n & (n + 1) -> 7 & 8 -> 0111 & 1000 = 0000
* Result: 0 == 0 -> true
*
* Input: n = 8 (Binary: 1000)
* n == 0 is false.
* n + 1 = 9 (Binary: 1001)
* n & (n + 1) -> 8 & 9 -> 1000 & 1001 = 1000 (which is 8)
* Result: 8 == 0 -> false
*
*/

```

---

## 🔑 Key Insights

* **Bitwise Operations:** Leveraging bitwise operators is exceptionally fast and allows O(1) time complexity.
* **Power of 2 Trick:** The expression `n & (n + 1)` is famously used to strip the lowest set bit. In this specific scenario, checking if `(n & (n + 1)) == 0` essentially checks if `n + 1` is a perfect power of 2, which only happens if `n` was a solid block of `1`s (e.g., 3, 7, 15, 31).

---

## 🔍 Further Exploration

* **Check if a Number is a Power of 2:** Uses a similar concept `(n & (n - 1)) == 0`.
* **Count Set Bits:** Brian Kernighan's Algorithm to count the number of 1s in a binary representation.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Check if All Bits Set](https://www.geeksforgeeks.org/problems/check-set-bits5408/1)

---

## ✍️ Author

**Nilesh**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `Amazon`
* `Bit Magic`
* `Data Structures`
* `GeeksforGeeks`