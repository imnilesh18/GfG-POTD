<div align="center">

# 🧮 Position of the Set Bit

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-position-of-set-bit3706/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-49.62%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-1-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given an integer `n`, determine the position of the **only set bit** (`1`) in its binary representation. The position is counted starting from `1` at the least significant bit (LSB).

* If `n` contains **exactly one** set bit, return its position.
* If `n` contains **no set bits** or **more than one** set bit, return `-1`.

---

## 🎯 Examples

### Example 1
```text
Input: n = 2
Output: 2
Explanation: 2 is represented as "10" in binary. It has only one set bit, which is at position 2.
```

### Example 2
```text
Input: n = 5
Output: -1
Explanation: 5 is represented as "101" in binary. It has two set bits; therefore, the output is -1.
```

<details>
<summary><b>📖 Example Breakdown (n = 2)</b></summary>

1. Binary representation of `2` is `...00000010`.
2. Counting from right to left (1-indexed):
   - Position 1: `0`
   - Position 2: `1` (This is our set bit!)
3. Since there are no other `1`s, the answer is `2`.

</details>

---

## 🛑 Constraints

> * `0 ≤ n ≤ 10^8`

---

## 💡 Solution Approach

### Bit Manipulation & Logarithm
**Intuition:** 
A number that contains exactly one set bit is a perfect power of 2. We can efficiently determine if a number is a power of 2 using the bitwise AND operation: `n & (n - 1)`. If this evaluates to `0` (and `n` is greater than `0`), it has exactly one set bit. Once confirmed, the position of that set bit can be found using the base-2 logarithm.
```cpp
// Intuition: A number with exactly one set bit is a power of 2. We can check this efficiently using bitwise AND, then find its position using base-2 logarithm.
// Approach: 
// 1. If n is 0 or has more than one set bit (checked by n & (n - 1) != 0), return -1.
// 2. Otherwise, use log2(n) to find the 0-indexed position of the set bit.
// 3. Add 1 to convert it to a 1-indexed position and return.
// Time Complexity: O(1) - Bitwise operations and log2 compute in constant time.
// Space Complexity: O(1) - No auxiliary space is used.

class Solution {
  public:
    int findPosition(int n) {
        // Check if n is 0 or has multiple set bits
        if (n == 0 || (n & (n - 1)) != 0)
            return -1;
    
        // Calculate 1-indexed position using base-2 logarithm
        return log2(n) + 1;
    }
};

/*
*
* Dry Run
* Input: n = 2
* Binary representation: "10"
* Step 1: n == 0 is false (2 != 0).
* Step 2: (n & (n - 1)) -> (2 & 1) -> ("10" & "01") -> 0. Exactly one set bit!
* Step 3: log2(2) + 1 -> 1 + 1 -> 2.
* Output: 2
*
*/
```

---

## 🧠 Key Insights

* **`n & (n - 1)` trick:** This is a classic bitwise operation that drops the lowest set bit of a number. If dropping the lowest set bit makes the number `0`, it means the number only had one set bit to begin with.
* **Math translation:** Once we know a number is a power of two, finding the set bit's position is essentially asking "2 to what power equals `n`?". The `log2(n)` function gives us the 0-based index, which we just shift by `+1` to meet the 1-based requirement of the problem.

---

## 🔍 Further Exploration

If you enjoyed this bit magic problem, consider exploring these related concepts and problems:
* **Power of 2** (Checking if a number is a power of 2)
* **Count Set Bits** (Brian Kernighan’s Algorithm)
* **Find the first set bit** from the right

---

## 🔗 References

* [GeeksforGeeks Problem: Position of the Set Bit](https://www.geeksforgeeks.org/problems/find-position-of-set-bit3706/1)
* [Bitwise Hacks for Competitive Programming](https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BitManipulation` `#Math` `#Logarithm` `#GeeksforGeeks` `#BasicDifficulty`